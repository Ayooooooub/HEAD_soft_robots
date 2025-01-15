#include <Servo.h>

Servo myservo;                     // create servo object to control a servo
int sensorPin = 8;                 // PIR sensor connected to pin 8
int servoPin = 7;                  // Servo connected to pin 7
int sendPin = 9;                   // Pin to send signal to other Arduino
bool motionDetected = false;       // keeps track of motion state
unsigned long lastMotionTime = 0;  // stores the last time motion was detected
const int motionDelay = 5000;      // 5 seconds delay

void setup() {
  myservo.attach(servoPin);        // attach servo to pin 7
  pinMode(sensorPin, INPUT);       // set PIR sensor pin as input
  pinMode(sendPin, OUTPUT);        // set send pin as output
  myservo.write(100);             // initialize servo to -180 degrees
}

void loop() {
  int sensorState = digitalRead(sensorPin);  // read PIR sensor state

  if (sensorState == HIGH) {  // motion detected
    if (!motionDetected) {    // only act if it's a new motion event
      motionDetected = true;
      myservo.write(0);  // move servo to 180 degrees
      digitalWrite(sendPin, HIGH);  // send signal to other Arduino
    }
    lastMotionTime = millis();  // update the last motion time
  } else {                      // no motion detected
    if (motionDetected && millis() - lastMotionTime > motionDelay) {
      motionDetected = false;
      myservo.write(100);  // move servo back to -180 degrees
      digitalWrite(sendPin, LOW);  // stop signal to other Arduino
    }
  }
}
