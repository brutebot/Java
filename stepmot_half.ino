// Half-step sequence for 28BYJ-48 motor
int IN1 = D1;
int IN2 = D2;
int IN3 = D3;
int IN4 = D4;

int stepDelay = 5; // milliseconds between steps

// 8-step half-step sequence
int halfStepSequence[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Rotate 1 revolution clockwise (approx 4096 half-steps for 28BYJ-48)
  for (int i = 0; i < 4096; i++) {
    stepMotor(i % 8);
    delay(stepDelay);
  }

  delay(1000);

  // Rotate 1 revolution counter-clockwise
  for (int i = 4095; i >= 0; i--) {
    stepMotor(i % 8);
    delay(stepDelay);
  }

  delay(1000);
}

void stepMotor(int step) {
  digitalWrite(IN1, halfStepSequence[step][0]);
  digitalWrite(IN2, halfStepSequence[step][1]);
  digitalWrite(IN3, halfStepSequence[step][2]);
  digitalWrite(IN4, halfStepSequence[step][3]);
}
