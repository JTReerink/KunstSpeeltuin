float bloem0 = 0;
float bloem1 = 0;
float bloem2 = 0;
float bloem3 = 0;
float bloem4 = 0;

void checkButtons(){
  bool buttonDownOne = digitalRead(BUTTON_ONE);
  bool buttonDownTwo = digitalRead(BUTTON_TWO);
  bool buttonDownThree = digitalRead(BUTTON_THREE);
  bool buttonDownFour = digitalRead(BUTTON_FOUR);
  
  if(buttonDownOne == LOW) {
    bloem0 = 1;
    bloem1 = 1;
    Serial.println("1 pressed");
  } 
  if(buttonDownTwo == LOW) {
    bloem0 = 2;
    bloem2 = 1;
    Serial.println("button 2 pressed");
  }
  if(buttonDownThree == LOW) {
    bloem0 = 3;
    bloem3 = 1;
    Serial.println("button 3 pressed");
  } 
  if(buttonDownFour == LOW) {
    bloem0 = 4;
    bloem4 = 1;
  } 
  if(buttonDownOne == HIGH && buttonDownTwo == HIGH && buttonDownThree == HIGH && buttonDownFour == HIGH) {
    bloem0 = 0;
    bloem1 = 0;
    bloem2 = 0;
    bloem3 = 0;
    bloem4 = 0;
  }
}
