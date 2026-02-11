#include <Arduino.h>
#include "config.h"
#include "pot_reader.h"
#include "bt_comm.h"

int angles[NUM_FINGERS];
unsigned long lastSend = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
  initBT();
}

void loop() {
  readAngles(angles);
  unsigned long now = millis();
  if (now - lastSend >= SEND_INTERVAL_MS) {
    sendAngles(angles);
    lastSend = now;
  }
}
