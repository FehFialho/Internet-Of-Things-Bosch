/*
  Ultrasonic distance measurement using ESP32. (01/08/2026)
  An ultrasonic sensor is used to calculate the distance to an object
  by measuring the time of the echo pulse and applying the speed of sound.
*/

/* ====== CONNECTIONS =======

   Ultrasonic Sensor (HC-SR04 or compatible)
   - TRIG -> ESP32 GPIO 13
   - ECHO -> ESP32 GPIO 12
   - VCC  -> 5V (or 3.3V if supported)
   - GND  -> GND

*/

#define trig 13
#define echo 12

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {

  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);

  float secs = pulseIn(echo, 1) / 1000000.;
  float distance = secs * 343.2 / 2 * 100; // Velocidade da Luz, duas vezes convertida para centimetros;

  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println("cm");
  delay(1000);

}