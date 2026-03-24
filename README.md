# lan-thermostat-sensor
A local‑network thermostat monitor using an ESP8266 + DHT22, Mosquitto (MQTT), and a Node‑RED dashboard. The ESP8266 reads temperature/humidity every ~5s and publishes compact JSON to the broker; Node‑RED subscribes and shows live gauges and rolling charts at http://127.0.0.1:1880/ui. No cloud, no SQL—simple, reliable, and easy to debug.
