#include "ArduinoLogger.h"

ArduinoLogger::ArduinoLogger(Stream& port, char* moduleName, logLevel_t level)
:_arduinoPort(port)
{
    _moduleName = moduleName;
    _logLevel = level;
}

void ArduinoLogger::printHeader(const char* messageTag)
{
    // Send the string "[_moduleName][messageTag]: "
    _arduinoPort.print("[");
    _arduinoPort.print(_moduleName);
    _arduinoPort.print("]");

    _arduinoPort.print("[");
    _arduinoPort.print(messageTag);
    _arduinoPort.print("]");

    _arduinoPort.print(": ");
}

void ArduinoLogger::send(logLevel_t level, char* levelTag, char* message)
{
    if(_logLevel >= level)
    {
        printHeader(levelTag);
        _arduinoPort.println(message);
    }
}

void ArduinoLogger::critical( char* message)
{
    send(LOGGER_LEVEL_CRITICAL, "CRITICAL", message);
}

void ArduinoLogger::error(char* message)
{
    send(LOGGER_LEVEL_ERROR, "ERROR", message);
}

void ArduinoLogger::warning(char* message)
{
    send(LOGGER_LEVEL_WARNING, "WARNING", message);
}

void ArduinoLogger::info(char* message)
{
    send(LOGGER_LEVEL_INFO, "INFO", message);
}