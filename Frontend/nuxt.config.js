import colors from 'vuetify/es5/util/colors'

const repositry_name = "F_2009"

export default {

  // Disable server-side rendering (https://go.nuxtjs.dev/ssr-mode)
  ssr: false,

  // Global page headers (https://go.nuxtjs.dev/config-head)
  head: {
    title: '安心ふろ～',
    meta: [
      { charset: 'utf-8' },
      { name: 'viewport', content: 'width=device-width, initial-scale=1' },
      { hid: 'description', name: 'description', content: '' },
    ],
    link: [
      { rel: 'icon', type: 'image/x-icon', href: 'favicon.ico' }
    ]
  },

  // Global CSS (https://go.nuxtjs.dev/config-css)
  css: [
  ],

  // Plugins to run before rendering page (https://go.nuxtjs.dev/config-plugins)
  plugins: [
  ],

  // Auto import components (https://go.nuxtjs.dev/config-components)
  components: true,

  // Modules for dev and build (recommended) (https://go.nuxtjs.dev/config-modules)
  buildModules: [
    // https://go.nuxtjs.dev/vuetify
    '@nuxtjs/vuetify',
  ],

  // Modules (https://go.nuxtjs.dev/config-modules)
  modules: [
    // https://go.nuxtjs.dev/axios
    '@nuxtjs/axios',
    // https://go.nuxtjs.dev/pwa
    '@nuxtjs/pwa',

    '@nuxtjs/onesignal',
  ],

  router: {
    linkActiveClass: 'active',
    base: `/${repositry_name}/`
  },

  // Axios module configuration (https://go.nuxtjs.dev/config-axios)
  axios: {
    baseURL: 'https://anshinfurow.hackwebapps.net/api'
  },

  workbox: {
    dev: true,
    // swURL: `${repositry_name}/sw.js`,
    swScope: `/${repositry_name}/`
  },

  oneSignal: {
    init: {
      appId: 'b595fe79-9901-4849-80b4-8ac6eabe379e',
      allowLocalhostAsSecureOrigin: true, // localhostで動作確認する場合true
      welcomeNotification: {
        disable: true
      },
    },
    // path: `/${repositry_name}`,
    importScripts: [`/${repositry_name}/sw.js`], // 必須
  },
  // Vuetify module configuration (https://go.nuxtjs.dev/config-vuetify)
  vuetify: {
    customVariables: ['~/assets/variables.scss'],
    theme: {
      dark: false,
      themes: {
        dark: {
          primary: colors.blue.darken2,
          accent: colors.grey.darken3,
          secondary: colors.amber.darken3,
          info: colors.teal.lighten1,
          warning: colors.amber.base,
          error: colors.deepOrange.accent4,
          success: colors.green.accent3
        }
      }
    }
  },

  // Build Configuration (https://go.nuxtjs.dev/config-build)
  build: {
  },

  generate: {
    dir: "../docs"
  },

  manifest: {
    name: "安心ふろ～",
    short_name: "安心ふろ～",
    title: "安心ふろ～",
    'og:title': '安心ふろ～',
    description: '高齢者の風呂場での異常を検知してくれるアプリ 「安心ふろ～」',
    'og:description': '高齢者の風呂場での異常を検知してくれるアプリ 「安心ふろ～」',
    lang: 'ja',
    theme_color: '#3DB4BE',
    background_color: '#3DB4BE',
    display: "standalone",
    start_url: `/${repositry_name}/`,
  },
}
