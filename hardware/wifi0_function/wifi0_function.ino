/*
 * File:      wifi_function.ino
 * Function:  手動wifi設定
 * Date:      2020/11/04 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 */
// libraries
// Wi-Fi
#include <WiFi.h>
#include <HTTPClient.h>

// defines

// class
// Wi-Fi

// variables
// Wi-Fi
const char *ssid = "jupiter";
const char *password = "19740718";

// functions
// Wi-Fi
/* Wi-Fiに接続 */
void connectWifi(const char ssid[], const char password[]){
  while (!Serial);
  delay(100);
  
  Serial.print("start Wifi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
}


void setup() {
  // Serial connection speed
  Serial.begin(115200);

  // initiate
  
  // 例
  connectWifi(ssid, password);
  Serial.println("");
  Serial.println("Connected");
}
 
void loop() {}
