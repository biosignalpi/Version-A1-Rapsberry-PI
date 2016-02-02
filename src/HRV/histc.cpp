//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: histc.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 18-Nov-2015 10:29:30
//

// Include Files
#include "rt_nonfinite.h"
#include "timeDomainHRV.h"
#include "histc.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *X
//                const double edges[33]
//                double N[33]
// Return Type  : void
//
void histc(const emxArray_real_T *X, const double edges[33], double N[33])
{
  int xind;
  int k;
  int low_i;
  int low_ip1;
  int high_i;
  int mid_i;
  memset(&N[0], 0, 33U * sizeof(double));
  xind = 0;
  for (k = 0; k < X->size[0]; k++) {
    low_i = 0;
    if (!rtIsNaN(X->data[xind])) {
      if ((X->data[xind] >= edges[0]) && (X->data[xind] < edges[32])) {
        low_i = 1;
        low_ip1 = 2;
        high_i = 33;
        while (high_i > low_ip1) {
          mid_i = (low_i + high_i) >> 1;
          if (X->data[xind] >= edges[mid_i - 1]) {
            low_i = mid_i;
            low_ip1 = mid_i + 1;
          } else {
            high_i = mid_i;
          }
        }
      }

      if (X->data[xind] == edges[32]) {
        low_i = 33;
      }
    }

    if (low_i > 0) {
      N[low_i - 1]++;
    }

    xind++;
  }
}

//
// File trailer for histc.cpp
//
// [EOF]
//
