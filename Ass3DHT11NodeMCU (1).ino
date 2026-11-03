#include <ESP8266WiFi.h>
#include <DHT.h>

// Wi-Fi credentials
const char* ssid = "Pooja";
const char* pass = "pooja123";

// ThingSpeak server and API details
const char* host = "api.thingspeak.com";
const char* apiKey = "OQ02HVI6XOPIARBH";
const char* readapiKey = "OWOHNRI0CYQ5S6CY";

// DHT sensor setup
#define DHTPIN D4         // Connect DHT11 data pin to D2 on NodeMCU
#define DHTTYPE DHT11     // Define sensor type as DHT11
DHT dht(DHTPIN, DHTTYPE); // Create DHT object

void setup() {
  Serial.begin(115200);
  delay(10);
  
  dht.begin(); // Initialize DHT sensor

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  // Read values from DHT11 sensor
  float temperature = dht.readTemperature(); // Default is Celsius
  float humidity = dht.readHumidity();

  // Check if reading failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(5000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Create WiFi client
  WiFiClient client;

  // Connect to ThingSpeak
 // https://api.thingspeak.com/update?api_key=4XG3WRHNVOWT8YL9&field1=76&field2=102
  if (client.connect(host, 80)) {
    String url = "/update?api_key=" + String(apiKey) +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(humidity);

    Serial.print("Requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
  }
  
  client.stop();  // Close the connection
  delay(16000);   // Wait at least 15 sec for next update
  
}
