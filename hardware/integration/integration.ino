/*
 * File:      integration.ino
 * Function:  風呂危険検知IoTシステム
 *            実装版
 * Date:      2020/11/05 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 * Software   Based on function programs
 * Model Note Move:
 *            going, pre-subloop2
 */
// libraries
// LCD
#include <Wire.h>  // I2C interface
#include<i2clcd.h> // i2clcdライブラリのヘッダ・ファイルを読み込む
// RFID
#include <SPI.h>
#include <MFRC522.h>
// JSON
#include <ArduinoJson.h>
// Wi-Fi
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
// Deep Sleep
#include <esp_deep_sleep.h>

// defines
// LCD
#define DISPLAY_TIME 4.0
// Distance
#define Trigger_Pin 17
#define Echo_Pin 16
// buzzer
// ピン番号
#define BUZZER_PIN 25
// 音を鳴らす時間
#define BEAT 500
// 音階名と周波数の対応
#define SO 392.00
#define SO_SH 416.00
#define RE 587
#define MI_FL 623.295
// RFID(ESP32)
#define SS_PIN 5
#define RST_PIN 26
// integration
#define GRANDPA "DADC3186"
#define GRANDMA "EA850485"
#define OTHER "0A1AF384"

// class
// LCD
i2clcd qlcd(0x3E, 3, 0x20);
// RFID
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

// variables
// Wi-Fi
const char *ssid = "Yu";
const char *password = "kY981108";
// JSON
// API Domain
const char *url = "http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/";
// Deep Sleep
const int sleeping_time = 1;  // ディープスリープ時間（秒）
// integration
const char *device_id = "prototypedevice01234";
boolean ongoingFlag = false;
boolean bathalertFlag = false;
boolean finishFlag = false;
int global_status;
int global_tag_id;
char* global_user_id;
char* global_hash;
int global_alert_time;

// functions
// LCD
/* LCDに表示する */
void displayValues(String row1, String row2) {
  qlcd.lcdclear();  // LCDモジュールのクリア
  // 1行目
  qlcd.lcdcu_set(0, 0);
  qlcd.i2cprint(row1);
  // 2行目
  qlcd.lcdcu_set(0, 1);
  qlcd.i2cprint(row2);

  delay(200);
}
// Wi-Fi
/* Wi-Fi special connection function*/
void wifi_special_connection(){
  Serial.println("start Wifi...");
  
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  
  if (!wifiManager.startConfigPortal("OnDemandAP")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
  }

  Serial.print("Wifi has been connected!");
}
// JSON
/* JSONのポストとJSONのString形式の取得 */
String jsonPost(const char url[], char api[], char json[]){
  String http_response;
  String host = (String)url + (String)api;

  HTTPClient http;
  http.begin(host);
  http.addHeader("Content-Type", "application/json");
  int status_code = http.POST((uint8_t*)json, strlen(json));
  if( status_code == 200 ){
    // JSON取得
    http_response = http.getString();
  }
  http.end();
  return http_response;
}
// distance
/* Send Trigger pulse */
void sendTrigger(){
  digitalWrite(Trigger_Pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_Pin, LOW);
}
double getDistance(){
  double V = 340;  // 音速
  double Duration = 0;  // 受信した時間
  double Distance = 0;  // 測定距離
  
  sendTrigger();  // 発射

  Duration = pulseIn(Echo_Pin, HIGH ); //発射から立ち下がりまでのus

  Duration = Duration/2; //往復距離を半分にする
  Distance = Duration*V*100/1000000; // 音速を計算　cm s に変換(m usより)
  return Distance;
}
// buzzer
/* アラート音1サイクル呼び出し */
void callAlert(){
  ledcWriteTone(1, 0);
  delay(BEAT * 0.125);
  ledcWriteTone(1, SO);
  delay(BEAT * 0.125);
  ledcWriteTone(1, RE);
  delay(BEAT * 0.125);
  ledcWriteTone(1, 0);
  delay(BEAT * 0.125);
  ledcWriteTone(1, SO_SH);
  delay(BEAT * 0.125);
  ledcWriteTone(1, MI_FL);
  delay(BEAT * 0.125);
  ledcWriteTone(1, 0);
  delay(BEAT * 0.5);
}
// RFID
/* Byte data -> String */
void array_to_string(byte array[], unsigned int len, char buffer[]) 
{ 
  for (unsigned int i = 0; i < len; i++) { 
    byte nib1 = (array[i] >> 4) & 0x0F; 
    byte nib2 = (array[i] >> 0) & 0x0F; 
    buffer[i*2+0] = nib1 < 0xA ? '0' + nib1 : 'A' + (nib1 - 0xA); 
    buffer[i*2+1] = nib2 < 0xA ? '0' + nib2 : 'A' + (nib2 - 0xA); 
  } 
  buffer[len*2] = '\0'; 
}
/* Helper routine to dump a byte array as hex values */
String printHex(byte *buffer, byte bufferSize) {
  char str[32] = ""; 
  array_to_string(buffer, bufferSize, str); 
  return str;
}
/* RFIDタグの読み取り */
String readRfid(){
  /* カードが新しいかと、カードが読み取れるかを確認 */
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!rfid.PICC_IsNewCardPresent())  // PICC_IsNewCardPresent() -> 「New Cardが現れた」
    return "ERROR";
  // Verify if the NUID has been readed
  if (!rfid.PICC_ReadCardSerial())  // PICC_ReadCardSerial() -> 「カードが読み取れるか確認」
    return "ERROR";
  /* PICタイプの取得 */
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return "ERROR";
  }
  String nuid = printHex(rfid.uid.uidByte, rfid.uid.size);
  // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
  return nuid;
}


void setup() {
  // Serial connection speed
  Serial.begin(115200);

  // initiate
  // LCD
  qlcd.init_lcd();  // LCDモジュール初期化
  // Distance
  pinMode(Trigger_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT);
  digitalWrite(Trigger_Pin, LOW);
  // buzzer
  ledcSetup(1, 12000, 8);
  ledcAttachPin(BUZZER_PIN, 1);
  // RFID
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  /* Setup */
  // 起動情報を表示
  displayValues("ANSHIN FLOW", "START UP!");
  delay(DISPLAY_TIME * 1000);
  
  // Wi-Fi接続
  // displayValues("Connecting...", "");
  // connectWifi(ssid, password);
  displayValues("From App,", "connect to Wi-Fi");
  wifi_special_connection();
  
  // 接続完了を表示
  displayValues("Wi-Fi network", "has connected!");
  // 2秒待機
  delay(DISPLAY_TIME * 1000);
}
 
void loop() {
  // time
  int start_time;
  int substart_time;
  int current_time;
  int diff_time;
  int subdiff_time;
  // bath param
  String person;
  
  // Subloop1
  while(true && !finishFlag){
    // connection
    // 情報表示
    displayValues("Verifying", "Dev Connection");
    // JSONオブジェクト作成
    const int capacity = JSON_OBJECT_SIZE(1);  // JSONオブジェクトの要素数
    StaticJsonDocument<capacity> json_request;
    // JSON構造化
    json_request["device_id"] = device_id;
    // json_request.stringify -> buffer
    char buffer[255];
    serializeJson(json_request, buffer, sizeof(buffer));
    // API指定
    char *api = "device/edit/connection";
    // HTTP POST
    String json = jsonPost(url, api, buffer);
    // JSON格納変数作成
    StaticJsonDocument<200> doc;
    // JSONパース
    deserializeJson(doc, json);
    // Output
    const int status = doc["status"];
    const int substatus = doc["substatus"];
    const int tag_id = doc["tag_id"];
    const char* user_id = doc["user_id"];
    const int alert_time = doc["alert_time"];
    const char* hash = doc["hash"];
    global_hash = (char*)hash;
    global_user_id = (char*)user_id;
    global_alert_time = (int)alert_time;
    // Serial.println(global_alert_time);
    // Serial.println(global_hash);
    // Serial.println(hash);
    
    // 情報表示
    displayValues("Completed", "Dev Connection");
    
    // status
    if(status == 200){
      // substatus
      if(substatus == 2){  // 2
        // ハッシュ取得
        // break
        break;
      }
      else if(substatus == 1){  // 1
        // ongoingへ
        displayValues("Your Status is", "BATH TIME!");
        delay(DISPLAY_TIME * 1000);
        ongoingFlag = true;
        if(tag_id == 0){
          person = "GRANDPA";
        }
        else if(tag_id == 1){
          person = "GRANDMA";
        }
        else{
          person = "OTHERS";
        }
        break;
      }
      else if(substatus == 0){  // 0
        // 情報表示
        displayValues("You've no device", "Reconnect af 30s");
        // 30秒待機
        delay(30 * 1000);
      }
    }
    else{
      // deepsleep
      displayValues("Rebooting...", "");
      esp_deep_sleep(sleeping_time * 1000000LL);
    }
  }

  if(!ongoingFlag){
    // Subloop1完了を表示
    displayValues("FOR BATH TIME,", "PLZ Touch TAG!");
    
    // 2秒待機
    // 必要なさそうだから消す
    // delay(DISPLAY_TIME * 1000);
    
    // 時間計測開始
    // 初期化
    start_time = millis();
    current_time = millis();
    diff_time = (current_time - start_time) / 1000;
  }

  // Subloop2
  while(true && !ongoingFlag){
    // displayValues("Subloop2!", "");
    // 距離センサを計測
    double distance = getDistance();
    
    // distance > 100
    if(distance > 30){  // true
      // Bottomloop1
      while(true){
        // 情報表示
        displayValues("Close door and", "PLZ Touch TAG!");
        // ブザー
        callAlert();
        
        // RFID READABLE
        String nuid = readRfid();
        if(!nuid.equals("ERROR")){  // true
          // 情報表示, 2秒表示
          displayValues("Released Alert!", "");
          delay(DISPLAY_TIME * 1000);
          displayValues("FOR BATH TIME,", "PLZ Touch TAG!");

          // break
          break;
        }
      }
    }
    // RFID READABLE
    String nuid = readRfid();
    if(!nuid.equals("ERROR")){  // true
      // タグ情報の取得
      if(nuid.equals(GRANDPA)){
        const int tag_id = 0;
        global_tag_id = (int)tag_id;
        person = "GRANDPA";
      }else if(nuid.equals(GRANDMA)){
        const int tag_id = 1;
        global_tag_id = (int)tag_id;
        person = "GRANDMA";
      }else if(nuid.equals(OTHER)){
        const int tag_id = 2;
        global_tag_id = (int)tag_id;
        person = "OTHERS";
      }else{
        continue;
      }
      
      // break
      break;
    }
    else{
      // second > 300
      current_time = millis();
      diff_time = (current_time - start_time) / 1000;
      if(diff_time > 300){  // true
        // 情報表示
        displayValues("Keeping with", "Wi-Fi connection");
        
        // return
        return;
      }
    }
  }

  if(!ongoingFlag){
    // チェックイン
    displayValues("For BATH", "Checkin...");
    // JSONオブジェクト作成
    const int capacity = JSON_OBJECT_SIZE(4);  // JSONオブジェクトの要素数
    StaticJsonDocument<capacity> json_request;
    // JSON構造化
    json_request["device_id"] = device_id;
    json_request["tag_id"] = global_tag_id;
    // Serial.println(global_user_id);
    json_request["user_id"] = (const char*)global_user_id;
    json_request["hash"] = (const char*)global_hash;
    // Serial.println(global_hash);
    // json_request.stringify -> buffer
    char buffer[255];
    serializeJson(json_request, buffer, sizeof(buffer));
    // Serial.println(buffer);
    // API指定
    char *api = "bath/new/checkin";
    // HTTP POST
    String json = jsonPost(url, api, buffer);
    // JSON格納変数作成
    StaticJsonDocument<200> doc;
    // JSONパース
    deserializeJson(doc, json);
    // Output
    const int status = doc["status"];
    const char* hash = doc["hash"];
    global_hash = (char*)hash;
    if(status == 200){
      // チェックインを表示
      displayValues("You've got", "Checkin!");
      // 2秒待機
      delay(DISPLAY_TIME * 1000);
    }
    else{
      // deepsleep
      displayValues("Rebooting...", "");
      esp_deep_sleep(sleeping_time * 1000000LL);
    }
  }

  // Subloop3
  start_time = millis();
  substart_time = millis();
  while(true){
    // 時間計測開始
    current_time = millis();
    diff_time = (current_time - start_time) / 1000;
    subdiff_time = (current_time - substart_time) / 1000;
    
    // Bottomloop1
    while(true){
      // display situation
      current_time = millis();
      diff_time = (current_time - start_time) / 1000;
      String row = person + " ";
      String row_buffer = (String)(diff_time / 60);
      row = row + row_buffer;
      row = row + "[min]";
      displayValues(row, "PLZ tag checkout");

      // distance > 30 (+ timer)
      double distance = getDistance();
      current_time = millis();
      diff_time = (current_time - start_time) / 1000;
      Serial.println(distance);
      Serial.println(diff_time);
      Serial.println();
      if((distance > 30) && (diff_time > 60) && !ongoingFlag){  // true
        // break
        break;
      }
      // total second > 60 min (DANGER)
      current_time = millis();
      diff_time = (current_time - start_time) / 1000;
      if(((diff_time / 60) > global_alert_time) && !ongoingFlag && !bathalertFlag){  // true
        // Bottomloop2
        // ongoing
        displayValues("Reporting to", "Server...");
        // JSONオブジェクト作成
        const int capacity = JSON_OBJECT_SIZE(3);  // JSONオブジェクトの要素数
        StaticJsonDocument<capacity> json_request;
        // JSON構造化
        json_request["device_id"] = device_id;
        json_request["tag_id"] = global_tag_id;
        json_request["hash"] = (const char*)global_hash;
        // json_request.stringify -> buffer
        char buffer[255];
        serializeJson(json_request, buffer, sizeof(buffer));
        // API指定
        char *api = "bath/edit/ongoing";
        // HTTP POST
        String json = jsonPost(url, api, buffer);
        // JSON格納変数作成
        StaticJsonDocument<200> doc;
        // JSONパース
        deserializeJson(doc, json);
        // Output
        const int status = doc["status"];
        const char* hash = doc["hash"];
        global_hash = (char*)hash;
        // status
        if(status == 200){  // 200
          bathalertFlag = true;
          while(true){
            // 情報表示
            displayValues("Too long bath.", "PLZ touch TAG!");
            // ブザー
            callAlert();
            // 情報表示
            displayValues("DANGER", "DANGER");
            // ブザー
            callAlert();
            // READABLE
            // RFID READABLE
            String nuid = readRfid();
            if(!nuid.equals("ERROR")){  // true
              // break
              break;
            }
          }
          // 情報表示
          displayValues("Released Alert!", "");
          delay(DISPLAY_TIME * 1000);
        }
        else{
          // deepsleep
          displayValues("Rebooting...", "");
          esp_deep_sleep(sleeping_time * 1000000LL);
        }
        
        // ongoing
        displayValues("Reporting to", "Server...");
        // JSONオブジェクト作成
        const int capacity_after_alert = JSON_OBJECT_SIZE(3);  // JSONオブジェクトの要素数
        StaticJsonDocument<capacity_after_alert> json_request_after_alert;
        // JSON構造化
        json_request_after_alert["device_id"] = device_id;
        json_request_after_alert["tag_id"] = global_tag_id;
        json_request_after_alert["hash"] = (const char*)global_hash;
        // json_request.stringify -> buffer
        char buffer_after_alert[255];
        serializeJson(json_request_after_alert, buffer_after_alert, sizeof(buffer_after_alert));
        // API指定
        char *api_after_alert = "bath/edit/ongoing";
        // HTTP POST
        String json_after_alert = jsonPost(url, api_after_alert, buffer_after_alert);
        // JSON格納変数作成
        StaticJsonDocument<200> doc_after_alert;
        // JSONパース
        deserializeJson(doc_after_alert, json);
        // Output
        const int status_after_alert = doc_after_alert["status"];
        const char* hash_after_alert = doc_after_alert["hash"];
        global_hash = (char*)hash_after_alert;
        // status
        if(status_after_alert == 200){  // 200
          // 情報表示
          displayValues("Reported", "your condition!");
          // 2秒待機
          delay(DISPLAY_TIME * 1000);
          // 周期時間リセット
          substart_time = millis();
        }
        else{
          // deepsleep
          displayValues("Rebooting...", "");
          esp_deep_sleep(sleeping_time * 1000000LL);
        }
      }
      else{  // false
        // second > 300 (Cycle)
        current_time = millis();
        subdiff_time = (current_time - substart_time) / 1000;
        if(((subdiff_time / 60) > 5) || ongoingFlag){  // true
          ongoingFlag = false;
          // ongoing
          displayValues("Reporting to", "Server...");
          // JSONオブジェクト作成
          const int capacity = JSON_OBJECT_SIZE(3);  // JSONオブジェクトの要素数
          StaticJsonDocument<capacity> json_request;
          // JSON構造化
          json_request["device_id"] = device_id;
          json_request["tag_id"] = global_tag_id;
          json_request["hash"] = (const char*)global_hash;
          // json_request.stringify -> buffer
          char buffer[255];
          serializeJson(json_request, buffer, sizeof(buffer));
          // API指定
          char *api = "bath/edit/ongoing";
          // HTTP POST
          String json = jsonPost(url, api, buffer);
          // JSON格納変数作成
          StaticJsonDocument<200> doc;
          // JSONパース
          deserializeJson(doc, json);
          // Output
          const int status = doc["status"];
          const char* hash = doc["hash"];
          global_hash = (char*)hash;
          // status
          if(status == 200){  // 200
            // 情報表示
            displayValues("Reported", "your condition!");
            // 2秒待機
            delay(DISPLAY_TIME * 1000);
            // 周期時間リセット
            substart_time = millis();
          }
          else{
            // deepsleep
            displayValues("Rebooting...", "");
            esp_deep_sleep(sleeping_time * 1000000LL);
          }
        }
      }
    }

    // checkout
    displayValues("Checkout...", "");
    // JSONオブジェクト作成
    const int capacity = JSON_OBJECT_SIZE(3);  // JSONオブジェクトの要素数
    StaticJsonDocument<capacity> json_request;
    // JSON構造化
    json_request["device_id"] = device_id;
    json_request["tag_id"] = global_tag_id;
    json_request["hash"] = (const char*)global_hash;
    // json_request.stringify -> buffer
    char buffer[255];
    serializeJson(json_request, buffer, sizeof(buffer));
    Serial.println(buffer);
    // API指定
    char *api = "bath/edit/checkout";
    // HTTP POST
    String json = jsonPost(url, api, buffer);
    // JSON格納変数作成
    StaticJsonDocument<200> doc;
    // JSONパース
    deserializeJson(doc, json);
    // Output
    const int status = doc["status"];
    const char* hash = doc["hash"];
    global_hash = (char*)hash;
    
    bathalertFlag = false;

    Serial.println(json);
    
    // status
    if(status == 200){  // 200
      // pre-subloop2へ
      finishFlag = true;
      displayValues("WE HOPE YOUR", "HAPPY BATH!");
      delay(DISPLAY_TIME * 1000);
      break;
    }
    else{  // 400
      // deepsleep
      displayValues("Rebooting...", "");
      esp_deep_sleep(sleeping_time * 1000000LL);
    }
  }
}
