/*
 * File:      wifispecial_function.ino
 * Function:  直線距離を測定します。
 * Date:      2020/11/06 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 */
// libraries
// Wi-Fi
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>     

// defines

// class

// variables

// functions
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


void setup() {
  // Serial connection speed
  Serial.begin(115200);

  // initiate

  // 例
  wifi_special_connection();

}
void loop() {
  
}
