<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS');

// LIMIT_LOGIN = 現在時刻　- 5 を導出
$limit_login = date("YmdHis", strtotime('-5 minute'));
// echo $limit_login

// 受信
$json_string = file_get_contents('php://input');  // raw data

// JSONエンコードされた文字列をArrayに
$contents = json_decode($json_string, true);

$link = new mysqli("DatabaseDomain", "DatabaseUser",
                   "DatabasePassword", "DatabaseName");
$link -> set_charset("utf8");

$sql = "SELECT * FROM device_information WHERE device_id='"
       .$contents['device_id']."'";
// echo $sql;

$res = $link -> query($sql);
$data = $res -> fetch_assoc();

if($data['sign_in'] == 1){
  $results = array(
    "status" => 400,
    "message" => "すでに割り当て済みのIoTデバイスです.",
  );
}
// echo (int)$data['device_connection_time'] - (int)$limit_login;
else if((int)$data['device_connection_time'] < (int)$limit_login){
  $results = array(
    "status" => 400,
    "message" => "IoTデバイスが接続されていません.",
  );
}
else{
  // 時刻の取得
  $now = new DateTime();
  $assigned_time = $now->format('YmdHis');

  // DB書き換え
  $sql = "UPDATE device_information SET sign_in=1, user_id='"
         .$contents['user_id']."', assigned_time='"
         .$assigned_time."' WHERE device_id='"
         .$contents['device_id']."'";
  // echo $sql;
  $link -> query($sql);

  // ハッシュ生成
  $user_hash = hash('sha256', $assigned_time);

  $results = array(
    "status" => 200,
    "hash" => $user_hash,
    "message" => "ユーザIDにデバイスを割り当てました.",
  );
}

// MySQLサーバの接続を切断
$link -> close;

// 返信用JSONに変換
header("Content-type: application/json; charset=UTF-8");
$json = json_encode($results, JSON_UNESCAPED_UNICODE);

// JSONをreturn
print($json);
?>
