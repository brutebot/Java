const int ledPin = 3;
const int buttonPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin, HIGH );  // LED ON when button pressed
  } else {
    digitalWrite(ledPin, LOW);   // LED OFF when button released
  }
}
