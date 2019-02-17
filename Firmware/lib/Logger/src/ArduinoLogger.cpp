#include "ArduinoLogger.h"

ArduinoLogger::ArduinoLogger(Stream& port, const char* moduleName, logLevel_t level)
:_arduinoPort(port)
{
    _moduleName = moduleName;
    _logLevel = level;
    _isEnabled = true;
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

void ArduinoLogger::send(logLevel_t level, const char* levelTag, const char* message)
{
    if(_isEnabled && _logLevel >= level)
    {
        printHeader(levelTag);
        _arduinoPort.println(message);
    }
}

void ArduinoLogger::critical(const char* message)
{
    send(LOGGER_LEVEL_CRITICAL, "CRITICAL", message);
}

void ArduinoLogger::error(const char* message)
{
    send(LOGGER_LEVEL_ERROR, "ERROR", message);
}

void ArduinoLogger::warning(const char* message)
{
    send(LOGGER_LEVEL_WARNING, "WARNING", message);
}

void ArduinoLogger::info(const char* message)
{
    send(LOGGER_LEVEL_INFO, "INFO", message);
}

void ArduinoLogger::enable()
{
    _isEnabled = true;
}

void ArduinoLogger::disable()
{
    _isEnabled = false;
}