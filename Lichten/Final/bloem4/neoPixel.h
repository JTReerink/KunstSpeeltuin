/*
 * Neopixel
 */


#include <Adafruit_NeoPixel.h>

// Neopixel Config
//#define NeoPIN D4 // Neopixel data pin
#define NeoPIN D1 // Neopixel data pin Jaap
#define NUM_LEDS 60 // number of leds
int brightness = 255;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NeoPIN, NEO_RGB + NEO_KHZ800);

void startNeoPixel(){
    strip.setBrightness(brightness);
    strip.begin();
    strip.show();
  }



/*
void setNeoColor(int r, int g, int b){
  Serial.print("Setting Neopixel...");
  // DEBUG
  Serial.print("RGB: ");
  Serial.print(r, DEC);
  Serial.print(" ");
  Serial.print(g, DEC);
  Serial.print(" ");
  Serial.print(b, DEC);
  Serial.println(" ");
  
  // setting whole strip to the given color
  for(int i=0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color( g, r, b ) );
  }
  // init
  strip.show();
  
  Serial.println("on.");
}
*/


/* Alle lichtplannen hier onder */

// 1 voor 1 AAN (no fade)
void walkIn (int eersteLED,int laatsteLED, int r,int g,int b, int wait) {
  for(int i=eersteLED; i<laatsteLED+1; i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(r, g, b));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void walkBack (int eersteLED,int laatsteLED, int r,int g,int b, int wait) {
  for(int i=laatsteLED; i>eersteLED-1; i--) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(r, g, b));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Alle tegelijk UITfaden
void fadeOutAll (int eersteLED,int laatsteLED, int r,int g,int b, int wait) {
    for(int j=100; j > -1; j -= 10) { //Fade out with 10%
      for(int i=eersteLED; i<laatsteLED+1; i++) { // For each pixel in strip...
        strip.setPixelColor(i, strip.Color((r/100.00*j),(g/100.00*j),(b/100.00*j)));        
      }
      strip.show();
      delay(wait);
    } 
}

// om en om infaden terwijl voorgaande nog bezig is
void fadeWalk(int eersteLED,int laatsteLED, int r,int g,int b, int wait) {
  for(int i=eersteLED; i<laatsteLED+5; i++) { // For each pixel in strip...
    if(i < laatsteLED+1){
      strip.setPixelColor(i, strip.Color((r/100.00*10),(g/100.00*10),(b/100.00*10)));
    }
    Serial.print("i: ");
    Serial.println(i);
    int p = 20;
    for(int j = i-1; j > eersteLED-1; j--){
      if( j < laatsteLED+1 ){
        strip.setPixelColor(j, strip.Color((r/100.00*p),(g/100.00*p),(b/100.00*p))); 
        
      }
      Serial.print("j: ");
        Serial.println(j);
      if(p<101){
        p += 10;
      }
    }
    strip.show();
    delay(wait);
  }
}
