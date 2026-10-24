const byte segmentPins[7] = {
  2, 3, 4, 5, 6, 7, 8
};

const byte digitPins[4] = {
  12, 11, 10, 9
};

// A B C D E F G
const byte numbers[10][7] = {
  // A B C D E F G
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 1, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 0, 1, 1 }   // 9
};

int counter = 9999;

unsigned long lastCountTime = 0;
unsigned long lastDisplayTime = 0;

const unsigned long countInterval = 1000;
const unsigned long refreshInterval = 2;

byte activeDigit = 0;

void setup() {
  Serial.begin(9600);

  // All digits OFF
  for (byte i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH);
    pinMode(digitPins[i], OUTPUT);
  }

  // All segments OFF
  for (byte i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
    pinMode(segmentPins[i], OUTPUT);
  }

  Serial.println("Countdown started");
}

void loop() {
  unsigned long now = millis();

  if (counter > 0 && now - lastCountTime >= 1000) {
    // Avance l'échéance d'une seconde pour conserver la cadence du décompte.
    lastCountTime += 1000;
    counter--;

    Serial.print("Counter: ");
    Serial.println(counter);
  }

  if (now - lastDisplayTime >= 2) {
    lastDisplayTime = now;
    showNextDigit();
  }
}

// Le multiplexage active un seul chiffre à la fois ; ses segments sont actifs à HIGH.
void showNextDigit() {

  // Désactive les chiffres avant de changer les segments pour éviter les affichages parasites.
  // Turn OFF all digits
  for (byte i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH);
  }

  int digits[4] = {
    (counter / 1000) % 10,
    (counter / 100) % 10,
    (counter / 10) % 10,
    counter % 10
  };

  byte number = digits[activeDigit];

  // Set segments
  for (byte i = 0; i < 7; i++) {
    digitalWrite(
      segmentPins[i],
      numbers[number][i] ? HIGH : LOW);
  }

  // Turn ON selected digit
  digitalWrite(digitPins[activeDigit], LOW);

  activeDigit = (activeDigit + 1) % 4;
}
