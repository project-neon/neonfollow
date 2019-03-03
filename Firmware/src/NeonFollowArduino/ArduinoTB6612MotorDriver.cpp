#include <ArduinoTB6612MotorDriver.h>
#include <HardwareTimer.h>

#ifdef _BOARD_MAPLE_MINI_H_ 

#define pwmWrite analogWrite

HardwareTimer timer(1);

#endif

TB6612MotorDriver::TB6612MotorDriver(Logger& logger, MotorDriverConfig_t config) :
MotorDriver::MotorDriver(logger, config)
{
    _config = config;
}

void TB6612MotorDriver::init()
{
    _logger.info("TB6612MotorDriver::init");
#ifdef _BOARD_MAPLE_MINI_H_ 
    _logger.info("Setting timer");
    timer.setPrescaleFactor(1);
    timer.setOverflow(760);
#endif
    _logger.info("Setting pins");
    pinMode(_config.powerPin, PWM);
    pinMode(_config.directionPinA, OUTPUT);
    pinMode(_config.directionPinB, OUTPUT);
    coast();
}

errorCode_t TB6612MotorDriver::setFrequency(uint32_t frequencyHz)
{
    _logger.error("Setting frequency");
    return ERR_NOT_SUPPORTED;
}

errorCode_t TB6612MotorDriver::setPower(uint16_t power)
{
    _logger.info("Setting power");
    if(power > 4095)
    {
        _logger.error("Invalid param");
        return ERR_INVALID_PARAM;
    }
    _config.power = power;
    pwmWrite(_config.powerPin, _config.power);
    return ERR_SUCCESS;
}

errorCode_t TB6612MotorDriver::setPower(uint16_t power, Direction_t direction)
{
    errorCode_t err;

    err = setDirection(direction);
    if(err != ERR_SUCCESS) return err;

    err = setPower(power);
    return err;
}

errorCode_t TB6612MotorDriver::setDirection(Direction_t direction)
{
    if(direction >= DIRECTION__EOF)
    {
        return ERR_INVALID_PARAM;
    }

    _logger.info(String("setting direction pins to " + String(direction == DIRECTION_CLOCKWISE ? "CW" : "CCW")).c_str());
    _config.direction = direction;
    digitalWrite(_config.directionPinA, direction == DIRECTION_CLOCKWISE);
    digitalWrite(_config.directionPinB, direction == DIRECTION_COUNTERCLOCKWISE);
    return ERR_SUCCESS;
}

errorCode_t TB6612MotorDriver::setAngle(uint16_t angle)
{
    _logger.info("setting angle");
    return ERR_NOT_SUPPORTED;
}

errorCode_t TB6612MotorDriver::step()
{
    _logger.info("step");
    return ERR_NOT_SUPPORTED;
}

errorCode_t TB6612MotorDriver::brake()
{
    _logger.info("brake");
    setPower(0);
    digitalWrite(_config.directionPinA, HIGH);
    digitalWrite(_config.directionPinB, HIGH);
    return ERR_SUCCESS;
}

errorCode_t TB6612MotorDriver::coast()
{
    _logger.info("coast");
    setPower(0);
    digitalWrite(_config.directionPinA, LOW);
    digitalWrite(_config.directionPinB, LOW);
    return ERR_SUCCESS;
}
