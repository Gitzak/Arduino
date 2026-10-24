#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

// UID dyal Tag can access
const byte allowedUID[4] = {
  0x17, 0x4C, 0x31, 0x07
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  Serial.println("RFID Access Control Ready");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  bool authorized = true;

  // Seul un UID de quatre octets identique à celui autorisé est accepté.
  if (rfid.uid.size != 4) {
    authorized = false;
  } else {
    for (byte i = 0; i < 4; i++) {
      if (rfid.uid.uidByte[i] != allowedUID[i]) {
        authorized = false;
        break;
      }
    }
  }

  if (authorized) {
    Serial.println("Access Granted - Welcome!");
  } else {
    Serial.println("Access Denied!");
  }

  // Place la carte au repos et désactive le chiffrement du lecteur après le traitement.
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(1000);
}