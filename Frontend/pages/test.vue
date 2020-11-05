<template>
    <dev class="main">
        <p>接続設定</p>
        <dev>現在接続中：</dev>
        <br><br>
        <dev>WiFi：</dev>
        <br><br>
        <dev>デバイス：</dev>
        <br><br><br>

        <p>STEP1</p>
        <dev>デバイスを接続します</dev>
        <br>
        <v-btn color="primary" elevation="2"
               @click="cameraStart();readImage();">
               デバイスの接続</v-btn>
    </dev>
</template>

<script>
import jsQR from "jsQR";
import * as ZXing from '@zxing/library'

export default {
  name: "Qr",
  data() {
    return {
      srcObject: "",
      width: 500,
      height: 500,
      json: null
    };
  },
  computed: {
    isReadQr: () => {
      return Boolean(this.json);
    }
  },
  methods: {
    cameraStart() {
      const p = navigator.mediaDevices.getUserMedia({
        audio: false,
        video: {
          width: this.width,
          height: this.height,
          frameRate: { ideal: 5, max: 15 }
        }
      });
      p.then(function(mediaStream) {
        document.querySelector("video").srcObject = mediaStream;
      });
    },
    readImage() {
      const video = document.querySelector("video");
      const canv = document.createElement("canvas");
      canv.height = this.height;
      canv.width = this.width;

      const context = canv.getContext("2d");

      setInterval(() => {
        console.log("search .....");
        context.drawImage(video, 0, 0, this.width, this.height);
        const imageData = context.getImageData(0, 0, this.width, this.height);
        const code = jsQR(imageData.data, imageData.width, imageData.height);
        if (code) {
          console.log("Found QR code", code, code.data);
          this.json = code.data;
        }
      }, 500);
    }
  }
};
</script>

<style scoped>
* {
    font-size: 15pt;
    margin: 5pt;
}
.main > p {
    font-size: 18pt;
    font-weight: 1000;
}

</style>