#include <WiFi.h>

const char* ssid = "lele";
const char* password = "20070318";

void WiFiEvent(WiFiEvent_t event) {
  switch(event) {
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("Connected!");
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("Disconnected!");
      WiFi.reconnect();
      break;
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);
  Serial.println("Trying to connect...");

}

void loop() {
  // put your main code here, to run repeatedly:

}