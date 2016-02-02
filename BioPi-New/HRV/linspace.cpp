//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: linspace.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 18-Nov-2015 10:29:30
//

// Include Files
#include "rt_nonfinite.h"
#include "timeDomainHRV.h"
#include "freqDomainHRV.h"
#include "linspace.h"

// Function Definitions

//
// Arguments    : double d1
//                double d2
//                double y[33]
// Return Type  : void
//
void linspace(double d1, double d2, double y[33])
{
  double delta1;
  double delta2;
  int k;
  y[32] = d2;
  y[0] = d1;
  if (((d1 < 0.0) != (d2 < 0.0)) && ((std::abs(d1) > 8.9884656743115785E+307) ||
       (std::abs(d2) > 8.9884656743115785E+307))) {
    delta1 = d1 / 32.0;
    delta2 = d2 / 32.0;
    for (k = 0; k < 31; k++) {
      y[1 + k] = (d1 + delta2 * (1.0 + (double)k)) - delta1 * (1.0 + (double)k);
    }
  } else {
    delta1 = (d2 - d1) / 32.0;
    for (k = 0; k < 31; k++) {
      y[1 + k] = d1 + (1.0 + (double)k) * delta1;
    }
  }
}


//
// Arguments    : double d2
//                double y[512]
// Return Type  : void
//
void linspace(double d2, double y[512])
{
  double delta1;
  int k;
  y[511] = d2;
  y[0] = 0.0;
  if ((d2 < 0.0) && (std::abs(d2) > 8.9884656743115785E+307)) {
    delta1 = d2 / 511.0;
    for (k = 0; k < 510; k++) {
      y[1 + k] = delta1 * (1.0 + (double)k);
    }
  } else {
    delta1 = d2 / 511.0;
    for (k = 0; k < 510; k++) {
      y[1 + k] = (1.0 + (double)k) * delta1;
    }
  }
}

//
// File trailer for linspace.cpp
//
// [EOF]
//
