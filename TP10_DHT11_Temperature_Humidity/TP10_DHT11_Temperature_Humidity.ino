#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Une valeur NaN indique une lecture invalide : abandonne cet échantillon avant l'affichage.
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 read failed!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println("----------------");

  // Espace les cycles de mesure de deux secondes pour le DHT11.
  delay(2000);
}