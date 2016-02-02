//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: std.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 18-Nov-2015 10:29:30
//

// Include Files
#include "rt_nonfinite.h"
#include "timeDomainHRV.h"
#include "std.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *varargin_1
// Return Type  : double
//
double b_std(const emxArray_real_T *varargin_1)
{
  double y;
  int n;
  int d;
  int ix;
  double xbar;
  int k;
  double r;
  n = varargin_1->size[0];
  if (varargin_1->size[0] > 1) {
    d = varargin_1->size[0] - 1;
  } else {
    d = varargin_1->size[0];
  }

  if (varargin_1->size[0] == 0) {
    y = 0.0;
  } else {
    ix = 0;
    xbar = varargin_1->data[0];
    for (k = 2; k <= n; k++) {
      ix++;
      xbar += varargin_1->data[ix];
    }

    xbar /= (double)varargin_1->size[0];
    ix = 0;
    r = varargin_1->data[0] - xbar;
    y = r * r;
    for (k = 2; k <= n; k++) {
      ix++;
      r = varargin_1->data[ix] - xbar;
      y += r * r;
    }

    y /= (double)d;
  }

  return std::sqrt(y);
}

//
// File trailer for std.cpp
//
// [EOF]
//
