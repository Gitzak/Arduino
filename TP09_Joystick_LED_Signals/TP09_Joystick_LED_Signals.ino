const int joystickY = A1;

const int leds[5] = {3, 4, 5, 6, 7};

const int ledCount = 5;

// Direction
bool leftToRight = true;

// Animation
int currentStep = 0;

unsigned long lastStepTime = 0;
const unsigned long stepInterval = 150;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  unsigned long now = millis();
  int y = analogRead(joystickY);

  // Joystick changes direction
  // La zone centrale de 400 à 600 conserve le sens précédent et limite les changements parasites.
  if (y < 400) {
    leftToRight = false;

  } else if (y > 600) {
    leftToRight = true;
  }

  // Center: keep last direction

  // Update animation
  if (now - lastStepTime >= stepInterval) {
    lastStepTime = now;

    // Turn off all LEDs
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(leds[i], LOW);
    }

    // Calculate LED position
    int index;

    if (leftToRight) {
      index = currentStep;
    } else {
      // Inverse l'ordre des indices pour parcourir les mêmes LED dans l'autre sens.
      index = ledCount - 1 - currentStep;
    }

    // Turn on selected LED
    digitalWrite(leds[index], HIGH);

    currentStep++;

    if (currentStep >= ledCount) {
      currentStep = 0;
    }
  }
}
