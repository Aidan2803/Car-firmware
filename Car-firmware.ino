/* Car firmware */

const int joystick_pin_x = 0;     // A0
const int joystick_pin_y = 1;     // A1
const int joystick_pin_butt = 2;  // D2

const int motorFront_IN_1 = 3;  // D3
const int motorFront_IN_2 = 4;  // D4
const int motorBack_IN_1 = 5;   // D5
const int motorBack_IN_2 = 6;   // D6

/* Joysticks */

int JoyStickGetX() { return analogRead(joystick_pin_x); }

int JoyStickGetY() { return analogRead(joystick_pin_y); }

bool JoyStcikIsButtonPressed() { return digitalRead(joystick_pin_butt); }

/* Motors */

void SpinMotor(int x_value) {

  if(x_value >= 512){  
    // Spin forward Front motor
  digitalWrite(motorFront_IN_1, HIGH);
  digitalWrite(motorFront_IN_2, LOW);

  // Spin forward Back motor
  digitalWrite(motorBack_IN_1, HIGH);
  digitalWrite(motorBack_IN_2, LOW);
  delay(100);
    }

  else if (x_value >= 201 && x_value <= 450){  // Spin back Front motor
  digitalWrite(motorFront_IN_1, LOW);
  digitalWrite(motorFront_IN_2, HIGH);

  // Spin back Back motor
  digitalWrite(motorBack_IN_1, LOW);
  digitalWrite(motorBack_IN_2, HIGH);
  delay(100);
}

else if(x_value >= 451 && x_value <= 511){  // Spin neutral Front motor
  digitalWrite(motorFront_IN_1, LOW);
  digitalWrite(motorFront_IN_2, LOW);

  // Spin neutral Back motor
  digitalWrite(motorBack_IN_1, LOW);
  digitalWrite(motorBack_IN_2, LOW);
  delay(100);}

else if(x_value >= 0 && x_value <= 200){ 
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
  pinMode(joystick_pin_x, INPUT);
  pinMode(joystick_pin_y, INPUT);
  pinMode(joystick_pin_butt, INPUT_PULLUP);

  pinMode(motorFront_IN_1, OUTPUT);
  pinMode(motorFront_IN_2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.print(JoyStickGetX());
  Serial.print("\n");
  SpinMotor(10);
}
