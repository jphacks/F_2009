<?php
// 受信
// $_GET["xxx"]で取得可能


$link = new mysqli("DatabaseDomain", "DatabaseUser",
                   "DatabasePassword", "DatabaseName");
$link -> set_charset("utf-8");

$sql = "DELETE FROM bath_information WHERE device_id='"
       .$_GET['device_id']."' AND bath_id="
       .$_GET['bath_id'];
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
