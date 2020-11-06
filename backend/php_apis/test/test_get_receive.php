<?php
// 受信

// 返信用JSON作成
// JSONにするArrayを作成
$results = array(
  "key1" => $_GET["test1"],
  "key2" => $_GET["test2"],
);
// 返信用JSONに変換
header("Content-type: application/json; charset=UTF-8");
$json = json_encode($results);

// JSONをreturn
print ($json);
?>
