<script>
import { Bar, mixins } from 'vue-chartjs';

export default {
  extends: Bar,
  // mixins: [mixins.reactiveProp],
  name: 'chart',
  props: {
    chartLabel: {
      type: Array,
    },
    chartData: {
      type: Array,
    },
    update: {
      type: Array
    }
  },
  data () {
    return {
      data: {
        labels: this.chartLabel,
        datasets: [
          {
            label: '入浴時間',
            data: this.chartData,
            borderColor: '#CFD8DC',
            fill: false,
            type: 'line',
            lineTension: 0.3,
          },
          {
            label: '入浴時間',
            data: this.chartData,
            backgroundColor: '#FFB304',
            borderColor: 'rgba(255, 159, 64, 1)',
            borderWidth: 1
          },
        ]
      },
      options: {
        legend: false,
        scales: {
          xAxes: [{
            scaleLabel: {
              display: false,
              labelString: '日付'
            }
          }],
          yAxes: [{
            ticks: {
              beginAtZero: true,
              stepSize: 10,
              callback: function(value, index, values) {
                  return `${value}分`
              }
            },
          }]
        }
      }
    }
  },
  watch: {
    chartLabel () {
      this.$data._chart.update()
    },
    chartData () {
      this.$data._chart.update()
    },
    update () {
      this.$data._chart.update()
    }
  },
  mounted () {
    this.renderChart(this.data, this.options)
  },
}
</script>
