#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#include <Arduino.h>

class Motor
{
  public:
    bool _isEnabled = false;
    uint8_t _motorNumber;

    void initialze(uint8_t enablePin, uint8_t pwmPin)
    {
        _enablePin = enablePin;
        _pwmPin = pwmPin;

        pinMode(_enablePin, OUTPUT);
        digitalWrite(_enablePin, LOW);
        pinMode(_pwmPin, OUTPUT);
        if (_motorNumber)
            OCR4A = _zeroPower;
        else
            OCR4B = _zeroPower;
    };

    void enableMotor(bool toggle)
    {
        digitalWrite(_enablePin, toggle);
        _isEnabled = toggle;
    };

    void setSpeed(float value)
    {
        value = 600.0-(value/100.0*600.0);
        if (_motorNumber)
            OCR4A = (int)value;
        else
            OCR4B = (int)value;
    };

  private:
    static const int _zeroPower = 600;
    int _enablePin, _pwmPin;
};

#endif