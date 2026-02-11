#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Servo.h>
#include "config.h"

static Servo servos[NUM_FINGERS];

inline void attachServos() {
  for (int i = 0; i < NUM_FINGERS; ++i) {
    servos[i].attach(SERVO_PINS[i]);
    servos[i].write(90);
  }
}

inline void applyAngles(int *angles) {
  for (int i = 0; i < NUM_FINGERS; ++i) {
    int a = constrain(angles[i], 0, 180);
    servos[i].write(a);
  }
}

#endif
