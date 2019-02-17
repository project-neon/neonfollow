#ifndef _NEON_LOGGER_H_
#define _NEON_LOGGER_H_

class Logger
{
public:
    typedef enum logLevel{
        LOGGER_LEVEL_CRITICAL = 0,  // Highest priority
        LOGGER_LEVEL_ERROR,
        LOGGER_LEVEL_WARNING,
        LOGGER_LEVEL_INFO, // Lowest priority
    }logLevel_t;

    virtual void critical(char* message) = 0;
    virtual void error(char* message) = 0;
    virtual void warning(char* message) = 0;
    virtual void info(char* message) = 0;

    virtual void enable() = 0;
    virtual void disable() = 0;

    void setLogLevel(logLevel_t level)
    {
        _logLevel = level;
    };

protected:
    virtual void send(logLevel_t level, char* levelTag,  char* message);

    logLevel_t _logLevel;
    char* _logLevelTag;
    char* _moduleName;
    void* _port;
    bool _isEnabled;
};

#endif //_NEON_LOGGER_H_