#define echoPin 11 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 12 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int LMP = 4;
int LMN = 5;
int RMP = 6;
int RMN = 7;

void setup() {
  //Motor Pins are OUTPUT
  pinMode(LMP, OUTPUT);
  pinMode(LMN, OUTPUT);
  pinMode(RMP, OUTPUT);
  pinMode(RMN, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);
}

String  Direction;
void loop() {
    digitalWrite(trigPin, LOW);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    if(distance <10){
        Direction = "S";
    }else{
        Direction = Serial.readString();
    }
    if (Direction == "S"){
      //Stop
      digitalWrite(LMP, LOW);
      digitalWrite(LMN, LOW);
      digitalWrite(RMP, LOW);
      digitalWrite(RMN, LOW);
    }
    else if (Direction == "F"){
      //Move Forward
      digitalWrite(LMP, HIGH);
      digitalWrite(LMN, LOW);
      digitalWrite(RMP, LOW);
      digitalWrite(RMN, HIGH);
    } else if (Direction == "B"){
      //Move backward
      digitalWrite(LMP, LOW);
      digitalWrite(LMN, HIGH);
      digitalWrite(RMP, HIGH);
      digitalWrite(RMN, LOW);
    } else if (Direction == "L"){
      //Right Turn
      digitalWrite(LMP, LOW);
      digitalWrite(LMN, HIGH);
      digitalWrite(RMP, LOW);
      digitalWrite(RMN, HIGH);
    } else if (Direction == "R"){
      //Left Turn
      digitalWrite(LMP, HIGH);
      digitalWrite(LMN, LOW);
      digitalWrite(RMP, HIGH);
      digitalWrite(RMN, LOW);
    }
    
}
