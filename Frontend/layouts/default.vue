<template>
  <v-app dark>
  <!--
    デザイン案ができた後はこっち
    <v-app-bar
      :clipped-left="clipped"
      :elevation="0"
      class="header"
      color="transparent"
      fixed
      app
    >
    -->
    <v-app-bar
      :clipped-left="clipped"
      color="amber darken-1"
      fixed
      dark
      app
    >
      <div class="text-h5 font-weight-bold">安心ふろ～</div>
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
      class="amber darken-1"
      fixed
      app  >
      <v-btn v-for="item in items" :key="item.title" :to="item.to">
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
          title: 'Home',
          to: '/'
        },
        {
          icon: 'mdi-chart-bubble',
          title: 'Inspire',
          to: '/inspire'
        }
      ]
    }
  },
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
