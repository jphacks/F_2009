<template>

  <v-row class="px-7 py-2">
    <v-col cols="12">
      <h1 class="amber--text text--darken-1">{{ getNowDate() }}</h1>
    </v-col>
    <v-col cols="12">
      <StatusCard :status="status" />
    </v-col>
    <v-col cols="12">
      <div class="text-h5 font-weight-black">今日の入浴時間</div>
      <h1 class="amber--text text--darken-1">
        {{ getTime(bath_time.entry_bath_time) }}
          ~
        {{ getTime(bath_time.exit_bath_time) }}
      </h1>
    </v-col>
    <v-col cols="12">
      <div class="text-h5 font-weight-black">平均入浴時間</div>
      <div class="text-body-1 font-weight-black">{{this.chart.label[0]}}~{{this.chart.label[6]}}</div>
      <h1 class="amber--text text--darken-1">{{ mean_bath_time }}分</h1>
    </v-col>
    <v-col cols="12">
      <BathChart :height="270" :chartData="chart.data" :chartLabel="chart.label" :update="chart.update" />
    </v-col>

    <v-overlay
      :absolute="true"
      :value="status===3"
      color="#E53A00"
    >
    </v-overlay>
  </v-row>
</template>

<script>
import BathChart from '~/components/BathChart'
import StatusCard from '~/components/StatusCard'
export default {
  components: {
    BathChart,
    StatusCard,
  },
  data() {
    return {
      status: 0,
      bath_time: {
        taking_bath_time: {hour: null, minutes: null},
        entry_bath_time: {hour: null, minutes: null},
        exit_bath_time: {hour: null, minutes: null},
      },
      chart: {
        data: [0, 0, 0, 0, 0, 0, 0],
        label: ['', '', '', '', '', '', ''],
        update: []
      },
      history: null,
      mean_bath_time: 0,
      alert: false,
    }
  },
  created() {
    this.$OneSignal.push(() => {
      this.$OneSignal.on('notificationDisplay', (event) => {
        this.updateData()
      })
    })
  },
  mounted() {
    this.updateData()
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
    },
    chageChartData() {
      this.chart.data[0] = Math.floor(Math.random() * Math.floor(10))
      this.chart.update = []
    },
    getTime: (time) => {
      if (time.hour == null){
        return ""
      }
      return time.hour+":"+time.minutes
    },
    getNowDate() {
      const now = new Date()
      return (now.getMonth() + 1)+'月'+(now.getDay()+1)+'日'
    },
    getUserId() {
      return window.localStorage.getItem("user_id")
    },
    updateData() {
      this.$axios.get("/status",  {
          headers: { "Authorization": `${this.getUserId()}` },
        })
        .then((res) => {
          const status = res.data.status
          let entry_time = res.data.entry_time
          let exit_time = res.data.exit_time
          this.status = status
          console.log(status)
          if (entry_time){
            entry_time = new Date(entry_time)
            this.bath_time.entry_bath_time.hour = entry_time.getHours()
            this.bath_time.entry_bath_time.minutes = entry_time.getMinutes()
          }
          if (exit_time){
            exit_time = new Date(exit_time)
            this.bath_time.exit_bath_time.hour = exit_time.getHours()
            this.bath_time.exit_bath_time.minutes = exit_time.getMinutes()
          }
        })
      this.$axios.get("/history/week", {
          headers: { "Authorization": `${this.getUserId()}` },
        })
        .then((res) => {
          const history = res.data.history
          const mean = res.data.mean
          this.mean_bath_time = mean
          history.map(x => x.date).forEach((ele, idx) => {
            const dateSplit = ele.split('-')
            this.chart.label[idx] = dateSplit[1]+'/'+dateSplit[2]
          })
          history.map(x => x.minute).forEach((ele, idx) => {
            this.chart.data[idx] = ele
          })
          this.chart.update = []
        })
    }

  },

}
</script>

<style scoped>

</style>
