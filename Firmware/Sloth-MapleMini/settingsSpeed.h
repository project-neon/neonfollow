#include "_config.h"
#include "structures.h"

#ifndef SETTINGSSPEED_H
#define SETTINGSSPEED_H

float speedbase = 25;
float kpdir = 1.0;
float kidir = 0.0;
float kddir = 0.35;

#define CONSTANTE 100 //This chance the PID constantes to a visible values

Setup Normal     = {speedbase, kpdir, kidir, kddir};

Setup PD0[] {
  // Target Speed, kp, ki, kd
  {30, 2.70, 0.0, 0.21}, // Slow Curve
  {40, 1.2, 0.0, 0.35}, // Curve
  {70, 1.65, 0.0, 0.35}, // FastCurve
  {100, 1.5, 0.0, 0.41}, // Straight
  // {90, 15.0, 0.0, 4.0}, // Straight
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
