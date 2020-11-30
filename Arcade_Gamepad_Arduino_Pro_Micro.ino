// Controller for 8 button arcade controller. OS detects as a regular USB gamepad.
// There will be 14 inputs: 4 Joystick directions, 8 game buttons, and a start and select button.
//
// Connect pins to ground
// Joystick pins: 2, 3, 4, 5
// Button pins: 6, 7, 8, 9, 10, 14, 15
// Start and Select pins: A0, A1
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Courtney Pitcher using Matthew Heironimus's library
// 2020-11-30
//--------------------------------------------------------------------

#include <Joystick.h>

#define NUMBER_OF_BUTTONS 10
#define NUMBER_OF_INPUTS (NUMBER_OF_BUTTONS + 4)

// Map of buttons to pins, first 4 are joystick pins and the rest are button pins
// 18 and 19 are A0 and A1 respectively in digital mode.
const int button_pin_map[NUMBER_OF_INPUTS] = 
  {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15, 18, 19};

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  NUMBER_OF_BUTTONS, 0,  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Joystick Pins
  pinMode(2, INPUT_PULLUP);  // Up
  pinMode(3, INPUT_PULLUP);  // Right
  pinMode(4, INPUT_PULLUP);  // Down
  pinMode(5, INPUT_PULLUP);  // Left
  // Initialize Button Pins
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);  // A0
  pinMode(19, INPUT_PULLUP);  // A1

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

// Last state of the buttons
int lastButtonState[NUMBER_OF_INPUTS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void loop() {

  // Read pin values
  for (int index = 0; index < NUMBER_OF_INPUTS; index++)
  {
    int currentButtonState = !digitalRead(button_pin_map[index]);
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // UP
          if (currentButtonState == 1) {
            Joystick.setYAxis(-1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 1: // RIGHT
          if (currentButtonState == 1) {
            Joystick.setXAxis(1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 2: // DOWN
          if (currentButtonState == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 3: // LEFT
          if (currentButtonState == 1) {
            Joystick.setXAxis(-1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        default: // Buttons
          Joystick.setButton(index - 4, currentButtonState);
          break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }

  delay(10);
}
