
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Wi‑Fi + MQTT
#define WIFI_SSID   "JULINGTON UNIT 255"
#define WIFI_PASS   "8d4262e0f7f3e937"
#define MQTT_HOST   "192.168.1.139"   // PC IP running Mosquitto
#define MQTT_PORT   1883
#define CLIENT_ID   "esp8266-temp-1"
#define TOPIC_DATA  "home/temperature"
#define TOPIC_STAT  "home/temperature/status"

// Sensor (D5 = GPIO14)
#define DHTPIN   14
#define DHTTYPE  DHT22

WiFiClient wifi;
PubSubClient mqtt(wifi);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastPub = 0;
const unsigned long PUB_MS = 5000;

void wifiEnsure() {
  if (WiFi.status() == WL_CONNECTED) return;
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.printf("\nWiFi OK  IP: %s\n", WiFi.localIP().toString().c_str());
}

void mqttEnsure() {
  if (mqtt.connected()) return;
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  // Last Will: status offline
  if (mqtt.connect(CLIENT_ID, nullptr, nullptr, TOPIC_STAT, 0, true, "offline")) {
    mqtt.publish(TOPIC_STAT, "online", true);
    Serial.println("MQTT OK (connected)");
  } else {
    Serial.printf("MQTT connect fail, rc=%d\n", mqtt.state());
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  dht.begin();
  Serial.println("\n=== ESP8266 + DHT22 + MQTT ===");
  wifiEnsure();
  mqttEnsure();
}

void loop() {
  wifiEnsure();
  mqttEnsure();
  mqtt.loop();

  if (millis() - lastPub >= PUB_MS) {
    lastPub = millis();


float h = dht.readHumidity();
float t_c = dht.readTemperature();
if (isnan(h) || isnan(t_c)) {
  Serial.println("Read: FAIL (sensor)");
  return;
}
float t_f = t_c * 9.0 / 5.0 + 32.0;

// JSON payload (compact and readable)
String payload = "{";
payload += "\"device\":\"" + String(CLIENT_ID) + "\",";
payload += "\"t_c\":" + String(t_c, 2) + ",";
payload += "\"t_f\":" + String(t_f, 2) + ",";
payload += "\"h\":"   + String(h, 1);
payload += "}";

bool ok = mqtt.publish(TOPIC_DATA, payload.c_str(), true);

// Clean serial line
Serial.print(ok ? "Pub OK  " : "Pub FAIL  ");
Serial.printf("C: %.2f  F: %.2f  H: %.1f%%  JSON: %s\n",
              t_c, t_f, h, payload.c_str());
  }
}