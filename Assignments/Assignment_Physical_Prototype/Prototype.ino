#include <Stepper.h>

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int steps = 200;  // change this to fit the number of steps per revolution

int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;
 
Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);  
  
 long duration, cm;


void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(in1Pin, OUTPUT);
   pinMode(in2Pin, OUTPUT);
   pinMode(in3Pin, OUTPUT);
   pinMode(in4Pin, OUTPUT);
   motor.setSpeed(20);

}

void loop() {
proximity();
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void spin(){
if(cm > 200) {
   myStepper.step(0);

} else if(cm <= 200 && cm >= 150 ){
   myStepper.step(steps);

} else if(cm <= 150 && cm >= 100 ){
   myStepper.step(steps*2);

} else if(cm <= 100 && cm >= 50 ){
   myStepper.step(steps*3);

} else if(cm <= 50 && cm >= 0 ){
   myStepper.step(steps*4);

}
}

void proximity() {
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(100);
}
