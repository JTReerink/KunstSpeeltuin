#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

/*
 * Wifi Network
 * insert here your own network Wifi Credentials 
*/
const char* ssid     = "Medialab"; // wifi lan
const char* password = "Mediacollege2"; // wifi lan

String server  = "http://madebyjaap.nl/thigmogarden";          // deployment server
String pathSendData = "/jsonWrite.php?src=esp&data="; // path to file
// Slow it down 
const int wait = 10000;  // msec between data requests


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    D1
#define SENSOR_PIN D2

float bloem0 = 0;
float bloem1 = 0;
float bloem2 = 0;
float bloem3 = 0;
float bloem4 = 0;

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 10

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



// setup() function -- runs once at startup --------------------------------
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pinMode(SENSOR_PIN, INPUT_PULLUP);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
  
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) wifiConnect();// reconnect Wifi if necessary 
  if (WiFi.status() == WL_CONNECTED) { //if connected
     httpRequestSendData(); // write data to server
  }
  delay(wait);    //Send a request every XXX seconds

//  checkMoveSensor();

}


void wifiConnect(){
  WiFi.begin(ssid, password); // connect to wifi ssid with password 
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000); // wait 1 sec
      Serial.print("Connecting..");
      }
  //if connected
  Serial.print("\r\nConnected: IP address: "); 
  Serial.println(WiFi.localIP());
 }

void httpRequestSendData(){
  StaticJsonDocument<200> jsonDoc; // 
  // create an empty array, arrayLocalData
  JsonArray arrayLocalData = jsonDoc.to<JsonArray>();
  arrayLocalData.add("bloem0"); 
  arrayLocalData.add(bloem0); // function to run
  arrayLocalData.add("bloem1");
  arrayLocalData.add(bloem1); // function to run
  arrayLocalData.add("bloem2");
  arrayLocalData.add(bloem2); // function to run
  arrayLocalData.add("bloem3");
  arrayLocalData.add(bloem3); // function to run
  arrayLocalData.add("bloem4");
  arrayLocalData.add(bloem4); // function to run
  String serverString;
  serializeJson(jsonDoc, serverString);
  
  HTTPClient http;                   //Instance of class HTTPClient
  String url = server + pathSendData  + serverString;
  Serial.println(url);               // handig voor debuggen
  http.begin(url);                   //Specify request destination
  int httpCode = http.GET();         //Send the request  
}

//void checkMoveSensor(){
//  bool newState = digitalRead(SENSOR_PIN);
//  
//  if(newState == HIGH && oldState == LOW) {
//    fadeInAll(25, 34, 50,25,0, 100);
//    
//  }
//  if(newState == LOW && oldState == HIGH) {
//    fadeOutAll(25, 34, 50,25,0, 100);
//
//  }
//  
//  oldState = newState;
//}



void plan1() {
  delay(1500); // wachten op bloem 0
  walkIn(0, 3, 0, 255, 0, 700); // steeltje bloem 1
  fadeWalk(4, 9, 255, 0, 221, 150); // bloem 1
  walkBack(0, 3, 0, 0, 0, 300); // steeltje bloem 1 uit
  delay(7000);
  fadeOutAll (4, 9, 255, 0, 221, 150); // bloem 1 uit fade
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
      strip.setPixelColor(i, strip.Color((r/100.00*10),(g/100.00*10),(b/100.00*10)));
    }
    int p = 20;
    for(int j = i-1; j > eersteLED-1; j--){
      if( j < laatsteLED+1){
        strip.setPixelColor(j, strip.Color((r/100.00*p),(g/100.00*p),(b/100.00*p))); 
      } 
      if(p<101){
        p += 10;
      }
    }
    strip.show();
    delay(wait);
  }
}
