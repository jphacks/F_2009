# Backend
## PHP
### PHPサーバの役割
1. IoTデバイスからの情報を取得する.
2. IoTデバイスとユーザ端末の認証を行う.
3. Flaskサーバに記録情報の提供を行う.

### PHPバックエンドの仕様書
https://www.notion.so/30bea1832bd2475b9c1cf394def3b0fc

### DBの操作
ダミーデータの操作に関して \
php_apis/test/dummyedit/record.php \
より、新規登録・一部削除・一覧表示が可能です.

### 注意事項
mysqli関数に関する情報は機密情報なので, 置き換えて各環境に合わせて使用ください.

## Flask
### Flaskサーバの役割
1. PHPサーバから入浴出入り時刻等をを取得
2. ユーザ認証
3. フロントが必要なデータに形式に変換、計算し提供
4. 緊急状態の閾値計算及びPHPサーバの閾値を更新

### Flaskバックエンド仕様書
https://app.swaggerhub.com/apis/ToruTamahashi/AnshinFlow/1.0.1

### DB定義
https://docs.google.com/document/d/1dWd-h3xYZmDbBt_bg17s4Y6AS2Awkbuyp-e70gQ2x90/edit?usp=sharing

### 注意事項
mysql接続ユーザid,パスワード,host,port, onesignalのapiキー,rest apiキーはpython-dotenvという各環境で設定するようにして下さい.
