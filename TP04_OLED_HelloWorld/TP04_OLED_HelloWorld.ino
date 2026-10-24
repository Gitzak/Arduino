#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// La valeur -1 indique que le pilote ne commande aucune broche de réinitialisation dédiée.
Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup() {
  Serial.begin(9600);

  // Initialise l'écran à l'adresse I²C 0x3C ; un échec bloque la suite du programme.
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED ERROR!");
    while (true);
  }

  Serial.println("OLED initialized!");

  display.clearDisplay();
  display.fillScreen(SSD1306_WHITE);
  // Transfère le tampon graphique vers l'écran après le remplissage.
  display.display();
}

void loop() {
}
