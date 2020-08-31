#include <Arduino.h>
#include "Adafruit_LiquidCrystal.h"
#include "Adafruit_Keypad.h"

Adafruit_LiquidCrystal lcd(7, 8, 9, 5, 6, 4);

const byte ROWS = 5;
const byte COLS = 4;

// how the keypad has its keys laid out
const char keys[ROWS][COLS] = {
    {'C', 'M', '/', '*'},
    {'7', '8', '9', '-'},
    {'4', '5', '6', '+'},
    {'1', '2', '3', '='},
    {'#', '0', '.', '#'},
};

const byte rowPins[ROWS] = {2, 10, 16, 14, 15};
const byte colPins[COLS] = {18, 19, 20, 21};

Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);
  customKeypad.begin();
  lcd.begin(16, 2);
  //lcd.print("hello, world!");
}
/*
char incomingByte = 0;

void loop()
{
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = (char)Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
    lcd.setCursor(15, 1);
    lcd.print(incomingByte);
  }
}
*/
void loop()
{
  customKeypad.tick();

  while (customKeypad.available())
  {
    keypadEvent e = customKeypad.read();
    Serial.print((char)e.bit.KEY);
    if (e.bit.EVENT == KEY_JUST_PRESSED)
      Serial.println(" pressed");
    else if (e.bit.EVENT == KEY_JUST_RELEASED)
      Serial.println(" released");
  }

  delay(10);
}
/**/