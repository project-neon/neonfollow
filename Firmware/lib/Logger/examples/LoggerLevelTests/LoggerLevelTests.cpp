#include <Arduino.h>
#include <appConfig.h>

#include <ArduinoLogger.h>

#define DEBUG_SERIAL Serial

ArduinoLogger logger(DEBUG_SERIAL,"teste", Logger::LOGGER_LEVEL_INFO);

void setup() {
  DEBUG_SERIAL.begin(9600);
  DEBUG_SERIAL.println("Startingt test.");

  pinMode(LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:
}

void callAllLogs()
{
  logger.info("Info message");
  logger.warning("Warning message");
  logger.error("Error message");
  logger.critical("Critical message");
}

void loop() {
  DEBUG_SERIAL.println("\n=====\nStarting test. All log levels should appear");
  logger.setLogLevel(Logger::LOGGER_LEVEL_INFO);
  callAllLogs();

  DEBUG_SERIAL.println("\nStarting test. Info level shouldn't appear");
  logger.setLogLevel(Logger::LOGGER_LEVEL_WARNING);
  callAllLogs();

  DEBUG_SERIAL.println("\nStarting test. Info and warning level shouldn't appear");
  logger.setLogLevel(Logger::LOGGER_LEVEL_ERROR);
  callAllLogs();

  DEBUG_SERIAL.println("\nStarting test. Only critical level should appear");
  logger.setLogLevel(Logger::LOGGER_LEVEL_CRITICAL);
  callAllLogs();

  delay(1000);
}