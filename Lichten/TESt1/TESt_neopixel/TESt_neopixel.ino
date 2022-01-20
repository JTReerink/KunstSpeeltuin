//pwm library https://nodemcu.readthedocs.io/en/dev/en/modules/pwm/
//https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


const char* ssid = "Medialab"; // wifi lan
const char* password = "Mediacollege2"; // wifi lan
String server = "http://schw.hosts1.ma-cloud.nl"; // deployment server

String path = "/jaap/control.json"; // path to file
String httpResponse;// response from webserver

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    D1
#define LED_COUNT 60

#define BUTTON_ONE 0
#define BUTTON_TWO D8
#define BUTTON_THREE D8
#define BUTTON_FOUR D8

float bloem0;
float bloem1;
float bloem2;
float bloem3;
float bloem4;

static const uint8_t LED1 = D5;//LED indicator
static const uint8_t LED2 = D6;//LED indicator

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



void setup () {
Serial.begin(115200);

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pinMode(BUTTON_ONE, INPUT_PULLUP);
  pinMode(BUTTON_TWO, INPUT_PULLUP);
  pinMode(BUTTON_THREE, INPUT_PULLUP);
  pinMode(BUTTON_FOUR, INPUT_PULLUP);

  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)

}

void loop() {
if (WiFi.status() != WL_CONNECTED) wifiConnect();// reconnect Wifi if necessary
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
httpRequest();
extractJson();
}



//Serial.println(httpResponse); //Print the response payload
delay(3000); //Send a request every 3 seconds

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



void httpRequest(){
HTTPClient http; //Declare an object of class HTTPClient

http.begin(server + path); //Specify request destination
int httpCode = http.GET(); //Send the request

if (httpCode > 0) { //Check the returning code
httpResponse = http.getString(); //Get the request response payload
Serial.println(httpResponse);
}
http.end(); //Close connection
}



void extractJson() { //extract JSON string from HTTP data
//Serial.println(httpResponse);
// JSONLib 6 https://arduinojson.org/v6/api/jsonarray/
int size = httpResponse.length() + 1;
char jsonString[size];
httpResponse.toCharArray(jsonString, size);
StaticJsonDocument<200> jsonDoc;
deserializeJson(jsonDoc, jsonString);// Deserialize the JSON document
JsonArray dataObj = jsonDoc.as<JsonArray>();
//JsonObject dataObj = jsonDoc.as<JsonObject>();
parseCommands(dataObj);
}



//void parseCommands(JsonObject dataObj){
void parseCommands(JsonArray dataObj){
if(dataObj[0] == "on"){
//Serial.print("device 1 is aan value: ");
plan1();
int range1 = dataObj[1];
analogWrite(LED1, range1); // show brightness
Serial.println(range1);
}
else{
analogWrite(LED1,0); // turn it off
}



if(dataObj[2] == "on"){
//Serial.print("device 2 is aan value: ");
int range2 = dataObj[3];
analogWrite(LED2, range2);
Serial.println(range2);
}
else{
analogWrite(LED2,0); // turn it off
}



}


void plan1() {
  fadeWalk(0, 5, 255, 0, 221, 250);
  delay(7000);
  fadeOutAll (0, 5, 255, 0, 221, 250);
}


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
