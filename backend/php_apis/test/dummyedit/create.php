<?php
// 受信
// $json_string = $_POST;
$json_string = file_get_contents('php://input');  // raw data

// JSONエンコードされた文字列をPHPの変数に
$contents = json_decode($json_string, true);


$link = new mysqli("DatabaseDomain", "DatabaseUser",
                   "DatabasePassword", "DatabaseName");
$link -> set_charset("utf-8");

$sql = "INSERT INTO bath_information (user_id, device_id, tag_id, checkin_time, checkout, bath_time, edited_time) VALUES ('"
       .$contents["user_id"]."', '"
       .$contents["device_id"]."', "
       .$contents["tag_id"].", '"
       .$contents["checkin_time"]."', "
       .$contents["checkout"].", "
       .$contents["bath_time"].", '"
       .$contents["edited_time"]."')";
$link -> query($sql);

// JSONにするArrayを作成
$results = array(
  "status" => 200
);
// 返信用JSONに変換
header("Content-type: application/json; charset=UTF-8");
$json = json_encode($results);

// JSONをreturn
print ($json);
?>
