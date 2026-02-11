#ifndef BT_RECV_H
#define BT_RECV_H

#include <BluetoothSerial.h>
#include <Arduino.h>
#include "config.h"

static BluetoothSerial SerialBT;

inline void initBTReceiver() {
  SerialBT.begin(BT_NAME);
  Serial.println("Bluetooth (slave) started and listening");
}

// Parse CSV line like: 10,20,30,40,50\n
inline bool readIncomingAngles(int *outAngles) {
  static String buf = "";
  while (SerialBT.available()) {
    char c = SerialBT.read();
    if (c == '\r') continue;
    if (c == '\n') {
      int idx = 0;
      int start = 0;
      for (int i = 0; i <= buf.length() && idx < NUM_FINGERS; ++i) {
        if (i == buf.length() || buf[i] == ',') {
          String token = buf.substring(start, i);
          outAngles[idx++] = token.toInt();
          start = i + 1;
        }
      }
      buf = "";
      return (idx == NUM_FINGERS);
    } else {
      buf += c;
    }
  }
  return false;
}

#endif
