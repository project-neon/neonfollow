#ifndef _ARDUINO_MOTOR_H
#define _ARDUINO_MOTOR_H

#include <Motor.h>
#include <Thread.h>

class ArduinoMotor : public Motor, public Thread
{
    public:
        ArduinoMotor(Logger& logger, MotorDriver& driver);
        void run(); 

        errorCode_t init();

        errorCode_t init(MotorEncoder *encoder);
};

#endif //_ARDUINO_MOTOR_H