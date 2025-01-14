#include <Servo.h>

int servoPin = 7; // Servo connected to pin 7
Servo myservo;    // create servo object to control a servo

int outsidePin = 10; // Pin to receive signal from Outside Calystegia
bool outsideState = false;

int insidePin = 8; // PIR sensor for Inside Calystegia
bool insideState = false;

int jealousyDelay = 15000;          // 15 seconds delay for jealousy
unsigned long jealousyTime = 0;     // Timer for jealousy
bool jealousyState = false;         // Tracks whether Jealousy Mode is active
bool jealousyOpen = false;          // tracks whether jealousy flower is open
unsigned long jealousyOpenTime = 0; // how long it's been since jealousy opened or closed
int jealousyOpenDelay = 500;        // how long jealousy stays open or closed

void setup()
{
  Serial.begin(9600);           // Start serial monitor for debugging
  myservo.attach(servoPin);     // Attach servo to pin 7
  pinMode(outsidePin, INPUT);   // Set receive pin as input
  pinMode(insidePin, INPUT);    // Set motion sensor pin as input
  openFlower();                 // Initialize servo to "open" position
  pinMode(LED_BUILTIN, OUTPUT); // Optional: LED for debugging
}

void loop()
{
  int outsideSensor = digitalRead(outsidePin);  // Read signal from Outside Calystegia
  int insideSensor = digitalRead(insidePin);    // Read motion from Inside Calystegia

  // Update states for outside motion
  if (outsideSensor && !outsideState) {
    outsideState = true;
    Serial.println("Outside ON");
    closeFlower();
  } else if (!outsideSensor && outsideState) {
    outsideState = false;
    Serial.println("Outside OFF");
    openFlower();
  }

  // Update states for inside motion
  if (insideSensor) {
    jealousyTime = millis();  // Reset jealousy timer when motion detected inside
    if (jealousyState) {
      jealousyState = false;  // Exit Jealousy Mode
      Serial.println("Jealousy OFF");

      openFlower();
    }
  }

  if (insideSensor && !insideState) {
    insideState = true;
    Serial.println("Inside ON");
  } else if (!insideSensor && insideState) {
    insideState = false;
    Serial.println("Inside OFF");
  }

  // Activate Jealousy Mode if:
  // 1. Enough time has passed since last inside motion.
  // 2. Movement is detected outside.
  if (!jealousyState && outsideSensor && millis() - jealousyTime > jealousyDelay) {
    jealousyState = true;  // Enter Jealousy Mode
    Serial.println("Jealousy ON");
  }

  // Handle Jealousy Mode behavior
  if (jealousyState) {
  jealousyBehaviour();
  }

  delay(10); // Small delay to stabilize loop
}

void jealousyBehaviour()
{
  
  // if 500 millis have passed
  if (millis() - jealousyOpenTime > jealousyOpenDelay)
  {
    // change opened to closed or closed to open
    jealousyOpen = !jealousyOpen;
    jealousyOpenTime = millis();

    if (jealousyOpen)
    {
      openFlower();
    }
    if (!jealousyOpen)
    {
      closeFlower();
    }

    // new open delay: random
    // jealousyOpenDelay = random (100, 1000);

    // new open delay: sinun
    float period = 5; // s
    float freq = 1.0 / period;
    float time = millis() / 1000.0;
    jealousyOpenDelay = map(sin(TWO_PI * freq * time) * 1000, -1000, 1000, 100, 1000);

  }

  /*
    myservo.write(0);                 // Example: Oscillate or perform actions in jealousy
    digitalWrite(LED_BUILTIN, HIGH);  // Optional: Turn on built-in LED
    delay(jealousyOpenDelay);

    myservo.write(100);
    digitalWrite(LED_BUILTIN, LOW);  // Optional: Turn off LED
    delay(jealousyOpenDelay);
  */
}


void openFlower() {
  myservo.write(100);
}

void closeFlower () {
  myservo.write(0);
}