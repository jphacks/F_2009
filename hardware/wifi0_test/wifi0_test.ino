/*
 * File:      wifi0_test.ino
 * Function:  Wi-Fi接続とJSON送受信のテスト
 * Date:      2020/11/04 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 */
// libraries
// Wi-Fi
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// defines

// class
// Wi-Fi
WiFiMulti wifiMulti;

// variables
// Wi-Fi
const char *ssid = "jupiter";
const char *password = "19740718";
const int capacity = JSON_OBJECT_SIZE(2);  // JSONオブジェクトの要素数
StaticJsonDocument<capacity> json_request;
char buffer[255];
const char *host = "http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/test/test_post_receive";

const char *device_id = "test1test2test3test4";

// functions

void setup() {
  // Serial connection speed
  Serial.begin(115200);

  // initiate
  // Wi-Fi
  while (!Serial);
  delay(100);
  
  Serial.print("start Wifi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("");
  Serial.println("Connected");
}
 
void loop() {
  json_request["device_id"] = device_id;

  serializeJson(json_request, Serial);
  Serial.println("");

  // json_request.stringify -> buffer
  serializeJson(json_request, buffer, sizeof(buffer));

  HTTPClient http;
  http.begin(host);
  http.addHeader("Content-Type", "application/json");
  int status_code = http.POST((uint8_t*)buffer, strlen(buffer));
  // Serial.printf("status_code=%d\r\n", status_code);
  if( status_code == 200 ){
    // JSON取得
    String json = http.getString();
    Serial.println(json);  // レスポンスのJSON
    StaticJsonDocument<200> doc;
    // JSONパース
    deserializeJson(doc, json);
    // Output
    const char* word1 = doc["key1"];
    const char* word2 = doc["key2"];
    const int word3 = doc["box1"]["key1-1"];
    Serial.println(word1);
    Serial.println(word2);
    Serial.println(word3);
  }
  http.end();

  delay(5000);
}
