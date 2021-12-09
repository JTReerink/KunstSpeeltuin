#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    D1
#define SENSOR_PIN D2
#define BUTTON_ONE 0

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 63

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
  

  
//  firstAttempt(strip.Color(255, 0, 0), 400);
//  firstAttempt(strip.Color(0, 255, 0), 400);
//  firstAttempt(strip.Color(0, 0, 255), 400);
//  fadeIn(255, 0, 0, 100);
//  fadeIn(0, 255, 0, 100);
//  fadeIn(0, 0, 255, 100);
}

void checkMoveSensor(){
  bool newState = digitalRead(SENSOR_PIN);
  
  if(newState == HIGH && oldState == LOW) {
    fadeInAll(50,25,0, 100);
  }
  if(newState == LOW && oldState == HIGH) {
    delay(20);
    fadeOutAll(50,25,0, 100);
  }
  
  oldState = newState;
}

void checkButton(){
  bool buttonDown = digitalRead(BUTTON_ONE);

  if(buttonDown == LOW) {
//    solid(99,99,99);
    fadeWalk (255,0,0,200);
  }
}

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

void firstAttempt (uint32_t color, int wait) {
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
