const int pirPin = 2;      // PIR sensor output pin
const int ledPin = 3;     // LED pin
const int buzzerPin = 12;  // Buzzer pin

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);      // Optional: to monitor sensor status
}

void loop() {
  int motionDetected = digitalRead(pirPin);

  if (motionDetected == HIGH) {
    digitalWrite(ledPin, HIGH);     // Turn ON LED
    digitalWrite(buzzerPin, HIGH);  // Turn ON Buzzer
    Serial.println("Motion Detected!");
  } else {
    digitalWrite(ledPin, LOW);      // Turn OFF LED
    digitalWrite(buzzerPin, LOW); 
    Serial.println("NO Motion ");
  }

  delay(100);  // Small delay to stabilize readings
}
 
