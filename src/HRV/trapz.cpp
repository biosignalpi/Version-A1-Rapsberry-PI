//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: trapz.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 25-Nov-2015 14:25:38
//

// Include Files
#include "rt_nonfinite.h"
#include "freqDomainHRV.h"
#include "trapz.h"

// Function Definitions

//
// Arguments    : const double x[11]
//                const double y[11]
// Return Type  : double
//
double b_trapz(const double x[11], const double y[11])
{
  double z;
  double b_x[11];
  int ix;
  int iy;
  double ylast;
  int k;
  memcpy(&b_x[0], &x[0], 11U * sizeof(double));
  for (ix = 0; ix < 10; ix++) {
    b_x[ix] = b_x[ix + 1] - b_x[ix];
  }

  z = 0.0;
  ix = -1;
  iy = 0;
  ylast = y[0];
  for (k = 0; k < 10; k++) {
    iy++;
    ix++;
    z += b_x[ix] * ((ylast + y[iy]) / 2.0);
    ylast = y[iy];
  }

  return z;
}

//
// Arguments    : const double x[25]
//                const double y[25]
// Return Type  : double
//
double c_trapz(const double x[25], const double y[25])
{
  double z;
  double b_x[25];
  int ix;
  int iy;
  double ylast;
  int k;
  memcpy(&b_x[0], &x[0], 25U * sizeof(double));
  for (ix = 0; ix < 24; ix++) {
    b_x[ix] = b_x[ix + 1] - b_x[ix];
  }

  z = 0.0;
  ix = -1;
  iy = 0;
  ylast = y[0];
  for (k = 0; k < 24; k++) {
    iy++;
    ix++;
    z += b_x[ix] * ((ylast + y[iy]) / 2.0);
    ylast = y[iy];
  }

  return z;
}

//
// Arguments    : const double x[5]
//                const double y[5]
// Return Type  : double
//
double trapz(const double x[5], const double y[5])
{
  double z;
  double b_x[5];
  int ix;
  int iy;
  double ylast;
  int k;
  for (ix = 0; ix < 5; ix++) {
    b_x[ix] = x[ix];
  }

  for (ix = 0; ix < 4; ix++) {
    b_x[ix] = b_x[ix + 1] - b_x[ix];
  }

  z = 0.0;
  ix = -1;
  iy = 0;
  ylast = y[0];
  for (k = 0; k < 4; k++) {
    iy++;
    ix++;
    z += b_x[ix] * ((ylast + y[iy]) / 2.0);
    ylast = y[iy];
  }

  return z;
}

//
// File trailer for trapz.cpp
//
// [EOF]
//
