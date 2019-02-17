#include <Arduino.h>
#include <appConfig.h>

#include <ArduinoLogger.h>
#include <ArduinoTB6612MotorDriver.h>
#include <ArduinoMotorEncoder.h>
#include <ArduinoMotor.h>

#define DEBUG_SERIAL Serial
#define PIN_M1_PWM  27
#define PIN_M1_IN1  28
#define PIN_M1_IN2  29
#define PIN_M2_PWM  26
#define PIN_M2_IN1  30
#define PIN_M2_IN2  31

#define CH_A_PIN 21
#define CH_B_PIN 22
#define PULSES_PER_REV 358.0 // 30:1 - X2_ENCODING

// Como o logLevel_t está definido dentro da classe Logger, precisamos usar
// o Logger:: para acessar qualquer coisa que está no seu namespace.




ArduinoLogger encoderLogger(DEBUG_SERIAL, "EncoderLogger", Logger::LOGGER_LEVEL_ERROR);
ArduinoLogger leftMotorLogger(DEBUG_SERIAL, "LeftMotorDriver", Logger::LOGGER_LEVEL_ERROR);
ArduinoLogger appLogger(DEBUG_SERIAL, "Application", Logger::LOGGER_LEVEL_ERROR);

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

ArduinoMotorEncoder encoder(encoderLogger, MotorEncoder::ENCODE_TYPE_X2, PULSES_PER_REV);
ArduinoMotor leftMotor(leftMotorLogger, leftDriver);

void setup() {
  DEBUG_SERIAL.begin(9600);  

  uint16_t pins[] = {CH_A_PIN, CH_B_PIN};
  encoder.setup(pins, 2);
  leftDriver.init();

  leftMotor._pid.setTunings(1, 0, 0);
  leftMotor.init(&encoder);
  leftMotor.setSpeed(2, 0.5);
  // leftMotor.setInterval(50);
}

void loop() {

  DEBUG_SERIAL.println(leftMotor.getCurrentSpeed());
  delay(50);
  leftMotor.run();

}