/* Car firmware */

/* Pins */

const int joystickPinX = 0;     // A0
const int joystickPinY = 1;     // A1
const int joystickPinButt = 2;  // D2

const int motorFront_IN_1 = 3;  // D3
const int motorFront_IN_2 = 4;  // D4
const int motorBack_IN_1 = 5;   // D5
const int motorBack_IN_2 = 6;   // D6

const int buttonPin = 7;         // D7
const int ledLightLeftPin = 8;   // D8
const int ledLightRightPin = 9;  // D9

/* Button variables */
int buttonState = 0;
int lastButtonState = 0;
int lastDebounceTime = 0;
int debounceDelay = 0;

/* Led light states */
int ledLeftLightState = 0;
int ledRightLightState = 0;

/* Joysticks */

int JoyStickGetX() { return analogRead(joystickPinX); }

int JoyStickGetY() { return analogRead(joystickPinY); }

bool JoyStcikIsButtonPressed() { return digitalRead(joystickPinButt); }

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

void ButtonIsPressed() {
  int currentButtonState = digitalRead(buttonPin);
  Serial.println(currentButtonState);

  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentButtonState != buttonState) {
      buttonState = currentButtonState;

      if (buttonState == HIGH) {
        ledLeftLightState = !ledLeftLightState;
        ledRightLightState = !ledRightLightState;
      }
    }
  }

  digitalWrite(ledLightLeftPin, ledLeftLightState);
  digitalWrite(ledLightRightPin, ledRightLightState);

  lastButtonState = currentButtonState;
}

void setup() {
  pinMode(joystickPinX, INPUT);
  pinMode(joystickPinY, INPUT);
  pinMode(joystickPinButt, INPUT_PULLUP);

  pinMode(motorFront_IN_1, OUTPUT);
  pinMode(motorFront_IN_2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
//  Serial.print(JoyStickGetX());
//  Serial.print("\n");
  ButtonIsPressed();
  SpinMotor(10);
}
