<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS');

// 時刻の取得
$now = new DateTime();
$time = $now->format('YmdHis');

// 受信
$json_string = file_get_contents('php://input');  // raw data

// JSONエンコードされた文字列をArrayに
$contents = json_decode($json_string, true);

$link = new mysqli("DatabaseDomain", "DatabaseUser",
                   "DatabasePassword", "DatabaseName");
$link -> set_charset("utf8");

// DEVICE_IDを検索する
$sql = "SELECT count(*) FROM device_information WHERE device_id='"
       .$contents['device_id']."'";
$res = $link -> query($sql);
$data = $res -> fetch_assoc();
if($data['count(*)'] == 0){
  $results = array(
    "status" => 400,
  	"message" => "デバイスIDが間違っています."
  );
  header("Content-type: application/json; charset=UTF-8");
  $json = json_encode($results);
  print($json);

  $link -> close;
  exit();
}

// 接続時間の更新
$sql = "UPDATE device_information SET device_connection_time='"
       .$time."' WHERE device_id='"
       .$contents['device_id']."'";
// echo $sql;
$link -> query($sql);

// device_information から sign_inを確認
$sql = "SELECT * FROM device_information WHERE device_id='"
       .$contents['device_id']."'";
$res = $link -> query($sql);
$data = $res -> fetch_assoc();
if($data['sign_in'] == 0){
  $results = array(
    "status" => 200,
    "substatus" => 0,
  	"message" => "接続に成功しました. ユーザアカウントが割り当てられていません. 30秒後に再確認を行います."
  );
  header("Content-type: application/json; charset=UTF-8");
  $json = json_encode($results);
  print($json);

  $link -> close;
  exit();
}

$user_id = $data['user_id'];
$alert_time = $data['alert_time'];
// hash生成
$hash = hash('sha256', $data['device_connection_time']);

// bath_information から checkoutを確認
$sql = "SELECT *, count(*) FROM bath_information WHERE device_id='"
       .$contents['device_id']."' AND checkout=0";
$res = $link -> query($sql);
$data = $res -> fetch_assoc();
if($data['checkout'] == 0 && $data['count(*)'] != 0){
  $results = array(
    "status" => 200,
    "substatus" => 1,
    "tag_id" => $data['tag_id'],
    "hash" => $hash,
    "alert_time" => $alert_time,
    "message" => "接続に成功しました. 入浴中です."
  );
}
else{
  $results = array(
    "status" => 200,
    "substatus" => 2,
  	"hash" => $hash,
    "user_id" => $user_id,
    "alert_time" => $alert_time,
  	"message" => "接続に成功しました."
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
