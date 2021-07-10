#include <ESP8266WiFi.h> // allows us to connect to wifi using its methods
//#include <ESP8266HTTPClient.h> // allows us to send HTTP requests using its methods
 
const char* ssid     = "SSID_HERE";
const char* password = "PASSWORD_HERE";
 
void setup () {
 
Serial.begin(115200);
WiFi.begin(ssid,password); // SSID AND PW
 
while (WiFi.status() != WL_CONNECTED) {
 // wait until a connection is established
delay(1000);
Serial.print("Connecting..");
 
}
 
}
 
void loop() {
 
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
//HTTPClient http;  //Declare an object of class HTTPClient
// 
//http.begin("www.Google.com");  //Specify request destination
//int httpCode = http.GET();//Send the request
// 
//if (httpCode > 0) { //Check the returning code
// 
//String payload = http.getString();   //Get the request response payload
//Serial.println(payload);                     //Print the response payload
// 
//}
// 
//http.end();   //Close connection
Serial.println("Connected.");
//create a json object from the microcontroller values and ID, and send it to https://desolate-castle-57587.herokuapp.com
 
}
 
delay(30000);    //Send a request every 30 seconds
 
}
