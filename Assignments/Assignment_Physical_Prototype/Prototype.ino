// Elio's Motor things
#define MOTOR_EN_1_2  10
#define MOTOR_EN_3_4  11
#define MOTOR_IN1     9
#define MOTOR_IN2     8
#define MOTOR_IN3     12
#define MOTOR_IN4     13

#define forward  0
#define backward 1

#define slow   10
#define normal 5
#define fast   2

#define single_step   0
#define half_step     2

int speeed;
int direcshen;
int stepping;

int stepperVal = 11; // Number of steps needed for one revolution
int counter = 0; // Revolution counter

//Variables for proximity sensor
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
long duration, cm;

// Elio's stepper code, drives the motor in the necessary direction
void stepp(void) {

  digitalWrite(MOTOR_EN_1_2, HIGH);
  digitalWrite(MOTOR_EN_3_4, HIGH);

  if (direcshen == forward) {
    if (stepping == single_step) {
      digitalWrite(MOTOR_IN1, HIGH);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN3, LOW);
      digitalWrite(MOTOR_IN4, LOW);
      delay(speeed);
      digitalWrite(MOTOR_IN1, HIGH);
      digitalWrite(MOTOR_IN2, HIGH);
      digitalWrite(MOTOR_IN3, LOW);
      digitalWrite(MOTOR_IN4, LOW);
      delay(speeed);
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, HIGH);
      digitalWrite(MOTOR_IN3, LOW);
      digitalWrite(MOTOR_IN4, LOW);
      delay(speeed);
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, HIGH);
      digitalWrite(MOTOR_IN3, HIGH);
      digitalWrite(MOTOR_IN4, LOW);
      delay(speeed);
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN3, HIGH);
      digitalWrite(MOTOR_IN4, LOW);
      delay(speeed);
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN3, HIGH);
      digitalWrite(MOTOR_IN4, HIGH);
      delay(speeed);
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN3, LOW);
      digitalWrite(MOTOR_IN4, HIGH);
      delay(speeed);
      digitalWrite(MOTOR_IN1, HIGH);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN3, LOW);
      digitalWrite(MOTOR_IN4, HIGH);
      delay(speeed);
    }
  }

  if (direcshen == backward) {
    if (stepping == single_step) {
      digitalWrite(MOTOR_IN4, HIGH);
      digitalWrite(MOTOR_IN3, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN1, LOW);
      delay(speeed);
      digitalWrite(MOTOR_IN4, LOW);
      digitalWrite(MOTOR_IN3, HIGH);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN1, LOW);
      delay(speeed);
      digitalWrite(MOTOR_IN4, LOW);
      digitalWrite(MOTOR_IN3, LOW);
      digitalWrite(MOTOR_IN2, HIGH);
      digitalWrite(MOTOR_IN1, LOW);
      delay(speeed);
      digitalWrite(MOTOR_IN4, LOW);
      digitalWrite(MOTOR_IN3, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN1, HIGH);
      delay(speeed);
    }
  }
}

void setup() {

  Serial.begin(9600);
  //Serial.println("L293D Stepper motor test");

  pinMode(MOTOR_EN_1_2, OUTPUT);
  pinMode(MOTOR_EN_3_4, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);

}

//Run the code aye
void loop() {
  proximity();
  stepControl();
  Serial.println(counter);
}

//Moves the motor clockwise 
void forwardStep() {
  direcshen = forward;   // choose forward or backward
  speeed = slow;         // choose slow, normal or fast
  stepping = single_step;  // choose single, power or half step
  for (int i = 0; i <= stepperVal; i++) 
  {stepp();}
  counter++;
}
//Moves the motor counter-clockwise 
void backwardStep(){
  direcshen=backward;     // choose forward or backward
  speeed = slow;           // choose slow, normal or fast
  stepping = single_step;    // choose single, power or half step
  for (int i=0;i<=stepperVal;i++)
  {stepp();}
  counter--;
}

// Runs the proximity sensor and prints the value as a distance in CM
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
  //delay(50);
}

// Converts sensor value to CM 
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

// Function to run the stepper
// For every 50cm between 0 and 200cm the sensor detects, the motor will move an according amount of revolutions to open and shut
 
void stepControl() {
  if (cm > 200 && counter > 0) {
    backwardStep();
    
  } else if (cm <= 200 && cm > 150 ) {
    if (counter <3) {
      forwardStep();
    }
    if (counter >3) {
      backwardStep();
    }
  } else if (cm <= 150 && cm > 100 ) {
    if (counter <6) {
      forwardStep();
    }
    if (counter >6) {
      backwardStep();
    }
  } else if (cm <= 100 && cm > 50 ) {
    if (counter <9) {
      forwardStep();
    }
    if (counter >9) {
      backwardStep();
    }
  } else if (cm <= 50 && cm >= 0 ) {
    if (counter <12) {
      forwardStep();
  }
}
}
