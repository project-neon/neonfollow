#include "_config.h"
#include "structures.h"

#ifndef SETTINGSSPEED_H
#define SETTINGSSPEED_H

float speedbase = 50;
float kpdir = 2.3;
float kidir = 0.0;
float kddir = 0.050;

#define CONSTANTE 100 //This chance the PID constantes to a visible values

Setup Normal     = {speedbase, kpdir, kidir, kddir};

Setup PD_IRON[]{
    // Target Speed, kp, ki, kd    
    {50, 2.30, 0.0, 0.05},  // Slow Curve

    {50, 2.30, 0.0, 0.05},  // Slow Curve
    {60, 1.50, 0.0, 0.075},  // Slow Curve
    {75, 1.00, 0.0, 0.10},  // Slow Curve
    // {62, 2.50, 0.0, 0.05},  // Curve
    // {70, 2.5, 0.0, 0.05}, // FastCurve    
    // {60, 0.90, 0.0, 0.075}, // Straight                         
};

Setup PD1[]{
    // Target Speed, kp, ki, kd    
    {25, 1.0, 0.0, 0.35},  // Slow Curve
    {40, 1.0, 0.0, 0.35},  // Curve
    {70, 1.65, 0.0, 0.35}, // FastCurve    
    {50, 1.20, 0.0, 0.8}, // Straight                         
};

//SMILE
// Setup SlowCurve = {0.62, 0.00025000, 0.000000, 0.0000050};

// Setup Curve = {0.6, 0.00022, 0.000000, 0.0000050};

// Setup Straight = {1.0, 0.00018, 0.000000, 0.0000075};

// Setup FastCurve = {0.7, 0.00022, 0.000000, 0.0000075};
// Setup FastFastCurve = {0.95, 0.00022, 0.000000, 0.0000075};


Setup PD0[]{
    // Target Speed, kp, ki, kd
    // {30, 2.70, 0.0, 0.21}, // Slow Curve
    {25, 1.0, 0.0, 0.35}, // Slow Curve
    {40, 1.0, 0.0, 0.35},  // Curve
    {70, 1.65, 0.0, 0.35}, // FastCurve
    // {100, 1.5, 0.0, 0.41}, // Straight
    {35, 1.0, 0.0, 0.4}, // Straight
    // {0.10, 0.00010, 0.000000, 0.0000010}  // Stop
};

// OLD SLoth (bigger)

Setup k0[] {
  // Target Speed, kp, ki, kd
  {0.62, 0.00025, 0.000000, 0.0000050}, // Slow Curve
  {0.60, 0.00022, 0.000000, 0.0000050}, // Curve
  {0.70, 0.00022, 0.000000, 0.0000075}, // FastCurve
  {1.00, 0.00018, 0.000000, 0.0000075}, // Straight
  {0.10, 0.00010, 0.000000, 0.0000010}  // Stop
};

Setup k1[] { // SlowCurve,Curve, FastCurve, Straight, Stop

  {0.30, 0.00020, 0.000000, 0.0000035},
  {0.40, 0.00020, 0.000000, 0.0000035},
  {0.70, 0.00022, 0.000000, 0.0000075},
  {1.00, 0.00018, 0.000000, 0.0000075},
  {0.10, 0.00010, 0.000000, 0.0000010}
};

Setup k2[] { // SlowCurve,Curve, FastCurve, Straight, Stop
  // 150mm x 75mm
  {0.30, 0.00020, 0.000000, 0.0000035},
  {0.50, 0.00040, 0.000000, 0.0000060},
  {1.00, 0.00030, 0.000000, 0.0000100},
  {1.00, 0.00020, 0.000000, 0.0000075},
  {0.10, 0.00010, 0.000000, 0.0000010}
};

Setup k3[] { // SlowCurve,Curve, FastCurve, Straight, Stop
  // MOTORS 30:1  120mm x 75mm
  {0.30, 0.00030, 0.000000, 0.0000030},
  // {0.70, 0.00020, 0.000000, 0.0000060},
  // {0.85, 0.00022, 0.000000, 0.000015},
  {0.50, 0.00040, 0.000000, 0.0000060},
  {0.85, 0.00022, 0.000000, 0.000025},
  // {1.00, 0.00022, 0.000000, 0.000025},
  // {0.85, 0.00014, 0.000000, 0.0000150},
  {1.00, 0.00022, 0.000000, 0.000025},
  {0.10, 0.00010, 0.000000, 0.0000010}
};




#endif
