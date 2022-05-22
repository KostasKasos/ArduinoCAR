                                      /* Included files needed for the program */
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>          // Include the webserver library needed to be used, it4s like Apache webserver 

#define enA   14                                      -//* Macro definition #
#define enB   12                               //    * The following part defines the mapping of the ports between the Board and the external components Motor controller,
#define IN_1  15                                      //* GPIO # General Purpose Input Output (PIN out)
#define IN_2  13                                     // Enable/speed motors Right        GPIO14(D5) 
#define IN_2  13                                    // Enable/speed motors Left         GPIO12(D6)
#define IN_3  2                                     // L298N in1 motors Right           GPIO15(D8)
#define IN_4  0                                   // L298N in2 motors Right           GPIO13(D7)
                                                // L298N in4 motors Left            GPIO0(D3)

                                   
String command;                                      //String to store app command state.
int speedCar = 800;                                  // 400 - 1023. PWM control

/* 
1023 =  5V --| 1000 Rotation/minute RPM
512 = 2.5 V -- 500 RPM


X * 5 = 1023 * 2.5
X =(1023*2.5 )/5
0 = 0v


*/   
int speed_Coeff = 3;                             // todo/ understand this 
const char* ssid = "Arduino-esp8266mod Car";
ESP8266WebServer server(80);                     //HTTP server port 80 

void setup() {
 pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
 Serial.begin(115200);                           // Serial is the communication protocol between the microcontroller and the ESP module , 115200 is the bauderate, send data up 1 meter, 9600 send data up to 4 meters
                                                            
  WiFi.mode(WIFI_AP);                           // Opening an Access Point
  WiFi.softAP(ssid);                            // Set the access point name

  IPAddress myIP = WiFi.softAPIP();            // It would gets the IP of the current ESP module
  Serial.print("AP IP address: ");             // printing to the uart monitor
  Serial.println(myIP);                        // The IP value 192.168.4.1
 
  server.on ( "/", HTTP_handleRoot );         // Turn on the WEB-server listner
  server.onNotFound ( HTTP_handleRoot );      // it4s the webpage that will be opened in case of error
  server.begin();                             // starting the Web server  
}

void forword(){ 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(enA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(enB, speedCar);
  }
void backword(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(enA, speedCar);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);                                                      
      analogWrite(enB, speedCar);
  }
void turnRight(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(enA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(enB, speedCar);
  }

void turnLeft(){
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(enA, speedCar);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(enB, speedCar);
  }

void Stop(){  
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(enA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);                         // 5v / 0 V / ON / OFF
      analogWrite(enB, speedCar);                      // Setting the PWM speed
 }

void loop() {
      server.handleClient();                            // listen and handle any requests 
      command = server.arg("State");                    // extracting the command from the client
      if (command == "F") forword();
      else if (command == "B") backword();
      else if (command == "L") turnLeft();
      else if (command == "R") turnRight();
      else if (command == "S") Stop();
}
void HTTP_handleRoot(void) {
if( server.hasArg("State") ){
       Serial.println(server.arg("State"));             // print for debug purpose 
  }
  server.send ( 200, "text/html", "" );                 // return an empty page / response
  delay(1);                                             // just sleep sometime to prevent service deny in case of many requests received in the same time
}
