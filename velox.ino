#include <Arduino.h>
#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>

// State variables
unsigned long lastPublish = 0;
int status = WL_IDLE_STATUS;

#include "sensor_backend.h"

#include "config.h"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

void setup() {
  Serial.begin(115200);
  backend.setupBackend();
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while (!Serial) { }

  String willPayload = "{\"idx\":36,\"nvalue\":0,\"svalue\":\"-273.15\"}";
  mqttClient.beginWill("domoticz/in", willPayload.length(), true, 1);
  mqttClient.print(willPayload);
  mqttClient.endWill();
}

void connectWifi() {
  status = WiFi.status();

wifi:
  // Connect to WPA/WPA2 network:
  if (WiFi.status() != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);

    // wait 10 seconds for connection:
    Serial.print("Connecting to wifi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Wifi connected");
  }

mqtt:
  if (!mqttClient.connected()) {
    mqttClient.setUsernamePassword(MQTT_USER, MQTT_PASS);
    if (!mqttClient.connect(MQTT_BROKER, MQTT_PORT)) {
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Lost wifi connection");
        delay(10000);
        goto mqtt;
      } else {
        Serial.println("No MQTT connection");
        delay(5000);
        goto wifi;
      }
    } else {
      Serial.println("MQTT connected");
    }
  }
}

void sendMqttData() {
  backend.prepareRead();
  int count = backend.getSensorCount();
  for (int i = 0; i < count; i++) {
    mqttClient.beginMessage(MQTT_TOPIC);
    mqttClient.print("{\"idx\":");
    mqttClient.print(backend.getDomoticzIndex(i));
    mqttClient.print(",\"nvalue\":");
    mqttClient.print(backend.readSensorInt(i));
    mqttClient.print(",\"svalue\":\"");
    mqttClient.print(backend.readSensorFloat(i));
    mqttClient.print("\"}");
    mqttClient.endMessage();
  }
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastPublish > PUBLISH_INTERVAL_MILLIS) {
    lastPublish = currentTime;

    connectWifi();
    sendMqttData();
  }
}
