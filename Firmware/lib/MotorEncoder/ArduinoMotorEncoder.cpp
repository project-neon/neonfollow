#include <ArduinoMotorEncoder.h>

// Uma referência (tipo o Logger&) nunca pode ser nula. Portanto, a gente tem que inicializar o Logger antes da classe
// a gente faz isso colocando o : no final do contrutor e definindo o logger.
ArduinoMotorEncoder::ArduinoMotorEncoder(Logger& logger, Encoding_t encoding, uint16_t pulsesPerRevolution) : 
MotorEncoder::MotorEncoder(logger)
{
    setEncoding(encoding);
    setPulsesPerRev(pulsesPerRevolution);
}

ArduinoMotorEncoder::ArduinoMotorEncoder(Logger& logger, Encoding_t encoding) : 
MotorEncoder::MotorEncoder(logger)
{
    ArduinoMotorEncoder(logger, encoding, 0);
}

ArduinoMotorEncoder::ArduinoMotorEncoder(Logger& logger, uint16_t pulsesPerRevolution) : 
MotorEncoder::MotorEncoder(logger)
{
    ArduinoMotorEncoder(logger, ENCODE_TYPE_X2, pulsesPerRevolution);
}

ArduinoMotorEncoder::ArduinoMotorEncoder(Logger& logger) : 
MotorEncoder::MotorEncoder(logger)
{
    ArduinoMotorEncoder(logger, ENCODE_TYPE_X2, 0);
}

errorCode_t ArduinoMotorEncoder::setup(uint16_t* pins)
{
    errorCode_t error;
    _logger.info("Encoder setup.");
    if(pins == NULL)
    {
        _logger.critical("Null pointer for 'pins' parameter on setup");
        return ERR_NULL_POINTER;
    }

    _pin = *pins;

    pinMode(_pin, INPUT);
    error = setInterruptMode(FALLING); //Deixei configurado a borda de descida como padrão. Podemos ajustar depois.

    return error;
}

float ArduinoMotorEncoder::getRevolutions()
{
    return (_pulseCount * 1.0)/(_pulsesPerRev * 1.0);
}

uint32_t ArduinoMotorEncoder::getRevolutionsCount()
{
    return _pulseCount/_pulsesPerRev;
}

void ArduinoMotorEncoder::_pulseCallback()
{
    _pulse();
}

errorCode_t ArduinoMotorEncoder::setInterruptMode(uint32_t mode)
{
    static uint32_t _intMode = FALLING;
    if(mode == LOW)     _intMode = LOW;
    if(mode == FALLING) _intMode = FALLING;
    if(mode == CHANGE)  _intMode = CHANGE;
    if(mode == RISING)  _intMode = RISING;
    
    else 
    {
        _logger.error("Unsuported value for interrupt mode. Setting the default value: FALLING");
        attachInterrupt(digitalPinToInterrupt(_pin), std::bind(&ArduinoMotorEncoder::_pulseCallback, this), _intMode);
        return ERR_NOT_SUPPORTED;
    }

    // Olha, esse negocio de std::bind é uma treta que acontece pelo seguinte:
    // A gente precisa passar um callback pra função attachInterrupt. Só que, a gente tá dentro de uma classe,
    // então na realidade a função _pulseCallback só vai existir quando a gente instanciar um objeto.
    // Por isso, se a gente passar simplesmente o _pulseCallback ele vai dar erro, pq na realidade nesse momento
    // ele ainda não sabe qual é o ponteiro dessa função. Quando a gente usa o std::bind, a gente ta basicamente falando
    // "Olha, esse negócio aqui vai ser a função _pulseCallback desse objeto que to criando agora"
    attachInterrupt(digitalPinToInterrupt(_pin), std::bind(&ArduinoMotorEncoder::_pulseCallback, this), _intMode);
    return ERR_SUCCESS;
}