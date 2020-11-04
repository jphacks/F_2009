<template>
  <button @click="$emit('input', id)" :class="[active, 'tab']">
    {{ label }}
  </button>
</template>

<script>
export default {
  props: {
    id: Number,
    value: Number
  },
  computed: {
    active() {
      return this.value === this.id ? 'active' : false
    }
  }
}
</script>

<style scoped>
.tab {
  width: 40px;
  height: 40px;
  border-radius: 2px 2px 0 0;
  background: #eeeeee;
  color: gray;
  border-radius: 50%;
  position: relative;
  margin: 25pt;
}
.tab:hover {
  background: yellow;
}
.active {
  background: yellow;
}
</style>