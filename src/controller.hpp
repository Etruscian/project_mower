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
        filterThrottle = 0.995*filterThrottle + 0.005*throttle;     // filtered throttle as speed estimate, 100Hz, in 2s op topSpeed
        _steeringGain = 1 - 0.8*filterThrottle**2;        // 0.8 value is arbitrary, _steeringGain [0,1]
        uSteer = direction * _steeringGain;         // direction [-1,1]
        x1 = 0.2;                                   // input = 0.2
        y1 = 0.35;                                  // output = 0.35
        if( throttle <= x1)                         // fuzzy throttle control
            uForward = y1/x1 *throttle;             // uForward [0, 1]
        else
            uForward = y1 + (1-y1)/(1-x1)*(throttle-x1);
        if( _leftMotor._isEnabled)
            _leftMotor.setSpeed(uForward + uSteer);      // setSpeed [0, 1] 
        if( _rightMotor._isEnabled)
            _rightMotor.setSpeed(uForward - uSteer);
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
    float x1, y1, uForward, uSteer, filterThrottle;
};

#endif