<?php
// API URL設定
$workspace = "http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/";
$api = "device/edit/connection";  // APIの指定
// $api = "bath/edit/checkout";  // APIの指定
// $api = "test/test_post_receive";
$url = $workspace.$api;

// JSONにするオブジェクトの構成例
$data = array(
  "prm1" => 1,
  "prm2" => "value2",
  "arr1" => array(
    "prm1" => "parm_arr1-1"
  )
);
// JSON
$data = array(
  "device_id" => "test",
	"user_id" => "_test",
  "alert_time" => 21,
	"hash" => "760551d18f24b11ce7bff9cd7cf46a7c8666f17e180d81e2e8106a5c9fd4b4c0",
);

echo "Before Encoded Sent JSON: ".$data."<br>";

// JSON形式に変換
$data = json_encode($data);
echo "Encoded Sent JSON: ".$data."<br>";

// ストリームコンテキストのオプションを作成
$options = array(
// HTTPコンテキストオプションをセット
  'http' => array(
    'method'=> 'POST',
    'header'=> 'Content-type: application/json; charset=UTF-8', //JSON形式で表示
    'content' => $data
  )
);

// ストリームコンテキストの生成
// ストリーム
// -> I/Oデータをプログラムで扱えるよう抽象化したもの
//    -> 抽象化の過程でストリームラッパーが用いられる
$context = stream_context_create($options);

// POST送信
$contents = file_get_contents($url, false, $context);

// reception.php のレスポンスを表示
echo "returned JSON:";
echo $contents."<br>";
$contents = json_decode($contents, true);
echo "returned Array:";
print_r($contents);
?>
