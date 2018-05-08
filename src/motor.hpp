#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>

class Motor {
    public:
        bool _isEnabled = false;

        Motor(uint8_t enablePin, uint8_t pwmPin){
            _enablePin = enablePin;
            _pwmPin = pwmPin;

            pinMode(_enablePin, OUTPUT);
            digitalWrite(_enablePin, LOW);
            pinMode(_pwmPin, OUTPUT);
            analogWrite(_pwmPin, _zeroPower);
        };

        void enableMotor(bool toggle){
            digitalWrite(_enablePin, toggle);
            _isEnabled = toggle;
        };

        void setSpeed(int value){
            if (_isEnabled){
                value = max(min(127-value, 0), 127);
                analogWrite(_pwmPin, value);
            }
        };

    private:
        static const int _zeroPower = 127;
        int _enablePin, _pwmPin;
};



#endif