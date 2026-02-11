#include <Arduino.h>
#include "config.h"
#include "bt_recv.h"
#include "servo_control.h"
#include "wifi_ws.h"

int angles[NUM_FINGERS];

void setup() {
  Serial.begin(115200);
  delay(100);
  initBTReceiver();
  attachServos();
  initWiFiWebSocket();
}

void loop() {
  wsLoop();
  if (wsHasData()) {
    getWsAngles(angles);
    applyAngles(angles);
  }
  // Keep backward compatibility with Bluetooth receiver if present
  if (readIncomingAngles(angles)) {
    applyAngles(angles);
  }
}
