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

/* ハッシュ確認 */
// DBにからログイン時間の取り出し, user_hash 生成
$sql = "SELECT assigned_time FROM device_information WHERE device_id='"
       .$contents["device_id"]."'";
$res = $link -> query($sql);
$time = $res -> fetch_assoc();
$user_hash = hash('sha256', $time["assigned_time"]);
// user_hash の比較
if (strcmp($contents["hash"], $user_hash) != 0){
  $results = array(
    "status" => 400,
  	"message" => "ID or ハッシュが間違っています."
  );
  header("Content-type: application/json; charset=UTF-8");
  $json = json_encode($results);
  print($json);

  $link -> close;
  exit();
}

// DB書き換え
$sql = "UPDATE device_information SET alert_time="
       .$contents['alert_time']." WHERE device_id='"
       .$contents['device_id']."' AND user_id='"
       .$contents['user_id']."'";
// echo $sql;
$link -> query($sql);

$results = array(
  "status" => 200,
  "message" => "アラート時間の更新に成功しました.",
);

// MySQLサーバの接続を切断
$link -> close;

// 返信用JSONに変換
header("Content-type: application/json; charset=UTF-8");
$json = json_encode($results, JSON_UNESCAPED_UNICODE);

// JSONをreturn
print($json);
?>
