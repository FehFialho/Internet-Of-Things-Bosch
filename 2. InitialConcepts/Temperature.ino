#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float umi = dht.readHumidity();
  float temp = dht.readTemperature();

  Serial.print("Temp: ");
  Serial.println(temp);
  Serial.print("Umidade: ");
  Serial.println(umi);
  delay(1000);
}