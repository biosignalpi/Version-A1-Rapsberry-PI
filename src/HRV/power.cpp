//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: power.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 25-Nov-2015 14:25:38
//

// Include Files
#include "rt_nonfinite.h"
#include "freqDomainHRV.h"
#include "power.h"
#include "freqDomainHRV_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *a
//                emxArray_real_T *y
// Return Type  : void
//
void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int a_idx_0;
  int k;
  a_idx_0 = (unsigned int)a->size[0];
  k = y->size[0];
  y->size[0] = (int)a_idx_0;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
  for (k = 0; k + 1 <= a->size[0]; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

//
// File trailer for power.cpp
//
// [EOF]
//
