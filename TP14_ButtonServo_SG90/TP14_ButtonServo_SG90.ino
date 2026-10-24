#include <Servo.h>

const int servoPin = 9;
const int buttonPin = 2;

Servo MyServo;

// Button debounce
bool lastReading = LOW;
bool buttonState = LOW;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 60;

// Servo control
bool servoMoving = false;

unsigned long servoStartTime = 0;
const unsigned long servoWait = 1000;

void setup() {
  Serial.begin(9600);

  // Aucun rappel interne : le montage doit maintenir un niveau stable au repos.
  pinMode(buttonPin, INPUT);

  MyServo.attach(servoPin);
  MyServo.write(0);
}

void loop() {
  unsigned long currentTime = millis();

  // 1. Read button
  bool reading = digitalRead(buttonPin);

  // 2. Detect button changes
  if (reading != lastReading) {
    lastDebounceTime = currentTime;
  }

  // 3. Wait for stable button signal
  if (currentTime - lastDebounceTime >= debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;

      // 4. New button press
      if (buttonState == HIGH && !servoMoving) {
        MyServo.write(180);

        servoStartTime = currentTime;
        servoMoving = true;

        Serial.println("Servo -> 180");
      }
    }
  }

  lastReading = reading;

  // 5. Return servo after 1 second
  // Le retour est temporisé sans bloquer la lecture du bouton.
  if (servoMoving && currentTime - servoStartTime >= servoWait) {

    MyServo.write(0);
    servoMoving = false;

    Serial.println("Servo -> 0");
  }
}
