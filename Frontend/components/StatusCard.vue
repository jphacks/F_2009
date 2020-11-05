<template>
  <v-card :color="color" dark class="pa-5 d-flex align-center justify-center text-h5 font-weight-bold" height="100" >
    <span :class="{'taking-bath': status===1}">{{ message }}</span></span>
  </v-card>
</template>

<script>
export default {
  props: {
    status: {
      type: Number,
    },
  },

  data() {
    return {
    }
  },
  computed: {
    message: function() {
      switch(this.status) {
        case 0:
          return "今日はまだおふろに入っていません。"
        case 1:
          return "ただいま入浴中です。"
        case 2:
          return "今日のおふろは無事に終了しました。"
        case 3:
          return "平均入浴時間を大幅に超過しています！！"
      }
      return ""
    },
    color: function() {
      switch(this.status) {
        case 0:
          return "#FFB304"
        case 1:
          return "#FFF2DC"
        case 2:
          return "#3DB4BE"
        case 3:
          return "#E53A00"
      }
      return ""
    }
  }
}
</script>

<style scoped>
.taking-bath {
  color: #3DB4BE
}
</style>
