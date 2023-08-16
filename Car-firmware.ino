/* Car firmware */

/* Pins */

const int motorFront_IN_1 = 3;  // D3
const int motorFront_IN_2 = 4;  // D4
const int motorBack_IN_1 = 5;   // D5
const int motorBack_IN_2 = 6;   // D6

const int ledLightLeftPin = 8;   // D8
const int ledLightRightPin = 9;  // D9


/* Led light states */
int ledLeftLightState = 0;
int ledRightLightState = 0;


/* Motors */
void SpinMotor(int x_value) {
  if (x_value >= 512) {
    // Spin forward Front motor
    digitalWrite(motorFront_IN_1, HIGH);
    digitalWrite(motorFront_IN_2, LOW);

    // Spin forward Back motor
    digitalWrite(motorBack_IN_1, HIGH);
    digitalWrite(motorBack_IN_2, LOW);
    delay(100);
  }

  else if (x_value >= 201 && x_value <= 450) {  // Spin back Front motor
    digitalWrite(motorFront_IN_1, LOW);
    digitalWrite(motorFront_IN_2, HIGH);

    // Spin back Back motor
    digitalWrite(motorBack_IN_1, LOW);
    digitalWrite(motorBack_IN_2, HIGH);
    delay(100);
  }

  else if (x_value >= 451 && x_value <= 511) {  // Spin neutral Front motor
    digitalWrite(motorFront_IN_1, LOW);
    digitalWrite(motorFront_IN_2, LOW);

    // Spin neutral Back motor
    digitalWrite(motorBack_IN_1, LOW);
    digitalWrite(motorBack_IN_2, LOW);
    delay(100);
  }

  else if (x_value >= 0 && x_value <= 200) {
    // Stop Front motor
    digitalWrite(motorFront_IN_1, HIGH);
    digitalWrite(motorFront_IN_2, HIGH);

    // Stop back Back motor
    digitalWrite(motorBack_IN_1, HIGH);
    digitalWrite(motorBack_IN_2, HIGH);
    delay(100);
  }
}

void setup() {
  pinMode(motorFront_IN_1, OUTPUT);
  pinMode(motorFront_IN_2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  SpinMotor(10);
}
