#ifndef XMASTER_CONFIG_H
#define XMASTER_CONFIG_H

#include <Arduino.h>

const char* BT_NAME = "ConHand_Master";
const int NUM_FINGERS = 5;
const int POT_PINS[NUM_FINGERS] = {34, 35, 32, 33, 25};
const unsigned long SEND_INTERVAL_MS = 50; // ms

#endif
