#include <Arduino.h>
#include "Adafruit_Keypad.h"
#include "Calculator.h"

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char *sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif // __arm__

int freeMemory()
{
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char *>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif // __arm__
}

//Adafruit_LiquidCrystal *lcd = nullptr;

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

Adafruit_Keypad *customKeypad = nullptr;
Calculator *calc = nullptr;
keypadEvent evt;

void setup()
{
  customKeypad = new Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
  calc = new Calculator();
  calc->print();
  Serial.begin(9600);
  customKeypad->begin();
}

void loop()
{
  static int i = 0;
  customKeypad->tick();

  while (customKeypad->available())
  {
    evt = customKeypad->read();
    if (evt.bit.EVENT == KEY_JUST_PRESSED)
    {
      Serial.print(i++);
      Serial.print(' ');
      Serial.println(freeMemory());
      calc->addChar((char)evt.bit.KEY);
      calc->print();
    }
  }
  delay(10);
}
