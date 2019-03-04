#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define FIX_MAX_ANALOG_READ 1000 //old = 1000
#define MAX_ANALOG_READ 1023 //old = 1023

//
// Project
//
#define PROJECT_NAME            "Sloth Firmware"
#define PROJECT_BOARD           "Maple Mini"
#define PROJECT_VERSION         "v0.8"

//
// Serial DEBUG
//
#define LOG_ENABLED true
#define LOG if(LOG_ENABLED) PC
#define BT Serial3
#define PC	Serial
#define PC_SPEED  115200
#define LOG_INTERVAL  10 //

//
// Bluetooth Configs (Type here)
//
#define BT_SPEED  115200
#define BTRX  1
#define BTTX  0

//
// Interface
//
#define PIN_BTN 32
#define PIN_LED 33

//
// Line Reader Settings
//
#define WHITE_LINE  true
#define NUM_SENSORS 8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  1  // average 4 analog samples per sensor reading
#define EMITTER_PIN 12  // emitter is controlled by digital pin 2
#define PIN_LR_S1 11  // AIN0
#define PIN_LR_S2 10  // AIN1
#define PIN_LR_S3 9   // AIN2
#define PIN_LR_S4 8   // AIN3
#define PIN_LR_S5 7   // AIN4
#define PIN_LR_S6 6   // AIN5
#define PIN_LR_S7 5   // AIN6
#define PIN_LR_S8 4   // AIN7
#define STRAIGHT_FIX  100

//
// Line Reader Settings
//
#define BAT_SENSE_PIN 3   // AIN8
//
//Lap Sensor Settings
//
#define CROSS_COUNTER 6
#define PIN_TRACK_MARKING_LEFT  15
#define PIN_TRACK_MARKING_RIGHT 16

//
// General Settings
//
#define STOP_BY_TIME true
#define LAP_TIME 500 //in seconds
#define STOP_BY_DISTANCE true
#define FINAL_TARGET_POSITION   13.50  // in meters
// #define FINAL_TARGET_POSITION   1.0
#define ACCELERATION_ENABLED true
#define ACCELERATION_INTERVAL 0.01
#define MAPPING_ENABLED false
#define FIRST_MARK_POSITION 0.5
#define OFFSET_ACELERATION 0.30
#define OFFSET_DESACELERATION 0.0
#define ACCELERATION_UP   5.00
#define ACCELERATION_DOWN -10.00

//
//Marking Settings
//

//
// Motors config (H-Bridge)
//
#define REVERSE 0.00
// #define MOTORS_ENABLE true
#define PIN_M1_PWM  26
#define PIN_M1_IN1  30
#define PIN_M1_IN2  31
#define PIN_M2_PWM  27
#define PIN_M2_IN1  28
#define PIN_M2_IN2  29

//
// Encoder config (Quadrature)
//
// #define PULSES_PER_REV 179.0 // 30:1 - X2_ENCODING
#define PULSES_PER_REV 358.0 // 30:1 - X4_ENCODING
#define PIN_ENC1_A  20
#define PIN_ENC1_B  19
#define PIN_ENC2_A  21
#define PIN_ENC2_B  22
//#define M_PI 3.14159
#define POSITION_FIX  0
#define WHEEL_RADIUS 0.020  // D = 40mm
#define WHEEL_PERIMETER (2.0*WHEEL_RADIUS*M_PI) // WHEEL_RADIUS * PI
#define PULSES2DISTANCE(p) (p / PULSES_PER_REV * WHEEL_PERIMETER)
#define AVG(l,r) ((l + r) / 2.0)
#define DIF(l,r) (r - l)
//
// Pulses to Distance
//

#define SlowCurve 0
#define Curve     1
#define FastCurve 2
#define Straight  3
#define Stop      4

#define TRACK_EVENT_NAME HACKPULICA_NORMAL_NEW
#define GAIN_NUMBER PD0

#endif
