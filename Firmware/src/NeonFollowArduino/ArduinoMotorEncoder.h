#ifndef _ARDUINO_MOTOR_ENCODER_H_
#define _ARDUINO_MOTOR_ENCODER_H_

#include <Arduino.h>
#include <MotorEncoder.h>

#ifndef voidArgumentFuncPtr
typedef void (*voidFuncPtr)(void);
typedef void (*voidArgumentFuncPtr)(void *);

#endif


class ArduinoMotorEncoder : public MotorEncoder
{
    public:
        // Construtores. Estou fazendo aqui pra TODOS os gostos. Podemos ou não deixar tudo configurado
        // logo no contrutor.
        ArduinoMotorEncoder(Logger& logger, Encoding_t encoding, uint16_t pulsesPerRevolution);
        ArduinoMotorEncoder(Logger& logger, Encoding_t encoding);
        ArduinoMotorEncoder(Logger& logger, uint16_t pulsesPerRevolution);
        ArduinoMotorEncoder(Logger& logger);

        // Funções que estão definidas como virtual na interface MotorEncoder
        errorCode_t setup(uint16_t* pins, uint8_t pinCount);

        // Funções de operação
        float getRevolutions();

        uint32_t getRevolutionsCount();

        // Fazendo o código percebi que há a necessidade de configurar as interrupções.
        // To fazendo isso de acordo com o Arduino, então coloquei uma função adicional nessa classe.
        void configureInterruptMode();

        private:
            uint16_t _chApin; // sabemos que o encoder pro arduino vai ficar num pino de interrupção.
            uint16_t _chBpin; // sabemos que o encoder pro arduino vai ficar num pino de interrupção.
            
            void _pulseCallback(); // função que chamamos quando sabemos que teve um pulso. 
                                   // A forma como isso opera depende da plataforma, por isso fica aqui no arquivo pro arduino
                                 
};

#endif //_ARDUINO_MOTOR_ENCODER_H_