/*
 * File:      distance_function.ino
 * Function:  直線距離を測定します。
 * Date:      2020/11/04 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 *            HC-SR04
 */
// libraries
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>   

// defines
// Distance
#define Trigger_Pin 17
#define Echo_Pin 16

// class

// variables

// functions
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


void setup() {
  // Serial connection speed
  Serial.begin(115200);

  // initiate
  // Distance
  pinMode(Trigger_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT);
  digitalWrite(Trigger_Pin, LOW);
}
void loop() {
  // 例
  double Distance = getDistance();
  Serial.print("Distance:");
  Serial.print(Distance);
  Serial.println(" cm");
  delay(1000);
}
