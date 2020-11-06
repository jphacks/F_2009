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
            <img src="~/static/device.png" width="220px" height="350px"><br>
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
            <img src="~/static/wifi.png" width="220px" height="350px"><br>
            <div class="step">STEP2：デバイスとスマートフォンを同じWi-Fiで接続してください。</div><br><br>
            <div class="step"><br>以下の画面になれば接続完了です。</div><br>
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
        text: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.',
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
.step {
  margin-left: 4em;
  text-indent: -4em;
}
.tsuchi {
  margin-left: 5em;
  text-indent: -5em;
}
</style>