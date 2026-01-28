#define Pino 17
hw_timer_t *timer = NULL; // Timer


int tempo = 0;
volatile int botao = 0;
bool flagBotao = 0;

void IRAM_ATTR minhaFuncao(){
  if (flagBotao != 1)
  {
    flagBotao = 1;
    tempo = 200;
  }
  //botao++;
}

void IRAM_ATTR onTimer(){
  if(flagBotao == 1){
    if(tempo >0){
      tempo--;
    }
    else{
      flagBotao = 0;
      if(digitalRead(Pino))
      {
        botao++;
      }
    }
  }
}

void setup() {

  Serial.begin(9600);
  pinMode(Pino, INPUT_PULLUP);
  digitalWrite(Pino, 1);

  attachInterrupt(
    digitalPinToInterrupt(Pino),
    minhaFuncao,
    FALLING
  );

  timer = timerBegin(1000000); 
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000, true, 0); // Esse divide pelo de cima
}


void loop() {
  Serial.println(botao);
}