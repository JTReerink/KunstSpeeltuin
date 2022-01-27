/*
 * Wifi Network
 * insert here your own network Wifi Credentials 
*/


//  const char* ssid     = "Wifi?"; // wifi lan
//  const char* password = "J@ap29E12"; // wifi lan

const char* ssid     = "Medialab"; // wifi lan
const char* password = "Mediacollege2"; // wifi lan

String server  = "http://schw.hosts1.ma-cloud.nl"; // deployment server
String path          = "/jaap/control.json"; // path to file with control data 
String path2         = "/jaap/jsonWrite.php?src=html&data="; // path to file
String httpResponse;// response from webserver


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
