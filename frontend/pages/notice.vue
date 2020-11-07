<template>
  <div>
    <v-row class="px-5 py-2">
      <v-col cols="12">
        <div class="text-h5 font-weight-black">通知・通報設定</div>
      </v-col>
      <v-col cols="12">
        <div class="text-h6 font-weight-black">通知設定</div>
        <v-switch
          v-model="notice"
          color="#FFB304"
        >
          <template v-slot:label>
            <div class="text-h6">おふろの出入り時に通知する</div>
          </template>
        </v-switch>
      </v-col>

      <v-col cols="12" class="mt-5">
        <div class="text-h6 font-weight-black">通報設定</div>
        <v-switch
          v-model="call"
          color="#FFB304"
        >
          <template v-slot:label>
            <div class="text-h6">緊急時に通報する</div>
          </template>
        </v-switch>
        <div class="amber--text text--darken-1">＊アラームから3分以内に浴室への出入りがない場合、 119番通報されます。</div>
      </v-col>

    </v-row>
  </div>
</template>

<script>
export default {
  data() {
    return {
      notice: true,
      call: false
    }
  }
}
</script>
