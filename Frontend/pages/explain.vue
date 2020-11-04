<template>
  <div class="example">
    <v-col class="contents" align="center">
      <div>説明1</div>
      <div>説明2</div>
      <div>説明3</div>
      <div>説明4</div>
      <div>説明5</div>
    </v-col>
    <v-col class="tabs" align="center">
      <Tab
        v-for="item in list"
        v-bind="item" :key="item.id"
        v-model="currentId"/>
    </v-col>
  </div>
</template>

<script>
import Tab from './tab.vue'
export default {
  components: { Tab },
  data() {
    return {
      currentId: 1,
      list: [
        { id: 1, content: '説明1' },
        { id: 2, content: '説明2' },
        { id: 3, content: '説明3' },
        { id: 4, content: '説明4' },
        { id: 5, content: '説明5' }
      ]
    }
  },
  computed: {
    current() {
      return this.list.find(el => el.id === this.currentId) || {}
    }
  }
}
</script>

<style scoped>
.contents {
  display: flex;
  position: relative;
  overflow-x: scroll;
  width: 100%;
  -webkit-overflow-scrolling: touch;
  -overflow-scrolling: touch;
  scroll-snap-type: x mandatory;
}
.contents > div {
   scroll-snap-align: center;
    height: 100%;
    width: 100%;
    flex: none;
}
.item {
  box-sizing: border-box;
  padding: 10px;
  width: 100%;
  transition: all 0.8s ease;
  scroll-snap-align: start;
  scroll-snap-align: cnter;
  flex: none;
}
.v-leave-active {
  position: absolute;
}
.v-enter {
  transform: translateX(-100%);
}
.v-leave-to {
  transform: translateX(100%);
}
</style>
