#ifndef XSLAVE_CONFIG_H
#define XSLAVE_CONFIG_H

#include <Arduino.h>

const char* BT_NAME = "ConHand_Master"; // master name must match
const int NUM_FINGERS = 5;
const int SERVO_PINS[NUM_FINGERS] = {18, 19, 21, 22, 23};

#endif
