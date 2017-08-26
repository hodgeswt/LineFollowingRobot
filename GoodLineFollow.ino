#include <Adafruit_MotorShield.h>
#include <Wire.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftRear = AFMS.getMotor(1);
Adafruit_DCMotor *rightRear = AFMS.getMotor(2);
Adafruit_DCMotor *leftFront = AFMS.getMotor(4);
Adafruit_DCMotor *rightFront = AFMS.getMotor(3);

// Global define of integer
int previousIrValue;

int loopNumber;

void setup() {
  Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftRear->setSpeed(150);
  leftRear->run(FORWARD);
  // turn on motor
  leftRear->run(RELEASE);
  //
  rightRear->setSpeed(150);
  rightRear->run(FORWARD);
  // turn on motor
  rightRear->run(RELEASE);
  //
  leftFront->setSpeed(150);
  leftFront->run(FORWARD);
  // turn on motor
  leftFront->run(RELEASE);
  //
  rightFront->setSpeed(150);
  rightFront->run(FORWARD);
  // turn on motor
  delay(100);
  rightFront->run(RELEASE);
  delay(1000);
  previousIrValue = analogRead(0);
  loopNumber = 0;
}
int leftValue;
int rightValue;
int centerValue;
int dampenedDrift;
void loop() {
  leftValue = analogRead(2); // gather sensor values
  rightValue = analogRead(0);
  centerValue = analogRead(1);

  dampenedDrift = (calculateDrift(leftValue, rightValue) / 40);
  Serial.println(dampenedDrift);
  if(dampenedDrift == 0) {
    motorsForward();
  }
  else if(dampenedDrift < -1) {
    pivotRight();
  }
  else if(dampenedDrift > 1) {
    pivotLeft();
  }
}

int calculateDrift(int left, int right) {
  int drift = (right - left);
  return(drift);
}

void motorsForward() {
  rightForward();
  leftForward();
}

void motorsBackward() {
  rightBackward();
  leftBackward();
}

void pivotLeft() {
  rightBackward();
  leftForward();
}

void pivotRight() {
  rightForward();
  leftBackward();
}

void rightForward() {
  rightRear->run(FORWARD);
  rightFront->run(FORWARD);
}

void leftForward() {
  leftRear->run(FORWARD);
  leftFront->run(FORWARD);
}

void rightBackward() {
  rightRear->run(BACKWARD);
  rightFront->run(BACKWARD);
}

void leftBackward() {
  leftRear->run(BACKWARD);
  leftFront->run(BACKWARD);
}
