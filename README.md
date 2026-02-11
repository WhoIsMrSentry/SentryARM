# ConHand - ESP32 Master/Slave and Web Receiver

This project reads potentiometer values from a control arm called "ConHand" and transmits finger angles from one ESP32 (master) to another ESP32 (slave) via Bluetooth. Each feature is modularized into separate `.h` files. If hardware is not available, a browser-based receiver uses the camera (MediaPipe Hands) to control a virtual hand.

Repository structure:

- `src/xmaster/` - ESP32 master: reads potentiometers and sends angles over Bluetooth.
- `src/xslave/` - ESP32 slave: receives angles and drives servos.
- `web/` - Browser receiver using MediaPipe Hands.

Quick setup

1. Required libraries (Arduino IDE / PlatformIO):
   - ESP32 core
   - `ESP32Servo` (or compatible Servo library for ESP32)
   - `BluetoothSerial` (included with the ESP32 core)

2. Hardware wiring
   - Master: connect 5 potentiometers to the ADC pins defined in `src/xmaster/config.h` (`POT_PINS`).
   - Slave: connect 5 servos to the pins defined in `src/xslave/config.h` (`SERVO_PINS`).

3. Flashing
   - Upload `xmaster.ino` to the master ESP32 and `xslave.ino` to the slave ESP32.

Web receiver

Open `web/index.html` in a browser and allow camera access. The MediaPipe Hands model will visualize the hand landmarks. This UI can be used as a software-only receiver when the physical ConHand is not available.

WebSocket -> ESP32

- The web client connects by default to `ws://192.168.4.1:81` (typical IP when the ESP32 runs as an AP).
- `src/xslave/wifi_ws.h` starts the ESP32 in access point mode with SSID `ConHand_AP` and password `conhand123`, and runs a WebSocket server on port 81.
- The browser computes five approximate finger angles from MediaPipe landmarks and sends them as CSV: `a0,a1,a2,a3,a4`.

Notes

- The Bluetooth protocol uses a simple CSV line per frame: `a0,a1,a2,a3,a4\n`.
- Consider adding checksum/ACK if packet integrity is required.
