//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: preProcessIBI.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 28-Dec-2015 15:01:17
//
#ifndef __PREPROCESSIBI_H__
#define __PREPROCESSIBI_H__

// Include Files
#include <cmath>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "timeDomainHRV_types.h"

// Function Declarations
/**
 * @brief Performs ectopic beat detection and ectopic beat correction
 * @param[in] ibi emxArray_real_T with [t,ibi]
 * @param[out] nibi emxArray_real_T with [t,ibi] after ectopic beat correction
 * @param[out] art logical array for the ibi array
 * @todo fix soo that it performs trending also, neccessary for the Freq-Domain Analysis
 */
extern void preProcessIBI(const emxArray_real_T *ibi, emxArray_real_T *nibi,
  emxArray_boolean_T *art);

#endif

//
// File trailer for preProcessIBI.h
//
// [EOF]
//
