/*
  Elevator control using Arduino. (01/07/2026)
  A relay turns the motor ON while the elevator moves up or down.
*/

/* ====== CONNECTIONS =======

   Relay 
   - pin 1 -> Arduino pin 8
   - pin 3 -> GND
   - COM -> +V (power supply)

   Motor
   - negative   -> GND
   - positive -> NO or NC Relay

*/

String entrada = "";
int rele = 8;
int atual = 1;
int alvo = 1;

void setup() {
  pinMode(rele, OUTPUT);
  Serial.begin(9600);
  Serial.print("Andar Atual: ");
  Serial.println(atual);
}

void loop() {

  if (Serial.available() > 0) {
    entrada = Serial.readStringUntil('\n');
    entrada.trim();
    alvo = entrada.toInt();

    if (alvo < 1 || alvo > 10) {
      Serial.println("Esse andar não existe!");
      alvo = atual; // evita executar o movimento
    }
  }

  if (atual != alvo){
    if (alvo > atual){
      digitalWrite(rele, 1);
      for (int i = atual; i < alvo; i++){
        Serial.print("Andar Nº");    
        Serial.println(i);    
        delay(1000);
      }
      digitalWrite(rele, 0);
      Serial.println("Chegou!");    
      atual = alvo;
      Serial.print("Andar Atual: ");
      Serial.println(atual);
    } 
    
    else {
      digitalWrite(rele, 1);
      for (int i = atual; i > alvo; i--){
        Serial.print("Andar Nº");    
        Serial.println(i);    
        delay(1000);
      }
      digitalWrite(rele, 0);
      Serial.println("Chegou!");    
      atual = alvo;
      Serial.print("Andar Atual: ");
      Serial.println(atual);
    }
  }
}