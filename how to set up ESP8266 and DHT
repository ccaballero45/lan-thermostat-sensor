


Title: Hardware & IDE Setup (ESP8266 + DHT22)

What connects to what

Board: ESP8266 NodeMCU (ESP‑12E)
Sensor: DHT22 (3 pins module labeled +, OUT, −)
Wiring:
DHT22 + → ESP 3V3 (3.3V)
DHT22 OUT → ESP D5 (GPIO14) *most important *
DHT22 − → ESP GND


Keep wires short. Power the ESP via USB.
Arduino IDE configuration

Board: Tools → Board → NodeMCU 1.0 (ESP‑12E Module)
Port: Tools → Port → COM4 (your CP210x port)
Upload Speed: 115200
CPU Freq: 80 MHz
Flash Size: 4M (default is fine)
Programmer: (ignored for ESP8266)
Libraries (Install via Library Manager)

Adafruit DHT sensor library
Adafruit Unified Sensor
PubSubClient (MQTT)
Firmware (what to edit)

Open: firmware/esp8266_dht22_mqtt.ino
Set:
WIFI_SSID = "Your_SSID"
WIFI_PASS = "Your_Password"
MQTT_HOST = "" (from ipconfig)
MQTT_PORT = 1883
DHTPIN = 14 (D5)
Topic: home/temperature
Payload: {"device":"esp8266-temp-1","t_c":,"h":}
Cadence: ~5 seconds
Build and upload

Close Serial Monitor if open.
Click Upload. After “Hard resetting via RTS pin…”, open Serial Monitor at 115200 baud.
Expected Serial output:
WiFi OK:
MQTT OK
Pub OK: {"device":"...","t_c":..,"h":..}
