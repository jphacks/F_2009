/*
 * File:      integration_model.ino
 * Function:  風呂危険検知IoTシステム
 * Date:      2020/11/05 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 * Software   Based on function programs
 * Model Note Move:
 *            going, pre-subloop2
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

  /* Setup */
  // 起動情報を表示
  // Wi-Fi接続
  // 接続完了を表示
  // 2秒待機
    
}
 
void loop() {
  // Subloop1
  while(){
    // connection
    // status
    if(){
      
    }
    else{
      // deepsleep
    }
    // substatus
    if(){  // 2
      // ハッシュ取得
      // break
    }
    else if(){  // 1
      // ongoingへ
    }
    else if(){  // 0
      // 情報表示
      // 30秒待機
    }
  }
  // Subloop1完了を表示
  // 2秒待機
  // 時間計測開始

  // Subloop2
  while(){
    // 距離センサを計測
    // distance
    if(){  // true
      // Bottomloop1
      while(){
        // 情報表示
        // ブザー
        // RFID READABLE
        if(){  // true
          // 情報表示
          // break
        }
      }
    }
    // READABLE
    if(){  // true
      // break
    }
    else{
      // second
      if(){  // true
        // 情報表示
        // 2秒待機
        // return
      }
    }
  }
  // チェックイン
  // チェックインを表示
  // 2秒待機

  // Subloop3
  while(){
    // 時間計測開始
    // Bottomloop1
    while(){
      // READABLE
      if(){  // true
        // same tag?
        if(){  // true
          // break
        }
        else{  // false
          // 情報表示
          // 時間計測
          // ブザー
          // 2秒非同期で待機
        }
      }
      // total second > 60 min (DANGER)
      if(){  // true
        // Bottomloop2
        while(){
          // 情報表示
          // ブザー
          // READABLE
          if(){  // true
            // break
          }
        }
        // 情報表示
        // 2秒待機
        // going
        // status
        if(){  // 200
          // 情報表示
          // 2秒待機
          // 周期時間リセット
        }
      }
      else{  // false
        // second > 300 (Cycle)
        if(){  // true
          // going
          // status
          if(){  // 200
            // 情報表示
            // 2秒待機
            // 周期時間リセット
          }
        }
      }
    }

    // checkout
    // status
    if(){  // 200
      // pre-subloop2へ
    }
    else{  // 400
      // deepsleep
    }
  }
}
