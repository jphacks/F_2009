<?php
// API URL設定
$workspace = "https://kn46itblog.com/hackathon/VRHack20200723";
$api = "/php_apis/getRanking.php";  // APIの指定
$getQ = "";
$url = $workspace.$api.$getQ;

echo "Sent GET Query: ".$getQ."<br>";

// ストリームコンテキストのオプションを作成
$options = array(
// HTTPコンテキストオプションをセット
  'http' => array(
    'method'=> 'GET',
    'header'=> 'Content-type: application/json; charset=UTF-8', //JSON形式で表示
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
echo $contents."<br/><br/>";
$contents = json_decode($contents, true);
echo "returned Array:";
print_r($contents);
?>
