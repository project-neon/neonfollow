#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <stdint.h>
#include <Logger.h>
#include <NeonErrorDef.h>

class MotorDriver{
    public:
        typedef enum{
            DIRECTION_CLOCKWISE,
            DIRECTION_COUNTERCLOCKWISE,
            DIRECTION__EOF,
        }Direction_t;

        typedef struct
        {
            int16_t powerPin;
            int16_t directionPinA;
            int16_t directionPinB;

            uint16_t angle;
            Direction_t direction;
            uint16_t power;
        }MotorDriverConfig_t;

        MotorDriver(Logger& logger, MotorDriverConfig_t config) : _logger(logger){};

        virtual void init() = 0;

        virtual errorCode_t setFrequency(uint32_t frequencyHz) = 0;

        virtual errorCode_t setPower(uint16_t power) = 0;

        virtual errorCode_t setPower(uint16_t power, Direction_t direction) = 0;

        virtual errorCode_t setDirection(Direction_t direction) = 0;

        virtual errorCode_t setAngle(uint16_t angle);
        
        virtual errorCode_t step();

        virtual errorCode_t brake() = 0;

        virtual errorCode_t coast() = 0;

        Direction_t getDirection(){
            return _config.direction;
        }

        uint16_t getPower()
        {
            return _config.power;
        }

        MotorDriverConfig_t getCurrentConfig()
        {
            return _config;
        }

    protected:
        MotorDriverConfig_t _config;
        Logger& _logger;
};

#endif // _MOTOR_DRIVER_H_