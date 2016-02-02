//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mean.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 18-Nov-2015 10:29:30
//

// Include Files
#include "rt_nonfinite.h"
#include "timeDomainHRV.h"
#include "mean.h"

// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[2]
// Return Type  : double
//
double b_mean(const double x_data[], const int x_size[2])
{
  double y;
  int k;
  if (x_size[1] == 0) {
    y = 0.0;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size[1]; k++) {
      y += x_data[k - 1];
    }
  }

  y /= (double)x_size[1];
  return y;
}

//
// Arguments    : const emxArray_real_T *x
// Return Type  : double
//
double mean(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      y += x->data[k - 1];
    }
  }

  y /= (double)x->size[0];
  return y;
}

//
// File trailer for mean.cpp
//
// [EOF]
//
