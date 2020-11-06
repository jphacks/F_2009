<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS');

// 受信
$json_string = file_get_contents('php://input');  // raw data

// JSONエンコードされた文字列をArrayに
$contents = json_decode($json_string, true);

if($contents['limit_day'] != 0){
  // LIMIT_TIME = 現在時刻　- LIMIT_DAY を導出
  $strtotime = '-'.$contents['limit_day'].' day';
  // 時刻の取得
  $limit_time = date("YmdHis", strtotime($strtotime));
}

$link = new mysqli("DatabaseDomain", "DatabaseUser",
                   "DatabasePassword", "DatabaseName");
$link -> set_charset("utf8");

/* ハッシュ確認 */
// DBにからログイン時間の取り出し, user_hash 生成
$sql = "SELECT * FROM device_information WHERE device_id='"
       .$contents["device_id"]."'";
$res = $link -> query($sql);
$data = $res -> fetch_assoc();
$user_hash = hash('sha256', $data["assigned_time"]);
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
// IoTデバイス割り当て確認
else if($data['sign_in'] == 0){
  $results = array(
    "status" => 400,
    "message" => "指定されたIoTデバイスは現在割り当てられていません."
  );
  header("Content-type: application/json; charset=UTF-8");
  $json = json_encode($results);
  print($json);

  $link -> close;
  exit();
}

// LIMIT_NUM, LIMIT_DAYからSQL文作成
if($contents["limit_num"] == 0 && $contents["limit_day"] == 0){
  $sql = "SELECT tag_id, checkin_time, checkout, bath_time FROM bath_information WHERE device_id='"
         .$contents["device_id"]."' AND user_id='"
         .$contents["user_id"]."' ORDER BY checkin_time DESC";
}
// day
else if($contents["limit_num"] == 0 && $contents["limit_day"] > 0){
  $sql = "SELECT tag_id, checkin_time, checkout, bath_time FROM bath_information WHERE device_id='"
         .$contents["device_id"]."' AND user_id='"
         .$contents["user_id"]."' AND edited_time>"
         .$limit_time." ORDER BY checkin_time DESC";
}
// num
else if($contents["limit_num"] > 0 && $contents["limit_day"] == 0){
  $sql = "SELECT tag_id, checkin_time, checkout, bath_time FROM bath_information WHERE device_id='"
         .$contents["device_id"]."' AND user_id='"
         .$contents["user_id"]."' ORDER BY checkin_time DESC LIMIT "
         .$contents["limit_num"];
}
// day & num
else if($contents["limit_num"] > 0 && $contents["limit_day"] > 0){
  $sql = "SELECT tag_id, checkin_time, checkout, bath_time FROM bath_information WHERE device_id='"
         .$contents["device_id"]."' AND user_id='"
         .$contents["user_id"]."' AND edited_time>"
         .$limit_time." ORDER BY checkin_time DESC LIMIT "
         .$contents["limit_num"];
}
// echo $sql;

$res = $link -> query($sql);
$results = array(
  "status" => 200,
  "grandma_list" => array(),
  "gramdpa_list" => array(),
  "message" => "入浴情報一覧の取得に成功しました.",
);
while($data = $res -> fetch_assoc()){
  $data_array = array(
    "checkin_time" => $data['checkin_time'],
		"checkout" => $data['checkout'],
		"bath_time" => $data['bath_time']
  );

  // listのルーティング
  // gramdma
  if($data['tag_id'] == 0){
    $results['grandma_list'] = array_merge($results["grandma_list"], array($data_array));
  }
  // grandpa
  else if($data['tag_id'] == 1){
    $results['grandpa_list'] = array_merge($results["grandpa_list"], array($data_array));
  }
}

// MySQLサーバの接続を切断
$link -> close;

// 返信用JSONに変換
header("Content-type: application/json; charset=UTF-8");
$json = json_encode($results, JSON_UNESCAPED_UNICODE);

// JSONをreturn
print($json);
?>
