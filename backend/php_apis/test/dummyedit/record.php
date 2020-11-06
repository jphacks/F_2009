<!DOCTYPE html>
<head>
  <meta charset="utf-8">
  <title>安心ふろ〜 Record</title>
</head>
<body>
  <?php
      session_start();
      if(!isset($_GET['reload_id']) && isset($_SESSION['reload_id'])){
        $_GET['reload_id'] = $_SESSION['reload_id'];
      }
      if(isset($_POST['create'])){
        $_POST['create'] = NULL;
        // 初期note取得
        $workspace = "http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/";
        $api = "test/dummyedit/create.php";  // APIの指定
        $url = $workspace.$api;
        // JSON
        $data = array(
          "user_id" => $_POST['user_id'],
          "device_id" => $_POST['device_id'],
        	"tag_id" => $_POST['tag_id'],
          "checkin_time" => $_POST['checkin_time'],
          "checkout" => $_POST['checkout'],
          "bath_time" => $_POST['bath_time'],
        	"edited_time" => $_POST['edited_time']
        );

        // JSON形式に変換
        $data = json_encode($data);

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
        $context = stream_context_create($options);
        // GET送信
        $contents = file_get_contents($url, false, $context);
        // APIのレスポンスをArrayに変換, note情報が格納されている
        $json_arr = json_decode($contents, true);
      }
      if(isset($_POST['delete'])){
        $_POST['delete'] = NULL;
        // 初期note取得
        $workspace = "http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/";
        $api = "test/dummyedit/resetDatabase.php";  // APIの指定
        $query = "?device_id=".$_POST['reset_id']."&bath_id=".$_POST['bath_id'];
        $url = $workspace.$api.$query;
        // echo $url;

        // ストリームコンテキストのオプションを作成
        $options = array(
            // HTTPコンテキストオプションをセット
            'http' => array(
                'method' => 'GET',
                'header' => 'Content-type: application/json; charset=UTF-8', //JSON形式で表示
            )
        );
        // ストリームコンテキストの生成
        $context = stream_context_create($options);
        // GET送信
        $contents = file_get_contents($url, false, $context);
        // APIのレスポンスをArrayに変換, note情報が格納されている
        $json_arr = json_decode($contents, true);
      }
      if(isset($_POST['reload'])){
        $_SESSION['reload_id'] = $_POST['reload_id'];
        $Location = "Location: ./record.php?reload_id=".$_POST['reload_id'];
        $_POST['reload_id'] = NULL;
        header($Location);
      }
  ?>
  <form action="" method="post">
    <div>新規のデータを入力する場合はこちらからデータを指定して記録してください.</div>
    <label for="user_id">user id</label>
    <input type="text" name="user_id"><br>
    <label for="device_id">device id</label>
    <input type="text" name="device_id"><br>
    <label for="tag_id">tag id</label>
    <input type="text" name="tag_id"><br>
    <label for="checkin_time">checkin time -> 14桁連数 ex.)20200619102000</label>
    <input type="text" name="checkin_time"><br>
    <label for="checkout">checkout -> 0 or 1</label>
    <input type="text" name="checkout"><br>
    <label for="bath time">bath time -> minute</label>
    <input type="text" name="bath_time"><br>
    <label for="edited_time">edited time -> 14桁連数</label>
    <input type="text" name="edited_time"><br>

    <input type="submit" name="create" value="記録する" /><br><br>

    <div>削除するデータの入浴IDとデバイスIDを指定してください</div>
    <label for="bath_id">入浴ID</label>
    <input type="text" name="bath_id"><br>
    <label for="reset_id">デバイスID</label>
    <input type="text" name="reset_id"><br>
    <input type="submit" name="delete" value="記録のリセット" /><br><br>

    <div>reload idで指定したデバイスでリストを表示します. 一度指定すればキャッシュで管理できます(上書き可能).</div>
    <label for="reload_id">reload id</label>
    <input type="text" name="reload_id"><br>
    <input type="submit" name="reload" value="リロード" />
  </form>
  <?php
    // リストの表示
    echo "<table border='1'>";
    echo "<tr><td>入浴ID</td><td>ユーザID</td><td>デバイスID</td><td>タグID</td><td>チェックイン時間</td><td>チェックアウト</td><td>入浴時間</td><td>最終編集時間</td></tr>";
    $link = new mysqli("DatabaseDomain", "DatabaseUser",
                       "DatabasePassword", "DatabaseName");
    $link -> set_charset("utf-8");

    $sql = "SELECT * FROM bath_information WHERE device_id='"
           .$_GET['reload_id']."'";
    // echo $sql;
    $res = $link -> query($sql);
    while($data = $res -> fetch_assoc()){
      echo "<tr>";
      echo "<td>".$data["bath_id"]."</td><td>".$data["user_id"]."</td><td>".$data["device_id"]."</td><td>".$data["tag_id"]."</td><td>".$data["checkin_time"]."</td><td>".$data["checkout"]."</td><td>".$data["bath_time"]."</td><td>".$data["edited_time"]."</td>";
      echo "</tr>";
    }
    echo "</table>";
  ?>
</body>
</html>
