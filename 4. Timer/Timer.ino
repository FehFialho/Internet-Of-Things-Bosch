hw_timer_t *timer = NULL;
int time = 0;

void IRAM_ATTR onTimer(){
  time++;
}
void setup() {
  Serial.begin(9600);

  WiFi.onEvent(WiFiEvent);
  WiFi.begin(SSID, password);
  Serial.println("Starting Wifi");

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 10000000, true, 0);
}

void loop() {
  Serial.println("Time: " + String(time));
}