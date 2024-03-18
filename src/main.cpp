#include <Arduino.h>
#include <OneWire.h>
#include <WiFi.h>
#include "env.h"
#include <HTTPClient.h> 
#include <ArduinoJson.h>
#include <DallasTemperature.h>



OneWire oneWire(temp_sensor);

DallasTemperature sensors(&oneWire);

unsigned int lastTime = 0;
unsigned int timerDelay = 2000;

void setup(){

  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  sensors.begin();
  sensors.setWaitForConversion(true);
  delay(1000);

   WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void patchTemp(float temp){
  HTTPClient http;
  String requestBody;
  String endpoint_temp = endpoint + temp;

  http.begin(endpoint_temp);
  http.addHeader("Content-Type","application/json");

    JsonDocument doc;

    doc ["temp"] = temp;
    doc.shrinkToFit();
    
    serializeJson(doc, requestBody);
  int httpResponseCode = http.PATCH(requestBody);
  http.PATCH(requestBody);
  Serial.print("Here is Response");
  Serial.println(requestBody);
  Serial.println(http.getString());
  Serial.println();
  http.end();
}

void getLightState(bool light)
{

  HTTPClient http;
  String requestBody;
  String endpoint_light = endpoint + light;

 
  
  http.begin(endpoint_light);  
  http.addHeader("Content-Type","application/json");

  int httpResponseCode = http.GET(); 

  if (httpResponseCode >0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String responseBody = http.getString();
    Serial.println(responseBody);
    

      JsonDocument doc;

      DeserializationError error = deserializeJson(doc, responseBody);

        if (error){
          Serial.print("deserializeJson()failed: ");
          Serial.println(error.c_str());
          return;
        }

          bool light = doc["light"];


          if(getLightState){
          digitalWrite(led_pin,HIGH);
          }else{
          digitalWrite(led_pin,LOW);
          } 
          }  
http.end();      
}





void loop(void){

delay(1000);
sensors.requestTemperatures();
sensors.requestTemperatures();
float x = sensors.getTempCByIndex(0);
Serial.println("Temperature: ");
Serial.println(x);
patchTemp(x);


}



// void setup() {

// Serial.begin(9600); 

//  

 
  
 
// }

// void loop() {
//   //Check WiFi connection status
//   if(WiFi.status()== WL_CONNECTED){

//     HTTPClient http;
  
//     // Establish a connection to the server
//     http.begin(endpoint);
    
//     // Specify content-type header
//     http.addHeader("Content-Type", "application/json");

//     // Serialise JSON object into a string to be sent to the API
//     StaticJsonDocument<64> doc;
//     char * httpRequestData;

//     doc["foo"] = "bar";
//     doc["fizz"] = "buzz";

// 		/* 

// 		{
// 			"foo": "bar",
// 			"fizz": "buzz"
// 		}

// 		*/
		
// 		// convert JSON document, doc, to string and copies it into httpRequestData
//     serializeJson(doc, httpRequestData);

//     // Send HTTP POST request
//     int httpResponseCode = http.POST(httpRequestData);
//     String http_response;

//     // check reuslt of POST request. negative response code means server wasn't reached
//     if (httpResponseCode>0) {
//       Serial.print("HTTP Response code: ");
//       Serial.println(httpResponseCode);

//       Serial.print("HTTP Response from server: ");
//       http_response = http.getString();
//       Serial.println(http_response);

//       StaticJsonDocument<1024> doc;

//       DeserializationError error = deserializeJson(doc, http_response);

//       if (error) {
//         Serial.print("deserializeJson() failed: ");
//         Serial.println(error.c_str());
//         return;
//       }

//       const char* variable_name = doc["key_name"];
//       int another_variable = doc["key_attribute"];
//       bool last_variable = doc["last_key"];
//     }
//     else {
//       Serial.print("Error code: ");
//       Serial.println(httpResponseCode);
//     }
   
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);
      
//     // Free resources
//     http.end();
//   }
//   else {
//     Serial.println("WiFi Disconnected");
//   }
// }


// void loop() 
// {

//  HTTPClient http; 
  
//   http.begin(endpoint);  
//   http.addHeader("api-key",api_key);

//   int httpResponseCode = http.GET(); 

//   if (httpResponseCode >0) {
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);
//     String responseBody = http.getString();
//     Serial.println(responseBody);
    

//       JsonDocument doc;

//       DeserializationError error = deserializeJson(doc, responseBody);

//         if (error){
//           Serial.print("deserializeJson()failed: ");
//           Serial.println(error.c_str());
//           return;
//         }
//         String message1 = doc["line_1"];
//         String message2 = doc["line_2"];

        
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print(message1);
//         lcd.setCursor(0, 1);
//         lcd.print(message2);


       
//       }
//       http.end();
//       delay(1000);  
// }
     
