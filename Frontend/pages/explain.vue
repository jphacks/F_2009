<template>
  <v-row>
    <v-carousel v-model="model" :height="height" class="">
      <v-carousel-item
        v-for="(color, i) in colors"
        :key="color"
      >
        <v-sheet
          :color="color"
          height="100%"
          tile
        >
          <v-row
            class="fill-height"
            align="center"
            justify="center"
          >
            <div class="display-3">
              説明 {{ i + 1 }}
            </div>
          </v-row>
        </v-sheet>
      </v-carousel-item>
    </v-carousel>
  </v-row>
</template>

<script>
export default {
  data() {
    return {
      model: 0,
      colors: [
        'primary',
        'secondary',
        'yellow darken-2',
        'red',
        'orange',
      ],
      height: window.innerHeight - 64 - 46,
    }
  }
}
</script>
