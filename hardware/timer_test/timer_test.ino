/*
 * File:      timer_test.ino
 * Function:  時間計測
 * Date:      2020/11/04 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 */
// libraries

// defines

// class

// variables

// functions


void setup() {
  // Serial connection speed
  Serial.begin(115200);

  // initiate
    
}
 
void loop() {
  // 例
  // 初期化
  int prevent_time = millis();
  int current_time = 0;
  int diff_time = 0;
  // タイマ部
  while(true){
    current_time = millis();
    diff_time = current_time - prevent_time;
    prevent_time = current_time;

    Serial.print("current: ");
    Serial.println(current_time / 1000);
    Serial.print("diff: ");
    Serial.println(diff_time / 1000);
    Serial.println("");

    delay(5000);
  }
}
