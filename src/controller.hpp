#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <Arduino.h>
#include <motor.hpp>

class Controller
{
  public:
    Controller()
    {
        _leftMotor.initialze(34, 2);
        _rightMotor.initialze(35, 3);
    };

    void update(float throttle, float direction)
    {
        _steeringGain = 1 - 0.8*throttle**2;
        if( _leftMotor._isEnabled)
            _leftMotor.setSpeed(throttle + direction * _steeringGain);
        if( _rightMotor._isEnabled)
            _rightMotor.setSpeed(throttle - direction * _steeringGain);
    };

    void enableMotors(bool toggle)
    {
        _leftMotor.enableMotor(toggle);
        _rightMotor.enableMotor(toggle);
    }

  private:
    Motor _leftMotor;
    Motor _rightMotor;
    float _steeringGain ; //= 0.3;
};

#endif