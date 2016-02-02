//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: trapz.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 25-Nov-2015 14:25:38
//
#ifndef __TRAPZ_H__
#define __TRAPZ_H__

// Include Files
#include <cmath>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "freqDomainHRV_types.h"

// Function Declarations
extern double b_trapz(const double x[11], const double y[11]);
extern double c_trapz(const double x[25], const double y[25]);
extern double trapz(const double x[5], const double y[5]);

#endif

//
// File trailer for trapz.h
//
// [EOF]
//
