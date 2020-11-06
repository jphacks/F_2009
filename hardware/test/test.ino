#include <WiFi.h>          //https://github.com/esp8266/Arduino
#include <WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
// JSON
#include <ArduinoJson.h>
#include <HTTPClient.h>

// JSON
// API Domain
const char *url = "http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/";

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    // is configuration portal requested?
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

    /*
    //if you get here you have connected to the WiFi
    IPAddress ipadr = WiFi.localIP();
    
    Serial.println("connected(^^)");
    Serial.println("local ip");
    Serial.println(ipadr);
    Serial.println(WiFi.SSID());
    */
}

void loop() {
  // put your main code here, to run repeatedly:
  // 例
  // JSONオブジェクト作成
  const int capacity = JSON_OBJECT_SIZE(1);  // JSONオブジェクトの要素数
  StaticJsonDocument<capacity> json_request;
  // JSON構造化
  json_request["device_id"] = "test1test2test3test4";
  
  // json_request.stringify -> buffer
  char buffer[255];
  serializeJson(json_request, buffer, sizeof(buffer));
  
  // API指定
  char *api = "test/test_post_receive";
  
  // Serial.println(buffer);
  
  // HTTP POST
  String json = jsonPost(url, api, buffer);
  
  // Serial.println(json);
  
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
