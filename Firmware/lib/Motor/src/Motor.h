#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>
#include <stddef.h>

#include <PID.h>
#include <Logger.h>
#include <MotorDriver.h>
#include <MotorEncoder.h>
#include <NeonErrorDef.h>

class Motor
{
    public:
        Motor(Logger& logger, MotorDriver& driver) : _logger(logger), _driver(driver), _pid(0,0,0){};
        
        PID _pid;

        virtual errorCode_t init() = 0;

        virtual errorCode_t init(MotorEncoder *encoder) = 0;

        errorCode_t setSpeed(float speed)
        {
            _targetSpeed = speed;
            return ERR_SUCCESS;
        }

        errorCode_t setSpeed(float speed, float acceleration)
        {
            setSpeed(speed);
            setAcceleration(acceleration);
            return ERR_SUCCESS;
        }

        errorCode_t setAcceleration(float acceleration) //rps^2 
        {
            _acceleration = acceleration;
            return ERR_SUCCESS;
        };

        errorCode_t setEncoder(MotorEncoder *encoder)
        {
            if(encoder == NULL) return ERR_NULL_POINTER;
            _encoder = encoder;
            return ERR_SUCCESS;
        }

        float getSpeed(){
            return _targetSpeed;
        }

        void setMaxSpeedRps(uint32_t maxSpeed)
        {
            _maxSpeedRps = maxSpeed;
        }
        
        uint32_t getMaxSpeedRps()
        {
            return _maxSpeedRps;
        }

        MotorEncoder* _encoder; // This is a pointer because this guy is optional
        MotorDriver& _driver; 

        void stop()
        {
            _targetSpeed = 0;
            _currentTargetSpeed = 0;
            _driver.coast();
        }

        float getCurrentSpeed()
        {
            return _currentSpeed;
        }

    protected:
        Logger& _logger;
        void (*_proccessCallback)();
        float _targetSpeed;
        float _currentTargetSpeed;
        float _currentSpeed;
        float _acceleration;
        float _lastEncoderRead;
        uint32_t _maxSpeedRps;


};

#endif // _MOTOR_H_