//  Final 360 Artifact
//  The creature's core will light up a different color depending on what it detects around the user
//  White neutral pulse if nothing is detected at all. Green if the user is being approached from the front.
//  If the user is approached from the back the reaction will differ in intensity.
//  The first state of detection is a yellow twinkle in the white glow, like a sparked interest.
//


// Include neopixel library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define pixelPin 3
#define numLights 16
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLights, pixelPin, NEO_GRB + NEO_KHZ800);
int fadeSpeed = 1;
int pulseDelay = 40;

//int buzzerPin = 1; Removed buzzer

//Variables for proximity sensors
const int pingPin = 6; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor
long duration, cm;

const int pingPin1 = 9; // Trigger Pin of Ultrasonic Sensor
const int echoPin1 = 10; // Echo Pin of Ultrasonic Sensor
long duration1, cm1;

const int pingPin2 = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPin2 = 13; // Echo Pin of Ultrasonic Sensor
long duration2, cm2;

/ Input pins for PIR sensors
int pirPin = A1;
// int pirPin1 = A3; Not being used

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  // pinMode(pirPin1, INPUT); Not being used
  // Initialize Neopixels
  strip.begin();
  strip.show();
}

void loop() {
  proximity();
  detection();
}

// Function to read values from the proximity sensors and print out the resulting number as a value in centimeters for ease of use and interpretation.
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
  Serial.print("cm  ");
  //Serial.println();

  pinMode(pingPin1, OUTPUT);
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin1, LOW);
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
  cm1 = microsecondsToCentimeters1(duration1);
  Serial.print(cm1);
  Serial.print("cm1  ");
  //Serial.println();

  // Last unused sensor
  //  pinMode(pingPin2, OUTPUT);
  //  digitalWrite(pingPin2, LOW);
  //  delayMicroseconds(2);
  //  digitalWrite(pingPin2, HIGH);
  //  delayMicroseconds(10);
  //  digitalWrite(pingPin2, LOW);
  //  pinMode(echoPin2, INPUT);
  //  duration2 = pulseIn(echoPin2, HIGH);
  //  cm2 = microsecondsToCentimeters2(duration2);
  //  Serial.print(cm2);
  //  Serial.print("cm2  ");
  //  Serial.println();
  //  delay(200);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

long microsecondsToCentimeters1(long microseconds) {
  return microseconds / 29 / 2;
}

//long microsecondsToCentimeters2(long microseconds) {
//  return microseconds / 29 / 2;
//}

// Neopixel light animation effects (snow, fade and runner) adapted from https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
void showStrip() {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.show();
#endif
}
void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < numLights; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
void setPixel(int Pixel, byte red, byte green, byte blue) {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
#endif
}
void fade(byte red, byte green, byte blue) {
  float r, g, b;
  for (int k = 5; k < 201; k = k + fadeSpeed) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
    delay(pulseDelay);
  }
  for (int k = 200; k >= 5; k = k - fadeSpeed) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
    delay(pulseDelay);
  }
}

void snow(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red, green, blue);

  int Pixel = random(numLights);
  setPixel(Pixel, 0xCC, 0x5f, 0x00);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel, red, green, blue);
  showStrip();
  delay(SpeedDelay);
}

void runner(byte red, byte green, byte blue, int WaveDelay) {
  int Position = 0;

  for (int j = 0; j < numLights * 2; j++)
  {
    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < numLights; i++) {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * 127 + 128;
      //setPixel(i,level,0,0);
      //float level = sin(i+Position) * 127 + 128;
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255)*red,
               ((sin(i + Position) * 127 + 128) / 255)*green,
               ((sin(i + Position) * 127 + 128) / 255)*blue);
    }
    showStrip();
    delay(WaveDelay);
  }
}
// End of code from https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/

// Detecting states of "danger". In increments of 50cm, as others approch the wearer, change state.
// Excepting the faraway movement, friendly movement and neutral states.
// Checks if motion has been triggered, and if so, then how far the triggering mass is.
void detection() {
  // Motion sensing values here
  int  val = digitalRead(pirPin);  // read input value
  //int  val2 = digitalRead(pirPin1);
  Serial.print(val);
  Serial.print("front");
  //Serial.print(val2);
  //Serial.print("back");
  Serial.println("");
  if (val == HIGH && cm1 > 200) {
    // Faraway movement detected - white with yellow sparks
    snow (0x10, 0x10, 0x10, 40, random(100, 500));
  } else if (val == HIGH && cm1 <= 200 && cm1 > 150 ) {
    // Yellow pulse
    fadeSpeed = 1;
    pulseDelay = 5;
    fade(0xCC, 0x5f, 0x00);
    Serial.println("yellow");
  } else if (val == HIGH && cm1 <= 150 && cm1 > 100 ) {
    //Yellow + red alternating spin
    runner(0xCC, 0x5f, 0x00, 20);  // yellow
    runner(0xCC, 0x3d, 0x00, 20);  // red
    Serial.println("alternating");
  } else if (val == HIGH && cm1 <= 100 && cm1 > 50 ) {
    // Red spin
    fadeSpeed = 1;
    pulseDelay = 0;
    runner(0xA6, 0x00, 0x00, 20);
    Serial.println("spin");
  } else if (val == HIGH && cm1 <= 50 && cm1 > 0 ) {
    // Urgent red pulse
    fadeSpeed = 1;
    pulseDelay = 0;
    fade(0xA6, 0x00, 0x00);
    Serial.println("urgent");
    delay(10);
  } else if (val == LOW && cm2 < 100 ) {
    // "Friendly" green pulse
    fadeSpeed = 1;
    pulseDelay = 10;
    fade(0x57, 0xCC, 0x25);
    Serial.println("friendly");
  } else {
    // Neutral white pulse
    fadeSpeed = 1;
    pulseDelay = 10;
    fade(0xFF, 0xFF, 0xFF);
    Serial.println("neutral");

  }
}
