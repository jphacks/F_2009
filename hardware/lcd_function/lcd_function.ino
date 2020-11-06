/*
 * File:      lcd_function.ino
 * Function:  LCDに受信情報を表示します。
 * Date:      2020/11/04 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 *            ブレッドボードに上記開発ボードとLCD、LEDを配線
 *            LCD: https://akizukidenshi.com/catalog/g/gK-08896/
 *                 16 × 2
 */
// libraries
// LCD
#include <Wire.h>  // I2C interface
#include<i2clcd.h> // i2clcdライブラリのヘッダ・ファイルを読み込む

// defines
// LCD
#define DISPLAY_TIME 0.5

// class
// LCD
i2clcd qlcd(0x3E, 3, 0x20);

// variables

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
  
  delay(DISPLAY * 1000);
}

void setup() {
  // Serial connection speed
  Serial.begin(115200);

  // initiate
  // LCD
  qlcd.init_lcd();  // LCDモジュール初期化
}

void loop() {
  // 例
  displayValues("9/12", "Yuritan Birthday");
}
