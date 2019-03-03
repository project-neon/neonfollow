#ifndef _ARDUINO_TB6612_MOTOR_DRIVER_H_
#define _ARDUINO_TB6612_MOTOR_DRIVER_H_

#include <MotorDriver.h>
#include <Arduino.h>

class TB6612MotorDriver : public MotorDriver 
{
    public:
        TB6612MotorDriver(Logger& logger, MotorDriverConfig_t config);

        void init();

        errorCode_t setFrequency(uint32_t frequencyHz);

        errorCode_t setPower(uint16_t power);

        errorCode_t setPower(uint16_t power, Direction_t direction);

        errorCode_t setDirection(Direction_t direction);

        errorCode_t setAngle(uint16_t angle);
        
        errorCode_t step();

        errorCode_t brake();

        errorCode_t coast();

    private:
};


#endif //_ARDUINO_TB6612_MOTOR_DRIVER_H_