#ifndef _NEON_ARDUINO_LOGGER_H_
#define _NEON_ARDUINO_LOGGER_H_

#include "Arduino.h"
#include "Logger.h"

class ArduinoLogger : public Logger
{

public:
    ArduinoLogger(Stream& port, char* moduleName, logLevel_t level);

    void critical(char* message);
    void error(char* message);
    void warning(char* message);
    void info(char* message);

    void setLogLevel(logLevel_t level);

private:
    void send(logLevel_t level, char* levelTag, char* message);
    void printHeader(const char* messageTag);
    Stream& _arduinoPort;
};

#endif //_NEON_ARDUINO_LOGGER_H_