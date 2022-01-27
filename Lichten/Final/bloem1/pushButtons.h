#define BUTTON_ONE 0
#define BUTTON_TWO D2

float button1 = 0;

float bloem0;
float bloem1;
float bloem2;
float bloem3;
float bloem4;

void checkButtons(){
  bool buttonDownOne = digitalRead(BUTTON_ONE);
  bool buttonDownTwo = digitalRead(BUTTON_TWO);
  
  if(buttonDownTwo == LOW) {
    bloem0 = 1;
    bloem1 = 1;
    Serial.println("1 pressed");
  } 
  if (buttonDownTwo == HIGH && bloem0 == 1) {
    bloem0 = 0;
    bloem1 = 0;
  }
}
