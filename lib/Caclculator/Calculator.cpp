#include "Calculator.h"

Calculator::Calculator(){};

bool Calculator::addChar(char key)
{
    switch (key)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        if (m_intValue < 99999999)
        {
            m_intValue = m_intValue * 10 + key - '0';
            if (m_isDec)
            {
                m_divisorPow += 1;
            }
        }
        break;
    case '.':
        m_isDec = true;
        break;
    case '-':
        if (m_intValue == 0)
        {
            m_isNeg = !m_isNeg;
            break;
        }
    case '+':
    case '*':
    case '/':
        compute();
        m_op = key;
    case 'M':
        memorize();
        break;
    case 'C':
        clear();
        break;
    case '=':
        compute();
        resetCurrent();
        m_op = ' ';
        break;
    default:
        m_error = true;
    }
    return m_error;
}

void Calculator::print()
{
    m_lcd = new Adafruit_LiquidCrystal(7, 8, 9, 5, 6, 4);
    String toPrint;
    m_lcd->begin(16, 2);
    m_lcd->clear();
    m_lcd->setCursor(0, 0);
    //m_lcd->print("M");
    //m_lcd->print(String(m_memory));
    m_lcd->print("->");
    toPrint = String(m_total);
    m_lcd->setCursor(15 - toPrint.length(), 0);
    m_lcd->print(toPrint);

    m_lcd->setCursor(0, 1);
    m_lcd->print(m_op);
    if (m_isDec)
    {
        toPrint = String(m_intValue / pow(10, m_divisorPow), m_divisorPow);
    }
    else
    {
        toPrint = String(m_intValue);
    }
    if (m_isNeg)
    {
        m_lcd->setCursor(14 - toPrint.length(), 1);
        m_lcd->print('-');
    }
    m_lcd->setCursor(15 - toPrint.length(), 1);
    m_lcd->print(toPrint);
    delete m_lcd;
}

void Calculator::resetCurrent()
{
    m_divisorPow = 0;
    m_isDec = false;
    m_intValue = 0;
    m_isNeg = false;
}

bool Calculator::memorize()
{
    m_memory = m_intValue / pow(10, m_divisorPow);
    if (m_isNeg)
    {
        m_memory *= -1;
    }
    resetCurrent();
    return true;
}

bool Calculator::clear()
{
    if (m_intValue == 0)
    {
        m_memory = 0;
        m_total = 0;
        m_op = ' ';
    }
    resetCurrent();
    return true;
};
bool Calculator::compute()
{
    float current = m_intValue / pow(10, m_divisorPow);
    if (m_isNeg)
    {
        current *= -1;
    }
    switch (m_op)
    {
    case ' ':
        if (current != 0)
        {
            m_total = current;
        }
        break;
    case '+':
        m_total += current;
        break;
    case '-':
        m_total -= current;
        break;
    case '*':
        m_total *= current;
        break;
    case '/':
        m_total /= current;
        break;
    default:
        break;
    }
    return true;
};