<template>
  <v-card>
    <v-toolbar
      color="grey"
      dark
      flat
    >
      <template v-slot:extension>
        <v-tabs
          v-model="tabs"
          centered
        >
          <v-tab
            v-for="n in 4"
            :key="n"
          >
            {{n}}
          </v-tab>
        </v-tabs>
      </template>
    </v-toolbar>

    <v-tabs-items v-model="tabs">
      <v-tab-item>
        <v-card flat>
          <v-card-title class="headline">
            デバイス接続方法
          </v-card-title>
          <v-card-text>
            <img src="~/static/device.png" width="220px" height="350px"><br><br>
            <div class="step">STEP1：接続ボタンをタップするとQRコードリーダーが立ち上がります。デバイスのQRコードを読み取って下さい。</div><br>
          </v-card-text>
        </v-card>
      </v-tab-item>
      <v-tab-item>
        <v-card flat>
          <v-card-title class="headline">
            Wi-Fi接続方法
          </v-card-title>
          <v-card-text>
            <img src="~/static/wifi.png" width="220px" height="350px"><br><br>
            <div class="step">STEP2：デバイスとスマートフォンをWi-Fiで接続してください。</div><br>
            <div class="sentence"><br>Wifi設定画面で"OnDemand AP"を選んで下さい。</div><br>
            <img src="~/static/wifi2.png" width="220px" height="350px"><br>
            <div class="sentence"><br>Configure WIFIを選択してください。</div><br>
            <img src="~/static/wifi3.png" width="220px" height="350px"><br>
            <div class="sentence"><br>SSIDとパスワードを入力して接続して下さい。</div><br>
            <img src="~/static/wifi4.png" width="220px" height="350px"><br>
            <div class="sentence"><br>次の文が表示されます。</div><br>
            <img src="~/static/wifi5.png" width="220px" height="350px"><br>
            <div class="sentence"><br>スマートフォンを元のWi-Fiに接続し、以下の画面となれば接続完了です。</div><br>
            <img src="~/static/connect.png" width="220px" height="350px"><br>
          </v-card-text>
        </v-card>
      </v-tab-item>
      <v-tab-item>
        <v-card flat>
          <v-card-title class="headline">
            ホーム画面の見方
          </v-card-title>
          <v-card-text>
            <img src="~/static/bath2.png" width="220px" height="350px"><br>
            <div>①：今日の日付です</div>
            <div>②：今日の入浴状況です</div>
            <div>③：今日の入浴時間が表示されます</div>
            <div>④：一週間の平均入浴時間が表示されます</div>
            <div>⑤：一週間の変化が見られます</div>
            <br>
            <div>入浴中</div><br>
            <img src="~/static/bath4.png" width="220px" height="350px"><br>
            <div>警告時</div><br>
            <img src="~/static/bath3.png" width="220px" height="350px"><br>
            <div>入浴終了時</div><br>
            <img src="~/static/bath1.png" width="220px" height="350px"><br>
          </v-card-text>
        </v-card>
      </v-tab-item>
      <v-tab-item>
        <v-card flat>
          <v-card-title class="headline">
            通知
          </v-card-title>
          <v-card-text>
            <img src="~/static/notif.png" width="220px" height="350px"><br>
            <div class="tsuchi">通知設定：お風呂の出入り時に通知したいか選べます。</div>
            <div class="tsuchi">通報設定：緊急時に通報するか選べます。</div>
          </v-card-text>
        </v-card>
      </v-tab-item>
    </v-tabs-items>
  </v-card>
</template>

<script>
  export default {
    data () {
      return {
        tabs: null,
      }
    },
  }
</script>

<style scoped>
img {
   display: block;
    margin-left: auto;
    margin-right: auto
}
div {
  font-size: 14pt;
}
.step {
  margin-left: 4em;
  text-indent: -4em;
}
.sentence {
    margin-left: 2em;
    text-indent: -2em;
    padding: 18pt;
}
.tsuchi {
  margin-left: 5em;
  text-indent: -5em;
}
</style>
