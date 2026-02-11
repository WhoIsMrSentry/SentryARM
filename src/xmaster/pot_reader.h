#ifndef POT_READER_H
#define POT_READER_H

#include <Arduino.h>
#include "config.h"

inline void readAngles(int *angles) {
  for (int i = 0; i < NUM_FINGERS; ++i) {
    int v = analogRead(POT_PINS[i]);
    angles[i] = map(v, 0, 4095, 0, 180); // ESP32 ADC 12-bit (0-4095)
  }
}

#endif
