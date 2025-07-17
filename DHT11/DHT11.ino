#include "DHT.h"

#define DHTPIN 7        // GPIO where DHT11 data is connected
#define DHTTYPE DHT11   // Define sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(1000);
  Serial.println("DHT11 Sensor Initialized.");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(1000); // Read every 1 seconds
}
