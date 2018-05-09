#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#include <Arduino.h>

class Motor
{
  public:
    bool _isEnabled = false;

    void initialze(uint8_t enablePin, uint8_t pwmPin)
    {
        _enablePin = enablePin;
        _pwmPin = pwmPin;

        pinMode(_enablePin, OUTPUT);
        digitalWrite(_enablePin, LOW);
        pinMode(_pwmPin, OUTPUT);
        analogWrite(_pwmPin, _zeroPower);
    };

    void enableMotor(bool toggle)
    {
        digitalWrite(_enablePin, toggle);
        _isEnabled = toggle;
    };

    void setSpeed(int value)
    {
        value = map(value * 100, 0, 100, 135, 0);
        analogWrite(_pwmPin, value);
    };

  private:
    static const int _zeroPower = 127;
    int _enablePin, _pwmPin;
};

#endif