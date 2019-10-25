int touch=9;//define capacitive touch sensor interface
int touchVal;//define digital variable val
int knobVal; // define analog rotation val
#define KNOB_PIN A1
#include <Mouse.h>
#include <Keyboard.h>
char up = 'w';
char down = 's';
char left = 'a';
char right = 'd';

int mouseSpeed = 20;


int xVal;
int yVal;

char inChar = Serial.read();
 
void setup() {
  // put your setup code here, to run once:
  pinMode(touch,INPUT);//define knock sensor to be output interface
  Serial.begin(9600); //Set serial baud rate to 9600 bps
  Mouse.begin();
  Keyboard.begin();
}
 
void loop() {
  // put your main code here, to run repeatedly:
  knobVal=analogRead(KNOB_PIN);//Read rotation sensor value from analog 0
  Serial.println(knobVal,DEC);//Print the value to serial port
  delay(100);
  touchVal=digitalRead(touch);//read the value of interface3 and evaluate it to val
  turnDirection();
  
  if(touchVal==HIGH)//when the knock sensor detect a signal, serial print
  {
    Serial.println("Touched uwu");
    Mouse.click();
  }
  else {
    Serial.println("Not touched uwu");
  }
 }
void turnDirection() {
  if(knobVal >= 0 & knobVal < 128) {
     Keyboard.releaseAll();
     Keyboard.press(down);
     yVal = mouseSpeed;
     Mouse.move(0, yVal, 0);
     
  }
  if(knobVal >= 128 && knobVal < 256) {
     Keyboard.releaseAll();
     Keyboard.press(down);
     Keyboard.press(left);
     yVal = mouseSpeed;
     xVal = -mouseSpeed;
     Mouse.move(xVal, yVal, 0);
  }
  if(knobVal >= 256 && knobVal < 384) {
     Keyboard.releaseAll();
     Keyboard.press(left);
     xVal = -mouseSpeed;
     Mouse.move(xVal, 0, 0);
  }
  if(knobVal >= 384 && knobVal < 512) {
     Keyboard.releaseAll();
     Keyboard.press(left);
     Keyboard.press(up);
     yVal = -mouseSpeed;
     xVal = -mouseSpeed;
     Mouse.move(xVal, yVal, 0);
  }
  if(knobVal >= 512 && knobVal < 640) {
     Keyboard.releaseAll();
     Keyboard.press(up);
     yVal = -mouseSpeed;
     Mouse.move(0, yVal, 0);
  }
  if(knobVal >= 640 && knobVal < 768) {
     Keyboard.releaseAll();
     Keyboard.press(up);
     Keyboard.press(right);
     yVal = -mouseSpeed;
     xVal = mouseSpeed;
     Mouse.move(xVal, yVal, 0);
  }
  if(knobVal >= 768 && knobVal < 896) {
     Keyboard.releaseAll();
     Keyboard.press(right);
     xVal = mouseSpeed;
     Mouse.move(xVal, 0, 0);
  }
  if(knobVal >= 896 && knobVal < 1024) {
     Keyboard.releaseAll();
     Keyboard.press(right);
     Keyboard.press(down);
     yVal = mouseSpeed;
     xVal = mouseSpeed;
     Mouse.move(xVal, yVal, 0);
     //
  }
}
// board spam: put cursor spam here
