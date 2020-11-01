<template>
  <v-row justify="center" align="stretch">
    <v-col cols="6">
      <v-card shaped color="amber lighten-2">
        <v-card-title>
          11月7日
        </v-card-title>
        <v-card-text>
          今日のお風呂は無事に終了しました．
        </v-card-text>
      </v-card>
    </v-col>
    <v-col cols="6">
      <v-card shaped color="amber lighten-2">
        <v-card-title>
          今日の入浴時間
        </v-card-title>
        <v-card-text>
          20:00 ~ 20:30
        </v-card-text>
      </v-card>
    </v-col>
    <v-col cols="12">
      <v-card shaped>
        <v-card-title>
          平均入浴時間
        </v-card-title>
        <v-card-text>
          45分
        </v-card-text>
        <BathChart />
      </v-card>
    </v-col>
  </v-row>
</template>

<script>
import BathChart from '~/components/BathChart'
export default {
  components: {
    BathChart,
  },
}
</script>

<style scoped>

</style>
