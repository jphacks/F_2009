<template>
  <v-app style="
    background: #FFFFFB
  ">

    <v-app-bar
      :clipped-left="clipped"
      color="#9EA1A2"
      fixed
      dark
      app
    >
      <span>{{getTitle()}}</span>
    </v-app-bar>
    <v-main>
      <v-container>
        <nuxt />
      </v-container>
    </v-main>

    <!--
    <v-bottom-navigation
      v-model="value"
      class="footer"
      fixed  >
    -->
    <v-bottom-navigation
      color="#FFB304"
      background-color="#9EA1A2"
      fixed
      dark
      app  >
      <v-btn v-for="item in items" :key="item.title" :to="item.to" style="height: 100%">
        <span>{{ item.title }}</span>
        <v-icon>{{ item.icon }}</v-icon>
      </v-btn>
    </v-bottom-navigation>


  </v-app>
</template>

<script>
export default {
  data () {
    return {
      clipped: false,
      drawer: false,
      fixed: false,
      items: [
        {
          icon: 'mdi-home',
          title: 'ホーム',
          to: '/'
        },
        {
          icon: 'mdi-wifi',
          title: '接続',
          to: '/connect'
        },
        {
          icon: 'mdi-bell',
          title: '通知',
          to: '/notice'
        },
        {
          icon: 'mdi-bell',
          title: '使い方',
          to: '/explain'
        }
      ]
    }
  },
  methods: {
    getTitle(){
      switch(this.$route.name) {
        case "index":
          return "ホーム"
        case "connect":
          return "接続"
        case "notice":
          return "通知"
        case "explain":
          return "使い方"
      }
      return this.$route.name
    }
  }
}
</script>

<style scoped>
.header {
      background: no-repeat;
      background-image: url("~assets/v.png");
      filter: drop-shadow(0px 3px 3px #aaa);
}

.footer {
      background: no-repeat;
      background-image: url("~assets/v.png");
      /* background-size: cover; */
      box-shadow: 0px 0px 0px 0px;
      filter: drop-shadow(0px -3px 3px #aaa);
}
</style>
