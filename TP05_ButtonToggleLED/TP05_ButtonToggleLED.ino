const int buttonPin = 2;
const int ledPin = 9;

// led state off
bool ledState = false;
bool lastReading = HIGH;
// button state HIGHT
bool buttonState = HIGH;

unsigned long lastDebounceTime = 0;
// after an delay
const unsigned long debounceDelay = 50;

void setup() {
  // Avec le rappel interne, un appui reliant le bouton à la masse produit LOW.
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  // set led OFF
  digitalWrite(ledPin, LOW);
}

void loop() {
  // on click buttonPin = LOW -> reading = LOW
  bool reading = digitalRead(buttonPin);

  // LOW != HIGH ---> yes true
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  // Valide le changement seulement après 50 ms sans nouvelle variation du signal.
  if (millis() - lastDebounceTime > debounceDelay) {

    // LOW != HIGH ---> yes true
    if (reading != buttonState) {
      // buttonState = LOW
      buttonState = reading;

      // yes true
      if (buttonState == LOW) {
        // TRUE != FALSE 
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }
    }
  }

  lastReading = reading;
}
