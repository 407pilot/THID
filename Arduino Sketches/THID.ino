// ============================================================
// Doug Craig, 2026
// https://github.com/407pilot/THID
//
// Compatible with any Arduino board that supports native USB HID:
// Leonardo, Micro, Pro Micro, Zero, MKR series, RP2040, etc.
//
// Required library: Bounce2 (available in Arduino Library Manager)
//
// Raw HID keycodes are used instead of named constants to ensure
// compatibility across all board packages and cores.
//
// HID Keycode Reference (used in this sketch):
//   0x82 = Left Alt
//   0x81 = Left Ctrl
//   0xB3 = ESC
//   0x20 = Space
//   'r'  = R key (ASCII literals are always safe)
//   'f'  = F key (ASCII literals are always safe)
// ============================================================

#include <Keyboard.h>
#include <Bounce2.h>

// --- Pin Definitions ---
const int PIN_CYCLE_START = 2;
const int PIN_FEEDHOLD    = 3;
const int PIN_CYCLE_STOP  = 6;
const int PIN_COOLANT     = 9;

const int NUM_BUTTONS = 4;
const int buttonPins[NUM_BUTTONS] = {
  PIN_CYCLE_START, PIN_FEEDHOLD, PIN_CYCLE_STOP, PIN_COOLANT
};

// --- Button Index Names ---
enum ButtonIndex {
  BTN_CYCLE_START = 0,
  BTN_FEEDHOLD,
  BTN_CYCLE_STOP,
  BTN_COOLANT
};

Bounce buttons[NUM_BUTTONS];

// --- Helper: send an optional modifier + key, then release ---
void sendKey(uint8_t modifier, uint8_t key) {
  if (modifier) Keyboard.press(modifier);
  Keyboard.press(key);
  delay(10);
  Keyboard.releaseAll();
}

void setup() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    buttons[i].attach(buttonPins[i]);
    buttons[i].interval(10);  // 10ms debounce
  }
  Keyboard.begin();
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].update();
  }

  if (buttons[BTN_CYCLE_START].fell()) sendKey(0x82, 'r');   // Alt+R
  if (buttons[BTN_FEEDHOLD].fell())    sendKey(0,    0x20);  // Space
  if (buttons[BTN_CYCLE_STOP].fell())  sendKey(0,    0xB3);  // Esc
  if (buttons[BTN_COOLANT].fell())     sendKey(0x82, 'f');   // Alt+F
}