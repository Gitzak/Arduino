#include <Servo.h>

const int servoPin = 9;
const int touchPin = 2;

Servo MyServo;

// Servo settings
const int minAngle = 0;
const int maxAngle = 90;

float servoSpeed = 120.0; // Degrees per second

const unsigned long servoWait = 1000;

// Servo states
enum ServoState {
  IDLE,
  FORWARD,
  WAIT,
  BACK
};

ServoState state = IDLE;

int angle = minAngle;

// Timing
unsigned long lastStepTimeUs = 0;
unsigned long waitStartTime = 0;

// Touch sensor
bool lastTouch = LOW;

void setup() {
  Serial.begin(115200);

  pinMode(touchPin, INPUT);

  MyServo.attach(servoPin);
  MyServo.write(minAngle);

  Serial.println("Servo ready!");
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long currentTimeUs = micros();

  bool touch = digitalRead(touchPin);

  // Calculate timing from speed
  // Chaque pas vaut un degré : cet intervalle convertit la vitesse en microsecondes par pas.
  unsigned long stepIntervalUs =
    (unsigned long)(1000000.0 / servoSpeed);

  // Detect new touch
  // Un front montant déclenche un cycle uniquement lorsque le servo est au repos.
  if (touch == HIGH && lastTouch == LOW && state == IDLE) {
    state = FORWARD;
    lastStepTimeUs = currentTimeUs;

    Serial.println("START");
  }

  lastTouch = touch;

  // Move forward
  // Les états et horodatages permettent de lire le capteur pendant le déplacement et la pause.
  if (state == FORWARD) {
    if (currentTimeUs - lastStepTimeUs >= stepIntervalUs) {
      lastStepTimeUs = currentTimeUs;

      angle++;
      MyServo.write(angle);

      if (angle >= maxAngle) {
        state = WAIT;
        waitStartTime = currentTime;
        Serial.println("Reached target");
      }
    }
  }

  // Wait at maximum angle
  if (state == WAIT) {
    if (currentTime - waitStartTime >= servoWait) {
      state = BACK;
      lastStepTimeUs = currentTimeUs;

      Serial.println("Returning...");
    }
  }

  // Move backward
  if (state == BACK) {
    if (currentTimeUs - lastStepTimeUs >= stepIntervalUs) {
      lastStepTimeUs = currentTimeUs;

      angle--;
      MyServo.write(angle);

      if (angle <= minAngle) {
        state = IDLE;
        Serial.println("DONE");
      }
    }
  }
}
