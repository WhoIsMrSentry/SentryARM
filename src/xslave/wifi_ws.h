#ifndef WIFI_WS_H
#define WIFI_WS_H

#include <WiFi.h>
#include <WebSocketsServer.h>
#include "config.h"

const char* AP_SSID = "ConHand_AP";
const char* AP_PASS = "conhand123";

static WebSocketsServer webSocket = WebSocketsServer(81);
static volatile bool wsNewData = false;
static int wsAngles[NUM_FINGERS];

void handleWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String msg = String((char*)payload);
    msg.trim();
    int idx = 0;
    int start = 0;
    for (int i = 0; i <= msg.length() && idx < NUM_FINGERS; ++i) {
      if (i == msg.length() || msg.charAt(i) == ',') {
        String token = msg.substring(start, i);
        wsAngles[idx++] = token.toInt();
        start = i + 1;
      }
    }
    if (idx == NUM_FINGERS) wsNewData = true;
  }
}

inline void initWiFiWebSocket() {
  WiFi.softAP(AP_SSID, AP_PASS);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP: ");
  Serial.println(IP);
  webSocket.begin();
  webSocket.onEvent(handleWebSocketEvent);
  Serial.println("WebSocket server started on port 81");
}

inline void wsLoop() {
  webSocket.loop();
}

inline bool wsHasData() {
  return wsNewData;
}

inline void getWsAngles(int *out) {
  for (int i = 0; i < NUM_FINGERS; ++i) out[i] = wsAngles[i];
  wsNewData = false;
}

#endif
