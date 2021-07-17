#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h> // allows us to connect to wifi using its methods
#include <ArduinoJson.h>
//#include <HTTPClient.h> // allows us to send HTTP requests using its methods

#define SENSOR D1 
#define SENSOR2 D6
#define ACTION D2 
#define ACTION2 D5 
 
const char* ssid     = "RouWiFi";
const char* password = "MiserableLife";
bool sensorVal = true;
bool sensorVal2 = true;
char* id[2]= {"00060012","00060011"};
 
void setup () {
 
Serial.begin(115200);
pinMode(SENSOR, INPUT);
pinMode(ACTION, OUTPUT);
pinMode(ACTION2, OUTPUT);
Serial.print("Connecting to ");
Serial.print(ssid);
Serial.print(" ");
connectToWifi();
}


void connectToWifi(){
  int timeout = 10;
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(500);
    Serial.print(".");
    timeout--;
  }
  if(WiFi.status()== WL_CONNECTED)
  {
    Serial.println();
    Serial.println("WiFi connected");  
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    digitalWrite(ACTION2,HIGH);
    Serial.println();
  }
  else{
    Serial.println("Could not connect to WiFi. Please try again!");
  }
}

void postDataToServer(int i){
  
  // Block until we are able to connect to the WiFi access point  
  while(WiFi.status() != WL_CONNECTED)
        WiFi.reconnect();
  Serial.println("Connecting to server ...");  
  HTTPClient http;   
  http.begin("http://desolate-castle-57587.herokuapp.com/update");  
  http.addHeader("Content-Type", "application/json");            
  StaticJsonDocument<200> doc;
  // Add values in the document     
  doc["id"] = id[i];
  if(i == 0)
    doc["empty"] = sensorVal;
  else
    doc["empty"] = sensorVal2;
  String requestBody;
  serializeJson(doc, requestBody);
  Serial.println(requestBody);
  if(WiFi.status() == WL_CONNECTED)
      Serial.println("Connected to WiFi and Server. Patching JSON Object");
  else
    {
      int timeout = 10;
      while(timeout>0 && WiFi.status() != WL_CONNECTED)
      {
        WiFi.reconnect();
        timeout--;
      }
    }
  // connectToWifi();        
  int httpResponseCode = http.PATCH(requestBody);
  String response = http.getString();  
  if(httpResponseCode>0){         
    String response = http.getString();                       
    Serial.println(httpResponseCode);   
    Serial.println(response);
  }
  else { 
   Serial.printf("Error occurred while sending HTTP PATCH: %s\n", http.errorToString(httpResponseCode).c_str()); 
  } 
}
 
void loop() {
 
int L =digitalRead(SENSOR);// read the sensor 
int L2 = digitalRead(SENSOR2);  
  if(L == LOW){
    Serial.println("1: Obstacle detected");
    digitalWrite(ACTION,HIGH);
    sensorVal= false;
  }else if (L == HIGH){
     Serial.println("1: All clear");
     digitalWrite(ACTION,LOW);   
     sensorVal= true;
     }
  if(L2 ==LOW)
    {
      Serial.println("2: Obstacle detected");
      sensorVal2 = false;
    }
  else if(L2 == HIGH)
  {
    Serial.println("2: All clear");
    sensorVal2 = true;
  }
  int i = 0;
  for(i=0;i<2;i++)
    postDataToServer(i);
  if(WiFi.status()== WL_CONNECTED)
  {
    digitalWrite(ACTION2,HIGH);
  }
  else{
    digitalWrite(ACTION2,HIGH);    
  }

  delay(5000);    //Send a request every 30 seconds
 
}
