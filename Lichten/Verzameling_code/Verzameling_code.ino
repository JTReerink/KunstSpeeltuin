void solid (int r,int g,int b){
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.show();
  }
}

void fadeWalk (int r,int g,int b, int wait) {
  for(int i=0; i<strip.numPixels()+10; i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color((r/100*10),(g/100*10),(b/100*10)));
    int p = 20;
    for(int j = i-1; j > -1; j--){
      strip.setPixelColor(j, strip.Color((r/100*p),(g/100*p),(b/100*p)));
      if(p<101){
        p += 10;
      }
    }
    strip.show();
    delay(wait);
  }
}

void amaze (byte i, int r,int g,int b, int wait){
  for(int j=0; j<101; j += 10){
    strip.setPixelColor(i, strip.Color((r/100.00*j),(g/100.00*j),(b/100.00*j)));
    strip.show();
    delay(wait);
  }
}

void walkIn (uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void fadeIn (int r,int g,int b, int wait) {
   for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      for(int j=0; j < 101; j += 10) { //Fade in with 10%
        strip.setPixelColor(i, strip.Color((r/100*j),(g/100*j),(b/100*j)));
        strip.show();
        delay(wait);
      }
    } 
}

void fadeOut (int r,int g,int b, int wait) {
   for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      for(int j=100; j > -1; j -= 10) { //Fade out with 10%
        strip.setPixelColor(i, strip.Color((r/100.00*j),(g/100.00*j),(b/100.00*j)));
      }
    } 
    strip.show();
}

void fadeInAll (int r,int g,int b, int wait) {
    for(int j=0; j < 101; j += 10) { //Fade in with 10%
      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
        strip.setPixelColor(i, strip.Color((r/100.00*j),(g/100.00*j),(b/100.00*j)));        
      }
      strip.show();
      delay(wait);
    } 
}

void fadeOutAll (int r,int g,int b, int wait) {
    for(int j=100; j > -1; j -= 10) { //Fade out with 10%
      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
        strip.setPixelColor(i, strip.Color((r/100.00*j),(g/100.00*j),(b/100.00*j)));        
      }
      strip.show();
      delay(wait);
    } 
}
