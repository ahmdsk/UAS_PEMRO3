<template>
  <q-page class="flex flex-center">
    <q-input v-model="monitor" filled type="textarea" rows="20" readonly style="width: 500px" />
  </q-page>
</template>

<script>
import { defineComponent, onMounted, ref } from 'vue'
import mqtt from 'mqtt'
import { mqttConfig, urlMQTT } from 'src/lib/mqtt'

export default defineComponent({
  name: 'IndexPage',

  setup() {
    const monitor = ref('')

    const client = mqtt.connect(urlMQTT, mqttConfig)

    onMounted(() => {
      client.on('connect', () => {
        monitor.value = 'Berhasil terhubung ke RabbitMQ\n'
      })

      client.subscribe("routing_ahmad", (err) => {
        if (!err) { }
      })

      client.on('message', (topic, payload) => {
        monitor.value += `${payload.toString()}\n`
      })
    });

    return {
      monitor
    }
  }
})
</script>
