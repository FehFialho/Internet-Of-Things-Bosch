#define Pino 13
#define quantidadeLED 6

hw_timer_t *timer = NULL; // Timer

int meusLeds[] = {25, 33, 32, 19, 18, 5};
int ledAtual = 0;

int tempo = 0;
int ledTempo = 0;

volatile int botao = 0;
bool flagBotao = 0;
bool sentido = 1;

void IRAM_ATTR minhaFuncao(){
  if (flagBotao != 1)
  {
    flagBotao = 1;
    tempo = 200;
  }
  //botao++;
}

void IRAM_ATTR onTimer(){

  ledTempo++;

  if(flagBotao == 1){
    if(tempo >0){
      tempo--;
    }
    else{
      flagBotao = 0;
      if(digitalRead(Pino))
      {
        botao++;
        sentido = !sentido;
        //ledAtual--;
      }
    }
  }
}

void setup() {

  for (int i = 0; i < quantidadeLED; i++ ){
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

  // Serial.print("Botao: ");
  // Serial.println(botao);

  // Serial.println("");

  // Serial.print("Led Tempo: ");
  // Serial.println(ledTempo);

  // Serial.println("");

  // Serial.print("Led Atual: ");
  // Serial.println(ledAtual);

  //if (ledTempo > 200){
    digitalWrite(meusLeds[ledAtual], HIGH);
    if (ledTempo > 400){
      digitalWrite(meusLeds[ledAtual], LOW);
      if (sentido){
        ledAtual++;
        if (ledAtual >= quantidadeLED){
          ledAtual = 0;
        }
      } 
      else{
        ledAtual--;
        if (ledAtual < 0){
          ledAtual = quantidadeLED - 1;
        }
      }
      ledTempo = 0;
    }
  //}=
}