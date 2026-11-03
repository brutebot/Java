
#define BLYNK_TEMPLATE_ID "TMPL6IESRTGAe"
#define BLYNK_TEMPLATE_NAME "MQ2"
#define BLYNK_AUTH_TOKEN "p-0nEJ0VRyzJnSjZfufqCR8COoUPFKQP"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

// Wi-Fi credentials
char ssid[] = "Pooja";  // Replace with your WiFi SSID
char pass[] = "pooja123";  // Replace with your WiFi password

// Define the analog pin where the MQ-2 sensor's AO pin is connected
const int mq2Pin = A0;  // A0 is the analog pin on NodeMCU

// Define the threshold value
int threshold = 90;  // Set the threshold value for gas concentration

// Virtual Pin for Blynk LED widgets
#define STATUS_PIN V0   // For displaying sensor value
#define SAFE_PIN V1     // GREEN LED (safe)
#define UNSAFE_PIN V2   // RED LED (unsafe)

void setup() {
  // Start serial communication at 115200 baud rate
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  Blynk.begin(auth, ssid, pass);
  
  // Wait for the serial monitor to open
  delay(1000);
}

void loop() {
  // Read the analog value from the MQ-2 sensor
  int sensorValue = analogRead(mq2Pin);

  // Print the sensor value to the serial monitor
  Serial.print("MQ-2 Sensor Value: ");
  Serial.println(sensorValue);

  // Update the sensor value on V0 in the Blynk app
  Blynk.virtualWrite(STATUS_PIN, sensorValue);  // Send sensor value to V0
  
  // Turn off previous LED states
  Blynk.virtualWrite(SAFE_PIN, LOW);
  Blynk.virtualWrite(UNSAFE_PIN, LOW);

  // Check if the sensor value exceeds the threshold
  if (sensorValue > threshold) {
    // If above threshold, turn on the RED LED in Blynk and print status
    Blynk.virtualWrite(UNSAFE_PIN, HIGH);  // RED light (gas detected)
    Serial.println("Threshold Exceeded! RED LED on.");
      Blynk.logEvent("Gas concentration exceeded threshold! RED LED ON.");
  } else {
    // If below threshold, turn on the GREEN LED in Blynk and print status
    Blynk.virtualWrite(SAFE_PIN, HIGH);  // GREEN light (no gas detected)
    Serial.println("Threshold Not Exceeded! GREEN LED on.");
  }

  // Update Blynk app
  Blynk.run();

  // Wait for 1 second before reading again
  delay(1000);
}
