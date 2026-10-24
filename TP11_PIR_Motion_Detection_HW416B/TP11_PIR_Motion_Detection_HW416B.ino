const int pirPin = 2;

void setup() {
  Serial.begin(9600);

  pinMode(pirPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int motion = digitalRead(pirPin);

  // Le capteur signale une détection par un niveau HIGH sur sa sortie numérique.
  if (motion == HIGH) {
    Serial.println("Motion detected!");
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    Serial.println("No motion");
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(500);
}