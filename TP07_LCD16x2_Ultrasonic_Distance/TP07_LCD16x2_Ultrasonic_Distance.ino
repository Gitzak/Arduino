#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 9;
const int echoPin = 10;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(trigPin, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("DISTANCE:");
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  // Limite l'attente de l'écho à 30 ms ; pulseIn renvoie zéro en cas de dépassement.
  unsigned long duration = pulseIn(echoPin, HIGH, 30000);

  lcd.setCursor(0, 1);

  if (duration == 0) {
    lcd.print("No echo         ");
  } else {
    // Convertit le temps aller-retour en centimètres avec une vitesse du son de 0,0343 cm/µs.
    float distance = duration * 0.0343 / 2.0;

    lcd.print(distance, 1);
    lcd.print(" cm        ");
  }

  delay(200);
}
