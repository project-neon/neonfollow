#ifndef _NEON_ARDUINO_LOGGER_H_
#define _NEON_ARDUINO_LOGGER_H_

#include <Arduino.h>
#include "Logger.h"

class ArduinoLogger : public Logger
{

public:
    ArduinoLogger(Stream& port, const char* moduleName, logLevel_t level);

    void critical(const char* message);
    void error(const char* message);
    void warning(const char* message);
    void info(const char* message);

    void critical(String message);
    void error(String message);
    void warning(String message);
    void info(String message);

    void enable();
    void disable();
    
private:
    void send(logLevel_t level, const char* levelTag, const char* message);
    void printHeader(const char* messageTag);
    Stream& _arduinoPort;
};

#endif //_NEON_ARDUINO_LOGGER_H_