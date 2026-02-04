#include <time.h>
#include <WiFi.h>

const char * servidor = "pool.ntp.org";
const long fuso = -10800;
const int verao = 0;

const char* SSID = "hotspot";
const char * password = "passs";

void WiFiEvent(WiFiEvent_t event){
   switch(event){
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("conectado");
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.print("Desconectado");
      WiFi.reconnect();
      break;
   }
}

void setup(){
  Serial.begin(9600);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(SSID, password);
  Serial.println("Iniciando conexão WIFI");
  configTime(fuso, verao, servidor);
}

void loop(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("sem hora");
    return;
  }
  Serial.println(&timeinfo);
}