hw_timer_t *timer = NULL;
int tempo = 0;

void IRAM_ATTR onTimer() {
  tempo ++;
}

void setup() {
  Serial.begin(9600);
  //seta a frequência do timer (1seg) - 80Mhz é o padrão
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000000, true, 0);

}

void loop() {
  Serial.println("Variável: " + String(tempo));
}