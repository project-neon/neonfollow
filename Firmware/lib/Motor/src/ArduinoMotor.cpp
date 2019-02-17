#include <ArduinoMotor.h>


ArduinoMotor::ArduinoMotor(Logger& logger, MotorDriver& driver) : 
Motor(logger, driver)
{
   _lastEncoderRead = 0;
}

void ArduinoMotor::run()
{  
    if(_encoder != NULL)
    {
        uint32_t time = millis();
        float deltaTime = ((time - last_run) * 1.0)/1000.0;

        // limit acceleration
        if(abs(_currentTargetSpeed - _targetSpeed) <= (0.05 * _acceleration * deltaTime))
        {
            _currentTargetSpeed = _targetSpeed;
        }
        else if(_currentTargetSpeed < _targetSpeed)
        {
            _currentTargetSpeed += _acceleration * deltaTime;
        }
        else
        {
            _currentTargetSpeed -= _acceleration * deltaTime;
        }
        _pid.setSetPoint(_currentTargetSpeed);

        float deltaRev;
        deltaRev = _encoder->getRevolutions() - _lastEncoderRead; 
        _lastEncoderRead = _encoder->getRevolutions();

        _currentSpeed = deltaRev/deltaTime; // RPS
        _pid.setProcessValue(_currentSpeed);

        float output = _pid.compute(time);
        output = map(output, 0, _maxSpeedRps, 0, 4095);
        _driver.setPower(_driver.getPower() + output);
    }
    else
    {
        /* socorro */
    }
    
    runned();
}

errorCode_t ArduinoMotor::init()
{
    return init(NULL);
}

errorCode_t ArduinoMotor::init(MotorEncoder *encoder)
{
    if(_encoder !=NULL) 
    {
        _encoder->reset();
    }

}

