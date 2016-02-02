//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mean.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 18-Nov-2015 10:29:30
//
#ifndef __MEAN_H__
#define __MEAN_H__

// Include Files
#include <cmath>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "timeDomainHRV_types.h"
#include "freqDomainHRV_types.h"

// Function Declarations
extern double b_mean(const double x_data[], const int x_size[2]);
extern double mean(const emxArray_real_T *x);

#endif

//
// File trailer for mean.h
//
// [EOF]
//
