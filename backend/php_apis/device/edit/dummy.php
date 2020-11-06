<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS');

// 受信
$json_string = file_get_contents('php://input');  // raw data

// JSONエンコードされた文字列をArrayに
$contents = json_decode($json_string, true);

$link = new mysqli("DatabaseDomain", "DatabaseUser",
                   "DatabasePassword", "DatabaseName");
$link -> set_charset("utf8");

// 時刻の取得
$now = new DateTime();
$time = $now->format('YmdHis');

$sql = "SELECT count(*) FROM device_information WHERE device_id='"
       .$contents['device_id']."'";
$res = $link -> query($sql);
$data = $res -> fetch_assoc();
if($data['count(*)'] == 0){
  $results = array(
    "status" => 400,
    "message" => "指定したIoTデバイスが存在しません."
  );
  header("Content-type: application/json; charset=UTF-8");
  $json = json_encode($results, JSON_UNESCAPED_UNICODE);
  print($json);

  $link -> close;
  exit();
}

// DB書き換え
$sql = "UPDATE device_information SET device_connection_time='"
       .$time."' WHERE device_id='"
       .$contents['device_id']."'";
// echo $sql;
$link -> query($sql);

$results = array(
  "status" => 200,
  "message" => "指定したIoTデバイスの接続時間を更新しました.",
);

// MySQLサーバの接続を切断
$link -> close;

// 返信用JSONに変換
header("Content-type: application/json; charset=UTF-8");
$json = json_encode($results, JSON_UNESCAPED_UNICODE);

// JSONをreturn
print($json);
?>
