# 安心ふろ〜（IoTデバイス）
## 製品概要
### 画像（設置後の様子）
![IoT Device](https://user-images.githubusercontent.com/49345024/98411801-10a22600-20ba-11eb-8396-64ec01ce0d45.jpg)

### IoTデバイスの役割
1. 入浴時間を監視・Webサーバ（PHP・DBサーバ）上に記録すること
2. 危険時の状況を検出すること

### IoTデバイスの機能
入浴時間をウェブ上に記録することができます。 \
距離センサやRFIDリーダを用いて、ユーザの行動を読み取り、ブザーと入力機器を用いてユーザとコミュニケーションをとることも可能です。

### デプロイ方法
1. Arduino IDEをインストールし, ESP32のボードマネージャを導入する. \
2. 下記の物品リストを揃える. \
3. 下記回路図の通り, ブレッドボード上に回路を組む. \
4. 下記外部ライブラリをArduinoメインフォルダのlibrariesに設置（その他ライブラリエラーが発生する場合はArduino IDE内部のライブラリマネージャよりライブラリのインストールが必要）. \
5. リポジトリ内の**integration.ino** をボードに書き込む
6. 浴室と更衣室を繋ぐ扉の横に設置する. \
   この際物品リストにある魔法のテープを利用すると壁紙部以外では後も残らず, 強力で安定した設置が可能となる.

### プログラム解説
integration.inoがデプロイ用プログラムです。その他のプログラムは単体テストを実施したものです。各関数について詳細を確認したい場合は確認してみてください。

## 設計
### 簡易版フローチャート
![フローチャート_簡易](https://user-images.githubusercontent.com/49345024/98449897-26c3eb00-217b-11eb-8ee8-8c8841878b32.png)

### 回路図
![回路図](https://user-images.githubusercontent.com/49345024/98411871-30d1e500-20ba-11eb-8048-7a1ccf5b606c.jpg)

### 物品リスト
https://www.notion.so/72437c29007544b48976c7b452898bb6?v=5f4ae2c5bcf64ef59f31a0458f2d1865

### 外部ライブラリ（Arduino）
wifimanager: https://github.com/zhouhan0126/WIFIMANAGER-ESP32 \
i2clcd: https://www.denshi.club/cookbook/arduino/esp32/esp32-7-i2clcd.html

### 補足資料（フローチャート完全版）
![フローチャート](https://user-images.githubusercontent.com/49345024/98411852-244d8c80-20ba-11eb-8cf8-9a81edf446f5.jpg)
