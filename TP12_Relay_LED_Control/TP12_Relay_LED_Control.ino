const int relayPin = 7;

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Active le relais pendant 500 ms, puis le désactive pendant 500 ms.
  digitalWrite(relayPin, HIGH);
  delay(500);

  // Désactive le relais pendant 500 ms, puis le réactive pendant 500 ms.
  digitalWrite(relayPin, LOW);
  delay(500);
}
