/*
 * File:      buzzer_function.ino
 * Function:  音を鳴らします。
 * Date:      2020/11/04 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 *            圧電ブザー
 */
// libraries

// defines
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

// class

// variables

// functions
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

void setup() {
  // Serial connection speed
  Serial.begin(115200);

  // initiate
  // buzzer
  ledcSetup(1, 12000, 8);
  ledcAttachPin(BUZZER_PIN, 1);
}
void loop() {
  callAlert();
}
