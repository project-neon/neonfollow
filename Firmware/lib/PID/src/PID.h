#ifndef PID_H
#define PID_H

#include <stdint.h>

class PID {
public:

    PID(float kP, float kI, float kD){
        _kP = kP;
        _kI = kI;
        _kD = kD;
        _lastTimer = 0;
    }
    
    void setProcessValue(float sample){
        _sample = sample;
    }
    
    void setSetPoint(float setPoint){
        _setPoint = setPoint;
    }
    
    void setTunings(float kP, float kI, float kD){
        _kP = kP;
        _kI = kI;
        _kD = kD;
    }

    float getKp()
    {
        return _kP;
    }

    float getKi()
    {
        return _kI;
    }

    float getKd()
    {
        return _kD;
    }
    
    float compute(uint32_t currentTime){
        
        _error = _setPoint - _sample;
        _timer = currentTime;
        float deltaTime =  _timer - _lastTimer;
        _lastTimer = _timer;
        _proportional = _error * _kP;
        _integral += (_error * _kI) * deltaTime;
        _derivative = ((_lastSample - _sample) * _kD) / deltaTime;

        _lastSample = _sample;
        
        _pid = _proportional + _integral + _derivative;
        
        return _pid;
     }
     
     protected: 
        float _timer;
        float _lastTimer;
        float _error;
        float _sample;
        float _lastSample;
        float _kP;
        float _kI;
        float _kD;      
        float _proportional;
        float _integral;
        float _derivative;
        float _pid;
        float _setPoint;
};

#endif