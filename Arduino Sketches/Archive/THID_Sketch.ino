//Written by Austin Allred, 2016

#include <Keyboard.h>

int Start = 2;  // Set a name to pin
int Hold = 3;  // Set a name to pin
int Stop = 6;  // Set a name to pin
int Cool = 9;  // Set a name to pin


void setup()
{
  pinMode(Start, INPUT_PULLUP);  // Set the button as an input with pullup resistor on
  pinMode(Hold, INPUT_PULLUP);  // Set the button as an input with pullup resistor on
  pinMode(Stop, INPUT_PULLUP);  // Set the button as an input with pullup resistor on
  pinMode(Cool, INPUT_PULLUP);  // Set the button as an input with pullup resistor on
  digitalWrite(Start, HIGH);  // Pull the button high
  digitalWrite(Hold, HIGH);  // Pull the button high
  digitalWrite(Stop, HIGH);  // Pull the button high
  digitalWrite(Cool, HIGH);  // Pull the button high


}

void loop()
{
  if (digitalRead(Start) == 0)  // if the button goes low
  {
    Keyboard.press(130);//left alt
    Keyboard.write('r');  // send a 'r' to the computer via Keyboard HID
    delay(500);  // delay
    Keyboard.release(130);
  }

  if (digitalRead(Hold) == 0)  // if the button goes low
  {
    Keyboard.write(32);  // send a Space to the computer via Keyboard HID
    delay(500);  // delay
  }

  if (digitalRead(Stop) == 0)  // if the button goes low
  {
    Keyboard.press(177);  // send a ESC to the computer via Keyboard HID
    delay(500);  // delay
    Keyboard.release(177);
  }

  if (digitalRead(Cool) == 0)  // if the button goes low
  {
    Keyboard.press(130);//left alt
    Keyboard.write('f');  // send a 'f' to the computer via Keyboard HID
    delay(500);  // delay
    Keyboard.release(130);
  }
}
