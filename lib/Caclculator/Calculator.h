
#ifndef CACLCULATOR_H
#define CACLCULATOR_H

#include "Arduino.h"
#include "Adafruit_LiquidCrystal.h"

class Calculator
{
public:
    Calculator();
    ~Calculator() = default;

    bool addChar(const char a_key);
    void print();

private:
    bool add();
    bool sub();
    bool multiply();
    bool divide();
    bool memorize();
    bool clear();
    bool compute();
    void resetCurrent();
    //static const unsigned char BUFF_LEN = 14;
    Adafruit_LiquidCrystal *m_lcd = nullptr;
    float m_memory = 0.;
    float m_total = 0.;
    long int m_intValue = 0;
    char m_divisorPow = 0;
    bool m_isDec = false;
    bool m_isNeg = false;
    //char m_buffer[BUFF_LEN];
    //String m_buffer = "";
    //unsigned char m_bufferLenght = 0;
    char m_op = ' ';
    bool m_error = 0;
};

#endif