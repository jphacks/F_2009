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

/* ハッシュ確認 */
// DBにからログイン時間の取り出し, user_hash 生成
$sql = "SELECT * FROM device_information WHERE device_id='"
       .$contents["device_id"]."'";
$res = $link -> query($sql);
$data = $res -> fetch_assoc();
$user_hash = hash('sha256', $data["device_connection_time"]);
// user_hash の比較
if (strcmp($contents["hash"], $user_hash) != 0){
  $results = array(
    "status" => 400,
  	"message" => "デバイスID or ハッシュ値が間違っています."
  );
  header("Content-type: application/json; charset=UTF-8");
  $json = json_encode($results);
  print($json);

  $link -> close;
  exit();
}

// 新しい入浴情報を入れる
$sql = "INSERT INTO bath_information (user_id, device_id, tag_id, checkin_time, edited_time) VALUES ('"
       .$contents['user_id']."', '"
       .$contents['device_id']."', "
       .$contents['tag_id'].", '"
       .$time."', '"
       .$time."')";
$link -> query($sql);

// hash生成
$hash = hash('sha256', $time);

$results = array(
  "status" => 200,
  "hash" => $hash,
  "message" => "チェックインに成功しました."
);

// 接続時間の更新
$sql = "UPDATE device_information SET device_connection_time='"
       .$time."' WHERE device_id='"
       .$contents['device_id']."'";
$link -> query($sql);

// MySQLサーバの接続を切断
$link -> close;

// 返信用JSONに変換
header("Content-type: application/json; charset=UTF-8");
$json = json_encode($results, JSON_UNESCAPED_UNICODE);

// JSONをreturn
print($json);
?>
