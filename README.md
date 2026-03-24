
ESP8266 reads a DHT22 sensor and publishes JSON (device, t_c, h) over MQTT every ~5s. Mosquitto runs on your PC; Node‑RED shows live gauges and charts at http://127.0.0.1:1880/ui. No SQL; if storage is added later, I’ll avoid SQL and use a simple file/non‑SQL option.



firmware/esp8266_dht22_mqtt.ino
nodered/flow.json
mosquitto/mosquitto.conf
scripts/Start-ThermostatDashboard.ps1


Requirements

Windows 10/11
Arduino IDE + ESP8266 core + CP210x driver
Mosquitto (Windows)
Node‑RED + node-red-dashboard
Wi‑Fi (ESP8266 and PC on same LAN)
Setup

Firmware (ESP8266)
Open firmware/esp8266_dht22_mqtt.ino in Arduino IDE.
Set WIFI_SSID, WIFI_PASS, MQTT_HOST = , DHTPIN = 14 (D5).
Install libs: Adafruit DHT, Adafruit Unified Sensor, PubSubClient.
Wire: DHT22 +3.3V, OUT→D5 (GPIO14), GND.
Upload; Serial @115200 should show “WiFi OK / MQTT OK / Pub OK”.
Mosquitto (must be running)
Ensure mosquitto.conf has: listener 1883 0.0.0.0 allow_anonymous true
Start (exact command): "C:\Program Files\Mosquitto\mosquitto.exe" -c "C:\Program Files\Mosquitto\mosquitto.conf" -v
Allow firewall on Private network.
Node‑RED
Start Node‑RED (node-red).
Import nodered/flow.json (Menu → Import).
Edit MQTT broker in the flow to use , port 1883, topic home/temperature.
Deploy. Open http://127.0.0.1:1880/ui.
How to run (each session)

Start Mosquitto with the command above.
Start Node‑RED (or run scripts/Start-ThermostatDashboard.ps1).
Power the ESP8266.
Verify

In a terminal: mosquitto_sub -h -t home/temperature -v
Expect JSON every ~5s. Dashboard gauges and charts should update.
Troubleshooting

ESP rc = -2: broker unreachable. Check , port 1883, firewall, Mosquitto running.
Port/local‑only: stop service (net stop mosquitto), then run the Mosquitto command above.
Chart stuck: ensure JSON node parses payload; change node feeds payload.t_c (number) into chart.
Serial blank: match baud 115200, correct COM (CP210x), press RESET.
Optional one‑click start

PowerShell: powershell -ExecutionPolicy Bypass -File "scripts\Start-ThermostatDashboard.ps1"
To auto‑start on login: Win+R → shell:startup → New Shortcut → Target: powershell.exe -ExecutionPolicy Bypass -File "C:\Thermostat\scripts\Start-ThermostatDashboard.ps1"

Notes for reviewers

Replace with your IPv4 (ipconfig).
