/*
  LED control using a push button with Arduino. (01/07/2026)
  Each time the button is pressed, the LED state is toggled
  (ON/OFF). The button uses the internal pull-up resistor.
*/

/* ====== CONNECTIONS =======

   Push Button
   - one terminal -> Arduino pin 6
   - other terminal -> GND

   LED
   - anode (+)  -> Arduino pin 4 (with resistor)
   - cathode (-) -> GND

*/

int button = 6;
int led = 4;

int state = 0;
int isPressed = 0;

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  isPressed = !digitalRead(button);
  if (isPressed){
    state = !state;
    digitalWrite(led, state);
    while (!digitalRead(button) == 1){}    
  }
  
  Serial.print("isPressed: ");
  Serial.println(isPressed);
  
  Serial.println("");
  Serial.println("-----------");
  Serial.println("");

  Serial.print("State: ");
  Serial.println(state);

}