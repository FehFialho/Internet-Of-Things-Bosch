// 01/14/2025 - Leleca

#include <WiFi.h>

#define green_led 33
#define red_led 32

const char* ssid = "lele";
const char* password = "20070318";
hw_timer_t *timer = NULL;
int tempo = 0;

void IRAM_ATTR connected() {
  digitalWrite(green_led, !digitalRead(green_led));
  digitalWrite(red_led, LOW);
}

void IRAM_ATTR disconnected() {
  digitalWrite(red_led, !digitalRead(red_led));
  digitalWrite(green_led, LOW);
}

void WiFiEvent(WiFiEvent_t event) {
  switch(event) {
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:  
      timerAttachInterrupt(timer, &connected);
      timerAlarm(timer, 50000, true, 0);
      Serial.println("conectadinho");
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      timerAttachInterrupt(timer, &disconnected);
      timerAlarm(timer, 250000, true, 0);
      Serial.println("desconectado");
      WiFi.reconnect();
      break;
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);
  Serial.println("Iniciando conexão Wifi...");
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  
  timer = timerBegin(1000000);

}

void loop() {
  

}