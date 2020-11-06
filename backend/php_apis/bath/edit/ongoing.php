<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS');

// 時刻の取得
$now = new DateTime();
$time = $now -> format('YmdHis');
$timestamp = $now -> getTimestamp();

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

// 入浴データの取り出し
$sql = "SELECT * FROM bath_information WHERE device_id='"
       .$contents['device_id']."' AND tag_id="
       .$contents['tag_id']." AND checkout=0";
$res = $link -> query($sql);
$data = $res -> fetch_assoc();

// 時間差の計算 time(now) - checkin_time
$strtotime = substr($data['checkin_time'], -14, -10).'-'
             .substr($data['checkin_time'], -10, -8).'-'
             .substr($data['checkin_time'], -8, -6).' '
             .substr($data['checkin_time'], -6, -4).':'
             .substr($data['checkin_time'], -4, -2).':'
             .substr($data['checkin_time'], -2);
$checkin_time = strtotime($strtotime);
$diff_minute = ($timestamp - $checkin_time) / 60;

// bath_time, edited_timeの更新
$sql = "UPDATE bath_information SET bath_time="
       .$diff_minute.", edited_time='"
       .$time."' WHERE device_id='"
       .$contents['device_id']."' AND checkout=0";
// echo $sql;
$link -> query($sql);

// hashの計算
$hash = hash('sha256', $time);

$results = array(
  "status" => 200,
  "hash" => $hash,
  "message" => "入浴継続登録に成功しました."
);

// IoTデバイス接続時間の更新
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
