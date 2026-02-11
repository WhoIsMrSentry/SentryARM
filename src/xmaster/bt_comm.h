#ifndef BT_COMM_H
#define BT_COMM_H

#include <BluetoothSerial.h>
#include <Arduino.h>
#include "config.h"

static BluetoothSerial SerialBT;

inline void initBT() {
  SerialBT.begin(BT_NAME);
  Serial.println("Bluetooth started as ");
  Serial.println(BT_NAME);
}

inline void sendAngles(int *angles) {
  // Basit CSV: a0,a1,a2,a3,a4\n
  for (int i = 0; i < NUM_FINGERS; ++i) {
    SerialBT.print(angles[i]);
    if (i < NUM_FINGERS - 1) SerialBT.print(',');
  }
  SerialBT.print('\n');
}

#endif
