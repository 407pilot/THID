# THID — Tormach Human Interface Device

The THID was created by Austin Allred of [EntirelyCrimson.com](http://entirelycrimson.com) and originally released in 2017 as an open source project. The original files have since been removed from that site; this repository preserves and continues the project. The Arduino sketch has been updated from Austin's original release — the original sketch has been preserved unchanged in the `archive` folder for reference.

## ⚠️ Warning

**This device does not replace a hardware emergency stop.** A software pendant cannot guarantee a response in the event of a program fault, electrical failure, or communication loss. Every CNC machine must have a dedicated hardwired E-stop that cuts power to the drives independently of any software or USB device. Do not use this pendant as a substitute for one.

By building and using this device you accept all risk. No warranty is expressed or implied. The authors are not responsible for damage to equipment, workpieces, or injury resulting from its use.

## What It Is

The THID is a compact physical control pendant for Tormach's PathPilot CNC controller, but could work with any controller that will accept a USB HID keyboard. It consists of an aluminum housing populated with an Arduino Micro clone and up to four buttons. When a button is pressed, the Arduino emulates a USB keyboard and sends a keystroke combination to the host PC, triggering the corresponding PathPilot action.

The default four-button configuration controls:

| Button | Action | Keystroke |
|---|---|---|
| Cycle Start | Begin program execution | Alt+R |
| Feed Hold | Pause execution | Space |
| Cycle Stop | Abort / emergency stop | Esc |
| Coolant | Toggle coolant on/off | Alt+F |

## Requirements

### Hardware
- Any Arduino-compatible board with native USB HID support — Arduino Leonardo, Micro, Pro Micro, RP2040-based boards, or equivalent clones
- Momentary pushbutton switches (normally open)
- Buttons wired between the assigned pin and GND — the internal pullup resistor is used, no external resistor needed

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- [Bounce2 library](https://github.com/thomasfredericks/Bounce2) — install via Arduino Library Manager (Sketch → Include Library → Manage Libraries → search "Bounce2")

## Wiring

Buttons are wired between the designated pin and GND. Do not wire buttons to 5V — the sketch uses `INPUT_PULLUP`, which holds each pin HIGH internally. Pressing a button pulls the pin LOW, which triggers the action.

Default pin assignments (edit the pin definitions at the top of the sketch to change them):

| Button | Pin |
|---|---|
| Cycle Start | 2 |
| Feed Hold | 3 |
| Cycle Stop | 6 |
| Coolant | 9 |

## Customization

### Remapping buttons to different keystrokes

Each button action is defined in a single line at the bottom of `loop()`. The `sendKey()` helper takes two arguments: a modifier key and a primary key.

```cpp
if (buttons[BTN_CYCLE_START].fell()) sendKey(0x82, 'r');   // Alt+R
if (buttons[BTN_FEEDHOLD].fell())    sendKey(0,    0x20);  // Space
if (buttons[BTN_CYCLE_STOP].fell())  sendKey(0,    0xB3);  // Esc
if (buttons[BTN_COOLANT].fell())     sendKey(0x82, 'f');   // Alt+F
```

To send a keystroke with no modifier, pass `0` as the first argument. ASCII characters (letters, numbers, symbols) can be written as literals: `'r'`, `'f'`, `'1'`, etc.

Common modifier keycodes:

| Modifier | Code |
|---|---|
| Left Alt | `0x82` |
| Left Ctrl | `0x81` |
| Left Shift | `0x80` |
| None | `0` |

Common special key codes:

| Key | Code |
|---|---|
| ESC | `0xB3` |
| Space | `0x20` |
| Enter | `0xB0` |
| Tab | `0xB3` |
| F1–F12 | `0xC2`–`0xCD` |

A full HID keycode reference can be found [here](https://www.usb.org/sites/default/files/hut1_3_0.pdf) (Section 10, Keyboard/Keypad Page).

### Adding or removing buttons

1. Add or remove a pin definition at the top of the sketch.
2. Update the `buttonPins[]` array and `NUM_BUTTONS` constant to match.
3. Add or remove the corresponding entry in the `ButtonIndex` enum.
4. Add or remove the corresponding `if` statement in `loop()`.

### Adjusting debounce timing

The debounce interval is set to 10ms by default, which is appropriate for most switches. If you experience double-triggering with a specific switch, increase the value in `setup()`:

```cpp
buttons[i].interval(10);  // increase if double-triggers are observed
```

## Bill of Materials

| Qty | Item | Notes | Link |
|---|---|---|---|
| 1 | Arduino Micro or compatible clone | Must support native USB HID — see note below | [https://amzn.to/4cnrPwq](https://amzn.to/4cnrPwq) |
| 1 | Aluminum housing | Use provided solid models for fabrication | |
| 4 | 19mm momentary pushbutton, stainless steel | Normally open; LED illuminated versions also fit | [https://amzn.to/4sDTDmv](https://amzn.to/4sDTDmv) |
| 4 | 20mm x 3mm round magnets | 20mm x 2mm magnets will work as well; retain with CA glue or Green Loctite | [https://amzn.to/3O4Rzpr](https://amzn.to/3O4Rzpr) |
| 4 | M3-0.5 x 25mm button head screw | Substitute for screw of your choice by modifying the solid model | [https://amzn.to/4mrWXiS](https://amzn.to/4mrWXiS) |

> **Disclosure:** The links above are Amazon affiliate links. Purchases made through them may provide a small commission at no additional cost to you.

### RP2040 boards

RP2040-based boards (such as the Raspberry Pi Pico and its clones) support USB HID but require the [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico) rather than the standard Arduino AVR core. To install it, add the following URL to **File → Preferences → Additional Boards Manager URLs** in the Arduino IDE, then install **Raspberry Pi Pico/RP2040 by Earle F. Philhower, III** from the Boards Manager:

```
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```

AVR-based boards (Leonardo, Micro, Pro Micro) do not require this step.

## Notes

- The sketch sends keystrokes to whatever application has focus on the host PC. Ensure PathPilot has focus before using the pendant.
- The device presents itself as a standard USB HID keyboard — no drivers are required on the host PC.

