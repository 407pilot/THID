//Written by Greg Carl, 2017
//https://www.dropbox.com/scl/fi/ed728qbyxwf266y9vswqs/Tormach-Arduino-Teensy-LC.txt?rlkey=8b7ntbvyowf5cmmgtpncsv4vr&st=xjd0irym&dl=0

#include <Bounce.h>
Bounce CYCLE_START = Bounce(2, 10);
Bounce COOLANT = Bounce(3, 10);
Bounce FEEDHOLD = Bounce(4, 10);
Bounce CYCLE_STOP = Bounce(5, 10);

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void loop() {
  CYCLE_START.update();
  COOLANT.update();
  FEEDHOLD.update();
  CYCLE_STOP.update();
  if (CYCLE_START.fallingEdge()) {
    Keyboard.set_modifier(MODIFIERKEY_ALT);
    Keyboard.send_now();
    delay(10);
    Keyboard.set_key1(KEY_R);
    Keyboard.send_now();
    delay(10);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    delay(10);
    Keyboard.set_modifier(0);
    Keyboard.send_now();
  }
  if (COOLANT.fallingEdge()) {
    Keyboard.set_modifier(MODIFIERKEY_ALT);
    Keyboard.send_now();
    delay(10);
    Keyboard.set_key1(KEY_F);
    Keyboard.send_now();
    delay(10);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    delay(10);
    Keyboard.set_modifier(0);
    Keyboard.send_now();
  }
  if (FEEDHOLD.fallingEdge()) {
    Keyboard.set_key1(KEY_SPACE);
    Keyboard.send_now();
    delay(10);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
  if (CYCLE_STOP.fallingEdge()) {
    Keyboard.set_key1(KEY_ESC);
    Keyboard.send_now();
    delay(10);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
}
