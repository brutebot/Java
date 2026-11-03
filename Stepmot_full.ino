// Full-step sequence for 28BYJ-48 motor
int IN1 = D1; // GPIO5
int IN2 = D2; // GPIO4
int IN3 = D3; // GPIO0
int IN4 = D4; // GPIO2

int stepDelay = 5; // milliseconds between steps

// 4-step full-step sequence
int fullStepSequence[4][4] = {
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Rotate 1 revolution clockwise (~2048 full steps for 28BYJ-48)
  for (int i = 0; i < 2048; i++) {
    stepMotor(i % 4);
    delay(stepDelay);
  }

  delay(1000);

  // Rotate 1 revolution counter-clockwise
  for (int i = 2047; i >= 0; i--) {
    stepMotor(i % 4);
    delay(stepDelay);
  }

  delay(1000);
}

void stepMotor(int step) {
  digitalWrite(IN1, fullStepSequence[step][0]);
  digitalWrite(IN2, fullStepSequence[step][1]);
  digitalWrite(IN3, fullStepSequence[step][2]);
  digitalWrite(IN4, fullStepSequence[step][3]);
}
