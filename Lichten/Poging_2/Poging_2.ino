#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket

#endif


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    D1
#define SENSOR_PIN D2
#define BUTTON_ONE 0
#define BUTTON_TWO D8

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

bool oldState = LOW;
uint32_t blue = (0, 0, 255);
uint32_t green = (255, 0, 0);

// setup() function -- runs once at startup --------------------------------
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pinMode(SENSOR_PIN, INPUT_PULLUP);
  pinMode(BUTTON_ONE, INPUT_PULLUP);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
  
}

void loop(){

  checkMoveSensor();
  checkButton();
  
}

// Bloem 0 = led 0 t/m 5
// Bloem 1 = led 6 t/m 15
//    Stam = 6 - 9
//    Bloem = 10 - 15
// Bloem 2 = led 16 t/m 24
//    Stam = 16 - 18
//    Bloem = 19 - 24
// Bloem 3 = led 25 t/m 34
//    Stam = 25 - 28
//    Bloem = 29 - 34
// Bloem 4 = led 35 t/m 43
//    Stam = 35 - 37
//    Bloem = 38 - 43


// MOVE SENSOR //
void checkMoveSensor(){
  bool newState = digitalRead(SENSOR_PIN);
  
  if(newState == HIGH && oldState == LOW) {
    fadeInAll(25, 34, 50,25,0, 100);
    
  }
  if(newState == LOW && oldState == HIGH) {
    fadeOutAll(25, 34, 50,25,0, 100);

  }
  
  oldState = newState;
}

// BUTTON //
void checkButton(){
  bool buttonDown = digitalRead(BUTTON_ONE);

  if(buttonDown == LOW) {
    fadeWalk(0, 5, 0, 255, 230, 250); // heel bloem 0
    //elay(5000);
    walkIn(6, 9, 0, 255, 0, 700); // steeltje bloem 1
   // delay(5000);
    fadeWalk(10, 15, 200, 0, 221, 150); // bloem 1

    walkBack(6, 9, 0, 0, 0, 300);
  }
  
  
  bool buttonDown2 = digitalRead(BUTTON_TWO);

  if(buttonDown2 == HIGH) {
    strip.setPixelColor(12, strip.Color(255, 0, 221));         //  Set pixel's color (in RAM)

    strip.setPixelColor(13, strip.Color(255,190,0));         //  Set pixel's color (in RAM)

    strip.setPixelColor(14, strip.Color(50,0,255));         //  Set pixel's color (in RAM)

    strip.setPixelColor(15, strip.Color(0, 255, 230));         //  Set pixel's color (in RAM)

    strip.setPixelColor(16, strip.Color(255,200,221));         //  Set pixel's color (in RAM)

    strip.setPixelColor(17, strip.Color(254,218,95));         //  Set pixel's color (in RAM)

    strip.setPixelColor(18, strip.Color(159,160,253));         //  Set pixel's color (in RAM)

    strip.setPixelColor(19, strip.Color(72,202,228));         //  Set pixel's color (in RAM)

    strip.setPixelColor(22, strip.Color(75,0,255));         //  Set pixel's color (in RAM)
    strip.show();
  }
}







// Alle functies hier onder


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

// Alle tegelijk INfaden
void fadeInAll (int eersteLED,int laatsteLED, int r,int g,int b, int wait) {
    for(int j=0; j < 101; j += 10) { //Fade in with 10%
      for(int i=eersteLED; i<laatsteLED+1; i++) { // For each pixel in strip...
        strip.setPixelColor(i, strip.Color((r/100.00*j),(g/100.00*j),(b/100.00*j)));        
      }
      strip.show();
      delay(wait);
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
void fadeWalk (int eersteLED,int laatsteLED, int r,int g,int b, int wait) {
  for(int i=eersteLED; i<laatsteLED+11; i++) { // For each pixel in strip...
    if(i < laatsteLED+1){
      strip.setPixelColor(i, strip.Color((r/100*10),(g/100*10),(b/100*10)));
    }
    int p = 20;
    for(int j = i-1; j > eersteLED-1; j--){
      if( j < laatsteLED+1){
        strip.setPixelColor(j, strip.Color((r/100*p),(g/100*p),(b/100*p))); 
      } 
      if(p<101){
        p += 10;
      }
    }
    strip.show();
    delay(wait);
  }
}
