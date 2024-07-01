#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Belajar Menghubungkan Sensor Kelembaban Tanah Dengan ESP8266
// dan Sensor Tanah (Soil Misture Sensor v2.0)

// Tabel Setup Alur Pin
// Sensor | ESP8266
// ----------------
// GND    | G
// VCC    | D8
// AUOT   | AO

// Kode
const int sensor_pin = A0;

const char* ssid = "Pasca Sarjana";
const char* password = "ublkecee";
const char* mqtt_server = "103.167.112.188";
const char* routing_key = "routing_ahmad";

WiFiClient espClient;
PubSubClient client(espClient);
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

// Setup untuk terhubung ke wifi
void setup_wifi() {
  delay(10);
  // mencoba menguhubungkan ke wifi
  Serial.println();
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // jika tidak konek maka print "...."
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  // Jika wifi terhubung tampilkan alamat ip
  Serial.println("");
  Serial.println("WiFi terhubung");
  Serial.println("Alamat IP: ");
  Serial.println(WiFi.localIP());
}

// Menghubungkan ke mqtt
void reconnect() {
  // looping jika belum berhasil konek
  while (!client.connected()) {
    Serial.print("Menguhubungkan kembali MQTT ...");
    // Create a random client ID
    String clientId = "ESP8266Client-AHMAD-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "/iot:kelas_edp", "kelas_edp")) {
      Serial.println("Berhasil terhubung dari ArduinoIDE");
      // Once connected, publish an announcement...
      client.publish(routing_key, "Berhasil terhubung dari ArduinoIDE");
      // ... and resubscribe
      // client.subscribe(routing_key);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" mencoba kembali dalam 5 detik");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // float moisture_percentage;
  // moisture_percentage = (100.00 - ((analogRead(sensor_pin) / 1023.00) * 100.00));
  snprintf(msg, MSG_BUFFER_SIZE, "Kelembaban Tanah: %s", String(analogRead(sensor_pin)));

  Serial.println(analogRead(sensor_pin));
  client.publish(routing_key, msg);
  delay(1000);
}