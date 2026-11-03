#include <DHT.h>

#define DHTPIN D4       // Connect DHT DATA to D4 (GPIO2)
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(2000);          // Let serial monitor settle
  dht.begin();
  Serial.println("DHT11 Sensor Test Starting...");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\tTemperature: ");
    Serial.print(t);
    Serial.println(" °C");
  }

  delay(2000);
}

/*
void setup() {
  Serial.begin(9600);        // Start Serial at 9600 baud
  delay(1000);               // Give some time for Serial to start
  Serial.println("Hello from NodeMCU!");
}

void loop() {
  Serial.println("Looping...");
  delay(1000);
}*/
