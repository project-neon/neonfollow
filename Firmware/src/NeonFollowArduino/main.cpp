#include <Arduino.h>
#include <appConfig.h>

#include <ArduinoLogger.h>
#include <ArduinoMotorEncoder.h>

#define DEBUG_SERIAL    Serial
#define PULSES_PER_REV  10

#define PULSE_GEN_PIN 10
#define CH_A_PIN 11
#define CH_B_PIN 9

// Como o logLevel_t está definido dentro da classe Logger, precisamos usar
// o Logger:: para acessar qualquer coisa que está no seu namespace.

ArduinoLogger appLogger(DEBUG_SERIAL, "ApplicationLogger", Logger::LOGGER_LEVEL_INFO);
ArduinoLogger encoderLogger(DEBUG_SERIAL, "EncoderLogger", Logger::LOGGER_LEVEL_INFO);
ArduinoMotorEncoder encoder(encoderLogger, MotorEncoder::ENCODE_TYPE_X4, PULSES_PER_REV);

void setup() {
  DEBUG_SERIAL.begin(9600);
  uint16_t pins[] = {CH_A_PIN, CH_B_PIN};
  encoder.setup(pins, 2);

  pinMode(PULSE_GEN_PIN, OUTPUT); //OUTPUT_OPEN_DRAIN
  digitalWrite(PULSE_GEN_PIN, LOW);

  // put your setup code here, to run once:
}

void loop() {
  appLogger.info("Starting test...");
  digitalWrite(PULSE_GEN_PIN, HIGH);
  delay(250);
  digitalWrite(PULSE_GEN_PIN, LOW);
  delay(250);

  uint16_t pulses = encoder.getPulses();
  uint16_t revCount = encoder.getRevolutionsCount();
  float rev = encoder.getRevolutions();

  // Aqui tem algumas boas práticas pra usar o logger. Como ele recebe uma const string,
  // é necessário escrever a String e depois usar a função c_str();
  String msg1 = "Pulses: " + String(pulses);
  String msg2 = "Revolutions: " + String(revCount);
  String msg3 = "Revolutions: " + String(rev);

  appLogger.info(msg1.c_str());
  appLogger.info(msg2.c_str());
  appLogger.info(msg3.c_str());

  if(pulses > 25) encoder.reset();

  appLogger.info("Test end..........");
  delay(250);
}
