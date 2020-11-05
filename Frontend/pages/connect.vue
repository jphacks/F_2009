<template>
  <div>
    <v-row class="px-5 py-2">
      <v-col cols="12">
        <div class="text-h5 font-weight-black">接続設定</div>
      </v-col>
      <v-col cols="12">
        <div class="text-h6 font-weight-black">接続状態：</div>
        <div class="text-h6 font-weight-black mt-2">デバイス：{{isConnected}}</div>
        <v-btn class="mt-2" color="#3DB4BE" width="127" dark @click="removeConnect">接続の解除</v-btn>
      </v-col>

      <v-col cols="12" class="mt-5">
        <div class="text-h6 font-weight-black">STEP1：</div>
        <div class="text-h6 mt-2">デバイスを接続します。</div>
        <v-btn class="mt-2" color="#FFB304" width="127" dark @click="connectDevice">デバイスの接続</v-btn>
      </v-col>

      <v-col cols="12" v-if="is_connect">
        <div class="text-h6 font-weight-black">STEP2：</div>
        <div class="text-h6 mt-2">デバイスをWi-Fiと接続します。</div>
        <v-btn class="mt-2" color="#FFB304" width="127" dark @click="connectWifi">Wi-Fiの接続</v-btn>
      </v-col>
      <v-overlay
        :absolute="true"
        :value="overlay"
      >
        <qrcode-stream @decode="onDecode" @init="onInit" :style="{height: `${height}px`}"/>
      </v-overlay>
    </v-row>
  </div>
</template>

<script>
import { QrcodeStream } from 'vue-qrcode-reader'

export default {

  components: { QrcodeStream },

  data () {
    return {
      result: '',
      error: '',
      overlay: false,
      height: window.innerHeight - 64 - 46,
      is_connect: !!window.localStorage.getItem("user_id")
    }
  },

  methods: {
    onDecode (result) {
      this.result = result
      this.$axios.post("/users/create", {
        device_id: `${result}`
        })
        .then((res) => {
          const user_id = res.data.user_id
          window.localStorage.setItem('user_id', user_id)
          this.overlay = false
          this.is_connect = true
        })
        .catch((err) => {
          alert("デバイスと接続出来ませんでした。")
        })

    },

    async onInit (promise) {
      try {
        await promise
      } catch (error) {
        if (error.name === 'NotAllowedError') {
          this.error = "ERROR: you need to grant camera access permisson"
        } else if (error.name === 'NotFoundError') {
          this.error = "ERROR: no camera on this device"
        } else if (error.name === 'NotSupportedError') {
          this.error = "ERROR: secure context required (HTTPS, localhost)"
        } else if (error.name === 'NotReadableError') {
          this.error = "ERROR: is the camera already in use?"
        } else if (error.name === 'OverconstrainedError') {
          this.error = "ERROR: installed cameras are not suitable"
        } else if (error.name === 'StreamApiNotSupportedError') {
          this.error = "ERROR: Stream API is not supported in this browser"
        }
      }
    },
    connectDevice() {
      if (this.is_connect) {
        alert("すでに接続されています")
      }else {
        this.overlay = true
      }
    },
    removeConnect() {
      window.localStorage.removeItem('user_id')
      this.is_connect = false
    },
    connectWifi() {
      const url = "192.168.4.1"
      this.$axios.get(url)
        .then((res)=>{
          window.location.href = url
        })
        .catch((err) => {
          alert("専用wifiに接続してください")
        })
    }
  },
  computed: {
    isConnected() {
      if (this.is_connect) {
        return "接続済み"
      }else {
        return "未接続"
      }
    }
  }
}
</script>

<style scoped>
.error {
  font-weight: bold;
  color: red;
}
</style>
