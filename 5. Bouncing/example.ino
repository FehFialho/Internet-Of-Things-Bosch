#define Pino 17

volatile int botao = 0;

void IRAM_ATTR minhaFuncao(){
  botao++;
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
}


void loop() {
  Serial.println(botao);
}