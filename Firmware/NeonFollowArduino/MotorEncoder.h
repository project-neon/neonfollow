#ifndef _MOTOR_ENCODER_H_
#define _MOTOR_ENCODER_H_

#include <stdint.h>

#include "Logger.h"
#include "NeonErrorDef.h"

class MotorEncoder
{
    public:
        //Definição dos tipos que combinamos no trello. Aqui, podemos extender e criar mais tipos de encoding 
        // tranquilamente. Só lembrar de adicionar o código no .cpp
        typedef enum
        {
            ENCODE_TYPE_X1,
            ENCODE_TYPE_X2,
            ENCODE_TYPE_X4,
            ENCODE_TYPE__EOF // EOF = End Of File, só pra gente saber que esse é o último. 
                             // Faz muito sentido quando vc faz um if pra comparar valores válidos
        }Encoding_t;


        MotorEncoder(Logger& logger) : _logger(logger){};

        // Função virtual significa que ela não tem implementação. Ou seja, 
        // pra gente conseguir compilar essa classe, precisamos extender ela
        // e implementar todas as funções virtuais na classe filha.
        // Outro ponto IMPORTANTE: Não podemos instanciar uma classe abstrata!
        // Isso quer dizer que não vamos conseguir criar um MotorEncoder encoder. 
        // A instância deve ser sempre da classe filha.
        // Porém, isso não impede a gente de usar uma referência pra essa classe.
        // Olha lá no private que faço isso pra logger.

        // Funções de configuração
        virtual errorCode_t setup(uint16_t* pins, uint8_t pinCount) = 0;

        // Como essas funções só setam/retornam valores de variáveis da classe,
        // já podemos economizar e definir o comportamento aqui. 
        // Essa função será aplicada pra todas as classes filhas.
        // Nada impede, entretando, de na classe filha a gente redefinir o comportamento
        // dessas funções.
    
        errorCode_t setEncoding(Encoding_t encoding)
        {
            // Avisa que dá ruim se a gente colocar um valor acima do suportado!
            if(encoding >= ENCODE_TYPE__EOF) return ERR_NOT_SUPPORTED;

            _encoding = encoding;
            return ERR_SUCCESS;
        }

        errorCode_t setPulsesPerRev(uint16_t pulses)
        {
            _pulsesPerRev = pulses;
            return ERR_SUCCESS;
        }

        // Funções de operação
        virtual float getRevolutions() = 0;

        virtual uint32_t getRevolutionsCount() = 0;

        // Como essas funções só setam/retornam valores de variáveis da classe,
        // já podemos economizar e definir o comportamento aqui. 
        // Essa função será aplicada pra todas as classes filhas.
        // Nada impede, entretando, de na classe filha a gente redefinir o comportamento
        // dessas funções.
        errorCode_t reset()
        {
            _logger.info("reset");
            _pulseCount = 0;
            return ERR_SUCCESS;
        }

        uint32_t getPulses()
        {
            return _pulseCount;
        }

        // Como as funções de get simplesmente retornam variáveis da classe, já podemos
        // economizar e defirnir o comportamento aqui. Essa função vai ser aplicada pra todas
        // as classes filhas daqui.
        Encoding_t getEncoding()
        {
            return _encoding;
        }

        uint16_t getPulsesPerRev()
        {
            return _pulsesPerRev;
        }

    // Adicionei uma função de "pulsar" pra incrementar a contagem. Não previmos isso no trello,
    // mas achei uma funcionalidade útil. 
    // Protected quer dizer que só as classes filhas tem acesso a essas funções
    protected:
        void _pulse()
        {
            _logger.info("pulse increment");
            _pulseCount++;
        }

        // Como iremos obrigatoriamente armazenar o encoding e os pulsos por revolução,
        // na própria interface a gente já deixa essas variáveis criadas. Assim não precisamos definir
        // cada uma com um nome na hora de herdar.
        uint16_t _pulsesPerRev; 
        Encoding_t _encoding;

        uint32_t _pulseCount;

        // Aqui estou usando uma referência pra logger.
        // Repara que todo o ArduinoLogger é um Logger!
        // A magia acontece quando você não precisa saber disso. Ou seja,
        // vou poder chamar todas as funções que tem na interface logger
        // sem me importar como é feito.
        Logger& _logger;

};


#endif //_MOTOR_ENCODER_H_
