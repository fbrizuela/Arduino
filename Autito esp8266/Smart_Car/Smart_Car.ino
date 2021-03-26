#define EnableA   15   // Enable motors Right        GPIO15(D8)        
#define EnableB   4    // Enable motors Left         GPIO4 (D2)
#define IN1  13        // L298N in1 motors Right     GPIO13(D7)
#define IN2  12        // L298N in2 motors Right     GPIO12(D6)
#define IN3  14        // L298N in3 motors Left      GPIO14(D5)
#define IN4  0         // L298N in4 motors Left      GPIO0 (D3)
                       //
#include <ESP8266WiFi.h>      //
#include <WiFiClient.h>       //
#include <ESP8266WebServer.h> //

String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "Smart Car Profe Pablo";
ESP8266WebServer server(80);

void setup() {
 
 pinMode(EnableA, OUTPUT);
 pinMode(EnableB, OUTPUT);  
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT); 
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ 

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(EnableA, speedCar);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(EnableB, speedCar);
  }

void goBack(){ 

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(EnableA, speedCar);

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(EnableB, speedCar);
  }

void goRight(){ 

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(EnableA, speedCar);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(EnableB, speedCar);
  }

void goLeft(){

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(EnableA, speedCar);

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(EnableB, speedCar);
  }

void goAheadRight(){
      
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(EnableA, speedCar/speed_Coeff);
 
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(EnableB, speedCar);
   }

void goAheadLeft(){
      
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(EnableA, speedCar);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(EnableB, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(EnableA, speedCar/speed_Coeff);

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(EnableB, speedCar);
  }

void goBackLeft(){ 

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(EnableA, speedCar);

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(EnableB, speedCar/speed_Coeff);
  }

void stopRobot(){  

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(EnableA, speedCar);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(EnableB, speedCar);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
