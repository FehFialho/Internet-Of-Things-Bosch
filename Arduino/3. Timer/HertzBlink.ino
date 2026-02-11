#define led 2
hw_timer_t *timer = NULL; // Timer

// 5hz - 0.2s
// 1hz - 1s

volatile int tempo = 0;
volatile int blink = 0;
volatile bool mode = 1;

void IRAM_ATTR onTimer(){

  tempo++;
  if (mode){
    digitalWrite(led, !digitalRead(led));
  }

  if (tempo % 5 == 0){
    digitalWrite(led, !digitalRead(led));
    blink++;
  }

}

void setup() {

  pinMode(led, OUTPUT);
  Serial.begin(9600);

// x será a quantidade em segundos que quero, multiplicar pelo TimerBegin, sera o valor do timerAlarm!

  timer = timerBegin(1000000); 
  timerAttachInterrupt(timer, &onTimer); // x = 0.2 * 1_000_000 # 200_000
  timerAlarm(timer, 200000, true, 0); // Esse divide pelo de cima
}

void loop() {

  Serial.println(tempo);

  if (tempo > 25){
    tempo = 0;
    mode = 0;
    if (blink == 5){
      blink = 0;
      mode = 1;
    }
  }
}