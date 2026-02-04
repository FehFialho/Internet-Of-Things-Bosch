#define Pino 16

#define LED_1 25
#define LED_2 33
#define LED_3 32
#define LED_4 18
#define LED_5 5
#define LED_6 17

int meusLeds[] = {25, 33, 32, 18, 5, 17};
int ledAtual = 25;
int horario = 1;

hw_timer_t *timer = NULL; // Timer

int tempo = 0;
volatile int botao = 0;
bool flagBotao = 0;

void mudarDirecao(){
  Serial.println("Mudando Direção");
}

void IRAM_ATTR minhaFuncao(){
  if (flagBotao != 1)
  {
    flagBotao = 1;
    tempo = 200;
  }
}

void IRAM_ATTR onTimer(){

  if(horario){
    for (int i = 0; i < sizeof(meusLeds); i++ ){
      digitalWrite(meusLeds[i], HIGH);
      delay(1000);
      digitalWrite(meusLeds[i], LOW);
      ledAtual = meusLeds[i];
    }
  } else{
    for (int i = sizeof(meusLeds); i > 0; i-- ){
      digitalWrite(meusLeds[i], HIGH);
      delay(1000);
      digitalWrite(meusLeds[i], LOW);
      ledAtual = meusLeds[i];
    }
  }


  if(flagBotao == 1){
    if(tempo >0){
      tempo--;
    }
    else{
      flagBotao = 0;
      if(digitalRead(Pino))
      {
        botao++;
        horario = !horario;
      }
    }
  }
}

void setup() {

  for (int i = 0; i < sizeof(meusLeds); i++ ){
    pinMode(meusLeds[i], OUTPUT);
  }

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
  Serial.print("Horário: ");
  Serial.println(horario);

  // for (int i = 0; i < sizeof(meusLeds); i++ ){
  //   digitalWrite(meusLeds[i], HIGH);
  //   delay(1000);
  //   digitalWrite(meusLeds[i], LOW);
  //   ledAtual = meusLeds[i];
  // }
  
}