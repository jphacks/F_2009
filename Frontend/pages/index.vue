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
          {{ meanBathTime }}分
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
  data() {
    return {
      status: null,
      bath_time : {
        taking_bath_time: {hour: null, minutes: null},
        entry_bath_time: {hour: null, minutes: null},
        exit_bath_time: {hour: null, minutes: null},
      },
      history: null,
      mean_bath_time: null
    }
  },
  created() {
    this.$OneSignal.push(['addListenerForNotificationOpened', (data) => {
      console.log('Received NotificationOpened:', data )}
    ]);
  },
  mounted() {
    this.$axios.get("/status")
      .then((res) => {
        const status = res.data.status
        const entry_time = res.data.entry_time
        const diff = this.dateFromEntry(entry_time)
        const {hour, minutes} = this.dateToHourMinutes(diff)
        console.log(hour + "時間")
        console.log(minutes + "分")
      })
    this.$axios.get("/history/week")
      .then((res) => {
        console.log(res.data.history)
      })
  },
  methods: {
    dateToHourMinutes(date) {
      const hour = Math.floor(date/3600000)
      const minutes = Math.floor((date%3600000)/60000)
      return {hour, minutes}
    },
    dateFromEntry(date) {
      const now = new Date()
      const diff = now - Date.parse(date)
      return diff
    }
  },
  computed: {
    // meanBathTime: function() {
    //   const sum = this.week_bath_time.reduce((prev, current, i, arr) => {
    //     return prev+current;
    //   });
    //   return sum/this.week_bath_time.length
    // }
  }
}
</script>

<style scoped>

</style>
