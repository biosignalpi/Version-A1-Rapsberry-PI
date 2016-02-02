//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: hist.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 18-Nov-2015 10:29:30
//
#ifndef __HIST_H__
#define __HIST_H__

// Include Files
#include <cmath>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "timeDomainHRV_types.h"

// Function Declarations
extern void MinAndMaxNoNonFinites(const emxArray_real_T *y, double *miny, double
  *maxy);
extern void hist(const emxArray_real_T *Y, double no[32], double xo[32]);

#endif

//
// File trailer for hist.h
//
// [EOF]
//
