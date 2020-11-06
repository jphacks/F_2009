/*
 * File:      json_function.ino
 * Function:  JSON送受信
 * Date:      2020/11/04 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 */
// libraries
// JSON
#include <ArduinoJson.h>
// Wi-Fi
#include <WiFi.h>
#include <HTTPClient.h>

// defines

// class

// variables
// JSON
// API Domain
const char *url = "http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/";
// Wi-Fi
const char *ssid = "jupiter";
const char *password = "19740718";

// functions
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
  // 例
  // JSONオブジェクト作成
  const int capacity = JSON_OBJECT_SIZE(2);  // JSONオブジェクトの要素数
  StaticJsonDocument<capacity> json_request;
  // JSON構造化
  json_request["device_id"] = "test1test2test3test4";

  // これ出力？
  // serializeJson(json_request, Serial);
  // Serial.println("");
  
  // json_request.stringify -> buffer
  char buffer[255];
  serializeJson(json_request, buffer, sizeof(buffer));
  
  // API指定
  char *api = "test/test_post_receive";

  // HTTP POST
  String json = jsonPost(url, api, buffer);
  
  // JSON格納変数作成
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

  delay(5000);
}
