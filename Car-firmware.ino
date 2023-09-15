// Version 0.1.0 Initial implementation

/* Car firmware */
#include <RH_ASK.h>
#include <SPI.h>

#define DEBUG_ENABLED

RH_ASK driver;

const int JOYSTICK_XY_MSG_LENGTH{9};
const int JOYSTICK_BUTON_MSG_LENGTH{2};
const int BUTTON_MSG_LENGTH{2};

const int ANALOG_SIZE{4};

/* Pins */

/*Motor pins*/
const int motorFront_IN_1_pin{3}; // D3
const int motorFront_IN_2_pin{4}; // D4
const int motorBack_IN_1_pin{5};  // D5
const int motorBack_IN_2_pin{6};  // D6

const int servoFrontPin{}; // TBD

/*Led pins*/
const int ledLightLeftPin{8};  // D8
const int ledLightRightPin{9}; // D9

/*Hyper sonic pins*/
const int echoPin{};   // pin for the echo of a hypersonic sensor TBD
const int trigerPin{}; // pin fpr the triger of a hypersonic sensor TBD

/*Data*/
struct ReceivedData {
  int joystick_x{};
  int joystick_y{};
  bool joystick_button_state{};
  bool button_state{};
};

/* Led light states */
int ledLeftLightState{0};
int ledRightLightState{0};
int ledFrontLightState{0};

int Helper_ConvertArrToInt(int *array, int length) {
  int sum{};

  for (int i = 0; i < length; i++) {
    int pow{1};
    for (int j = 0; j < length - i - 1; j++) {
      pow *= 10;
    }
    int res = array[i] * pow;
    sum += res;
  }

  return sum;
}

/* Motors */
void SpinMotor(int x_value) {
  if (x_value >= 512) {
    // Spin forward Front motor
    digitalWrite(motorFront_IN_1_pin, HIGH);
    digitalWrite(motorFront_IN_2_pin, LOW);

    // Spin forward Back motor
    digitalWrite(motorBack_IN_1_pin, HIGH);
    digitalWrite(motorBack_IN_2_pin, LOW);
    delay(100);
  }

  else if (x_value >= 201 && x_value <= 450) { // Spin back Front motor
    digitalWrite(motorFront_IN_1_pin, LOW);
    digitalWrite(motorFront_IN_2_pin, HIGH);

    // Spin back Back motor
    digitalWrite(motorBack_IN_1_pin, LOW);
    digitalWrite(motorBack_IN_2_pin, HIGH);
    delay(100);
  }

  else if (x_value >= 451 && x_value <= 511) { // Spin neutral Front motor
    digitalWrite(motorFront_IN_1_pin, LOW);
    digitalWrite(motorFront_IN_2_pin, LOW);

    // Spin neutral Back motor
    digitalWrite(motorBack_IN_1_pin, LOW);
    digitalWrite(motorBack_IN_2_pin, LOW);
    delay(100);
  }

  else if (x_value >= 0 && x_value <= 200) {
    // Stop Front motor
    digitalWrite(motorFront_IN_1_pin, HIGH);
    digitalWrite(motorFront_IN_2_pin, HIGH);

    // Stop back Back motor
    digitalWrite(motorBack_IN_1_pin, HIGH);
    digitalWrite(motorBack_IN_2_pin, HIGH);
    delay(100);
  }
}

/*Data processing*/

ReceivedData receiveAndAnalyzeData() {
  int test_arr[13] = {0, 1, 2, 3, 5, 6, 7, 4, 1, 1, 0, 2, 1};
  int *converted_buff = test_arr;
  // int *converted_buff = ConvertBuff(
  //     buf, buflen); // [0][2][3][4][5][7][8][9][1] - integer array
  //                   // in example [0] - byte means message from the
  //                   // JoystickXY, rest of the array is a payload
  //                   // [2][3][4][5] for the X value (first 4 bytes after
  //                   header
  //                   // byte) [7][8][9][1] for the Y value (last 4 bytes)
  int jxy_msg_buff[JOYSTICK_XY_MSG_LENGTH];
  int jbutt_msg_buff[JOYSTICK_BUTON_MSG_LENGTH];
  int butt_msg_buff[BUTTON_MSG_LENGTH];

  Serial.println("=============================");
  Serial.println(converted_buff[JOYSTICK_XY_MSG_LENGTH + 1]);
  Serial.println(converted_buff[JOYSTICK_XY_MSG_LENGTH + 1 + 2]);
  Serial.println("=============================");

  for (int i = 1, j = 0; i < JOYSTICK_XY_MSG_LENGTH; i++, j++) {
    jxy_msg_buff[j] = converted_buff[i];
  }

  int jx_array[ANALOG_SIZE];
  int jy_array[ANALOG_SIZE];

  for (int i = 0; i < ANALOG_SIZE; i++) {
    jx_array[i] = jxy_msg_buff[i];
  }
  for (int i = ANALOG_SIZE, j = 0; i < ANALOG_SIZE * 2; i++, j++) {
    jy_array[j] = jxy_msg_buff[i];
  }

  ReceivedData rd{};

  rd.joystick_x = Helper_ConvertArrToInt(jx_array, ANALOG_SIZE);
  rd.joystick_y = Helper_ConvertArrToInt(jy_array, ANALOG_SIZE);
  rd.joystick_button_state = converted_buff[JOYSTICK_XY_MSG_LENGTH + 1];
  rd.button_state = converted_buff[JOYSTICK_XY_MSG_LENGTH + 1 + 2];

#ifdef DEBUG_ENABLED
  Serial.println("rd.joystick_x");
  Serial.println(rd.joystick_x);
  Serial.println("rd.joystick_y");
  Serial.println(rd.joystick_y);
  Serial.println("rd.joystick_button_state");
  Serial.println(rd.joystick_button_state);
  Serial.println("rd.button_state");
  Serial.println(rd.button_state);
#endif
};

void setup() {
  pinMode(motorFront_IN_1_pin, OUTPUT);
  pinMode(motorFront_IN_2_pin, OUTPUT);

  Serial.begin(9600);
  if (!driver.init()) {
    Serial.println("Driver init failed");
  }
}

void loop() { receiveAndAnalyzeData(); }
