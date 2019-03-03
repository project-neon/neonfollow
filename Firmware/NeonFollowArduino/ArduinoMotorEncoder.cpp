#include "ArduinoMotorEncoder.h"

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

errorCode_t ArduinoMotorEncoder::setup(uint16_t* pins, uint8_t pinCount)
{
    errorCode_t error;
    _logger.info("Encoder setup.");
    if(pins == NULL)
    {
        _logger.critical("Null pointer for 'pins' parameter on setup");
        return ERR_NULL_POINTER;
    }

    if(pinCount != 2)
    {
        _logger.error("Wrong number of pins for this module");
        return ERR_INVALID_PARAM;
    }

    _chApin = pins[0];
    _chBpin = pins[1];

    pinMode(_chApin, INPUT);
    pinMode(_chBpin, INPUT);
    configureInterruptMode(); //Deixei configurado a borda de descida como padrão. Podemos ajustar depois.

    return ERR_SUCCESS;
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
    _logger.info("_pulseCallback");
    _pulse();
}

void ArduinoMotorEncoder::configureInterruptMode()
{
    switch (_encoding)
    {
        // Olha, esse negocio de std::bind é uma treta que acontece pelo seguinte:
        // A gente precisa passar um callback pra função attachInterrupt. Só que, a gente tá dentro de uma classe,
        // então na realidade a função _pulseCallback só vai existir quando a gente instanciar um objeto.
        // Por isso, se a gente passar simplesmente o _pulseCallback ele vai dar erro, pq na realidade nesse momento
        // ele ainda não sabe qual é o ponteiro dessa função. Quando a gente usa o std::bind, a gente ta basicamente falando
        // "Olha, esse negócio aqui vai ser a função _pulseCallback desse objeto que to criando agora"
    case ENCODE_TYPE_X1:
//        attachInterrupt(digitalPinToInterrupt(_chApin), std::bind(&ArduinoMotorEncoder::_pulseCallback, this) , FALLING);
        detachInterrupt(_chBpin);
        break;

    case ENCODE_TYPE_X2:
//        attachInterrupt(digitalPinToInterrupt(_chApin), std::bind(&/ArduinoMotorEncoder::_pulseCallback, this), CHANGE);
        detachInterrupt(_chBpin);
        break;

    case ENCODE_TYPE_X4:
//        attachInterrupt(digitalPinToInterrupt(_chApin), std::bin/d(&ArduinoMotorEncoder::_pulseCallback, this), CHANGE);
//        attachInterrupt(digitalPinToInterrupt(_chBpin), std::/bind(&ArduinoMotorEncoder::_pulseCallback, this), CHANGE);
        break;

    default:
        _logger.critical("Missing a correct interrupt configuration.");
        break;
    }
}
