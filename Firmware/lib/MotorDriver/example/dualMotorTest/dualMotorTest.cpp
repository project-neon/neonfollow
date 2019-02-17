#include <Arduino.h>
#include <appConfig.h>

#include <ArduinoLogger.h>
#include <ArduinoTB6612MotorDriver.h>

#define DEBUG_SERIAL Serial
#define PIN_M1_PWM  27
#define PIN_M1_IN1  28
#define PIN_M1_IN2  29
#define PIN_M2_PWM  26
#define PIN_M2_IN1  30
#define PIN_M2_IN2  31

ArduinoLogger leftMotorLogger(DEBUG_SERIAL, "LeftMotorDriver", Logger::LOGGER_LEVEL_INFO);
ArduinoLogger rightMotorLogger(DEBUG_SERIAL, "RightMotorDriver", Logger::LOGGER_LEVEL_INFO);
ArduinoLogger appLogger(DEBUG_SERIAL, "Application", Logger::LOGGER_LEVEL_INFO);

MotorDriver::MotorDriverConfig_t leftConfig = 
{
  .powerPin = PIN_M2_PWM,
  .directionPinA = PIN_M2_IN1,
  .directionPinB = PIN_M2_IN2,
};

MotorDriver::MotorDriverConfig_t rightConfig = 
{
  .powerPin = PIN_M1_PWM,
  .directionPinA = PIN_M1_IN1,
  .directionPinB = PIN_M1_IN2,
};

TB6612MotorDriver leftDriver(leftMotorLogger, leftConfig);
TB6612MotorDriver rightDriver(rightMotorLogger, rightConfig);

void setup() {
  DEBUG_SERIAL.begin(9600);  
  while(DEBUG_SERIAL.available() == 0);

  leftDriver.init();
  leftDriver.coast();

  rightDriver.init();
  rightDriver.coast();
  // put your setup code here, to run once:
}

void loop() {
  while(DEBUG_SERIAL.available() == 0);
  while(DEBUG_SERIAL.available())DEBUG_SERIAL.read();

  leftDriver.setPower(4096/8, MotorDriver::DIRECTION_CLOCKWISE);
  delay(1000);
  leftDriver.coast();
  rightDriver.setPower(4096/8, MotorDriver::DIRECTION_COUNTERCLOCKWISE);
  delay(1000);
  rightDriver.coast();
  delay(1000);
  rightDriver.setPower(4096/8, MotorDriver::DIRECTION_CLOCKWISE);
  delay(1000);
  rightDriver.brake();
  delay(2000);
  // put your main code here, to run repeatedly:
}