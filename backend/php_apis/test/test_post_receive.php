<?php
// 受信
// $json_string = $_POST;
$json_string = file_get_contents('php://input');  // raw data

// echo "JSON: ".$json_string."<br>";

// JSONエンコードされた文字列をPHPの変数に
$contents = json_decode($json_string, true);
// echo "Array: ".$contents."<br>";
// echo "Array key[key1]: ".$contents["key1"]."<br>";

// 返信用JSON作成
$results = array(
  "key1" => $contents["key1"],
  "key2" => $contents["key2"],
  "box1" => array(
    "key1-1" => $contents["box1"]["key1-1"]
  )
);
$results = array(
  "key1" => $contents["device_id"],
  "key2" => "key2",
  "box1" => array(
    "key1-1" => 111
  )
);

// 詳細確認用
// var_dump($contents);

header("Content-type: application/json; charset=UTF-8");
$json = json_encode($results);

// print($json_string)
// print($contents);  // _rだとArrayの中身まで表示(_rは詳細に出力)
print ($json);
?>
