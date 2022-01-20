/*
 * Duurzaam Huis Led Control
 * Temperature + Humidity Sensor DHT11
 * MediaCollege Amsterdam feb 2021
*/

// network
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Neopixel
#include "neoPixel.h"


/*
 * Wifi Network
 * insert here your own network Wifi Credentials 
*/
#include "network.h" 

//#include "pushButtons.h"


// Slow it down
const int wait = 1000;  // msec between data requests


void setup () {
  Serial.begin(115200); // start Serial monitor
  startNeoPixel(); // NeoPixel start
//  pinMode(BUTTON_ONE, INPUT_PULLUP);
//  pinMode(BUTTON_TWO, INPUT_PULLUP);
//  pinMode(BUTTON_THREE, INPUT_PULLUP);
//  pinMode(BUTTON_FOUR, INPUT_PULLUP);
}
 
void loop() {  
  if (WiFi.status() != WL_CONNECTED) wifiConnect();// reconnect Wifi if necessary 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

//     checkButtons();
//     httpRequest2(); // write data to server
     httpRequest(); // get data from server
     extractJson(); // execute data from server
  }
 
  //Serial.println(httpResponse);  //Print the response payload
  delay(wait);    //Send a request every XXX seconds
}



void httpRequest(){
  HTTPClient http;               //Declare an instance of class HTTPClient
  
  http.begin(server + path);     //Specify request destination
  int httpCode = http.GET();     //Send the request
   
  if (httpCode > 0) {            //Check the returning code
      httpResponse = http.getString();  //Get the request response payload      
      Serial.println(httpResponse);                                    
     }
   http.end();   //Close connection  
  }


/* 
void httpRequest2(){
  
  //https://arduinojson.org/v6/api/jsonarray/
  StaticJsonDocument<200> jsonDoc;
  // create an empty array, arrayLocalData
  JsonArray arrayLocalData = jsonDoc.to<JsonArray>(); 
  arrayLocalData.add(bloem0); // value from DHT11
  arrayLocalData.add(bloem1); // value from DHT11
  arrayLocalData.add(bloem2); // value from DHT11
  arrayLocalData.add(bloem3); // value from DHT11
  arrayLocalData.add(bloem4);
  String serverString;
  serializeJson(jsonDoc, serverString);
  
  HTTPClient http;                                       //Instance of class HTTPClient
  String url = server + path2  + serverString;
  Serial.println(url);
  http.begin(url);                                      //Specify request destination
  int httpCode = http.GET();                            //Send the request  
  }
*/


void extractJson() {                //extract JSON string from HTTP data
  //Serial.println(httpResponse);
  // JSONLib 6 https://arduinojson.org/v6/api/jsonarray/
  int size = httpResponse.length() + 1;
  char jsonString[size];
  httpResponse.toCharArray(jsonString, size);
  StaticJsonDocument<200> jsonDoc;
  deserializeJson(jsonDoc, jsonString);// Deserialize the JSON document
  JsonArray dataObj = jsonDoc.as<JsonArray>();
  parseCommands(dataObj);
 } 



void parseCommands(JsonArray dataObj){
  if(dataObj[3] == 1){
    plan1();
  }
}
void plan1() {
  Serial.print("plan 1 uitvoeren");
  delay(1500);
  walkIn(0, 3, 255, 0, 0, 700); // steeltje bloem 1
  fadeWalk(4, 9, 0, 75, 255, 250);
  walkBack(0, 3, 0, 0, 0, 300); // steeltje bloem 1 uit
  delay(7000);
  fadeOutAll (4, 9, 0, 75, 255, 250);
}
