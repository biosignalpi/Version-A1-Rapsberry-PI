//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: median.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 18-Nov-2015 10:29:30
//

// Include Files
#include "rt_nonfinite.h"
#include "timeDomainHRV.h"
#include "median.h"
#include "timeDomainHRV_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *x
// Return Type  : double
//
double median(const emxArray_real_T *x)
{
  double y;
  emxArray_int32_T *idx;
  int i;
  int midm1;
  unsigned int unnamed_idx_0;
  int k;
  emxArray_int32_T *iwork;
  int n;
  boolean_T p;
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  if (x->size[0] == 0) {
    y = rtNaN;
  } else {
    emxInit_int32_T(&idx, 1);
    i = x->size[0];
    midm1 = (i + (i < 0)) >> 1;
    unnamed_idx_0 = (unsigned int)x->size[0];
    i = idx->size[0];
    idx->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)idx, i, (int)sizeof(int));
    k = (int)unnamed_idx_0;
    for (i = 0; i < k; i++) {
      idx->data[i] = 0;
    }

    emxInit_int32_T(&iwork, 1);
    n = x->size[0] + 1;
    i = iwork->size[0];
    iwork->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)iwork, i, (int)sizeof(int));
    for (k = 1; k <= n - 2; k += 2) {
      if ((x->data[k - 1] <= x->data[k]) || rtIsNaN(x->data[k])) {
        p = true;
      } else {
        p = false;
      }

      if (p) {
        idx->data[k - 1] = k;
        idx->data[k] = k + 1;
      } else {
        idx->data[k - 1] = k + 1;
        idx->data[k] = k;
      }
    }

    if ((x->size[0] & 1) != 0) {
      idx->data[x->size[0] - 1] = x->size[0];
    }

    i = 2;
    while (i < n - 1) {
      i2 = i << 1;
      j = 1;
      for (pEnd = 1 + i; pEnd < n; pEnd = qEnd + i) {
        b_p = j;
        q = pEnd - 1;
        qEnd = j + i2;
        if (qEnd > n) {
          qEnd = n;
        }

        k = 0;
        kEnd = qEnd - j;
        while (k + 1 <= kEnd) {
          if ((x->data[idx->data[b_p - 1] - 1] <= x->data[idx->data[q] - 1]) ||
              rtIsNaN(x->data[idx->data[q] - 1])) {
            p = true;
          } else {
            p = false;
          }

          if (p) {
            iwork->data[k] = idx->data[b_p - 1];
            b_p++;
            if (b_p == pEnd) {
              while (q + 1 < qEnd) {
                k++;
                iwork->data[k] = idx->data[q];
                q++;
              }
            }
          } else {
            iwork->data[k] = idx->data[q];
            q++;
            if (q + 1 == qEnd) {
              while (b_p < pEnd) {
                k++;
                iwork->data[k] = idx->data[b_p - 1];
                b_p++;
              }
            }
          }

          k++;
        }

        for (k = 0; k + 1 <= kEnd; k++) {
          idx->data[(j + k) - 1] = iwork->data[k];
        }

        j = qEnd;
      }

      i = i2;
    }

    emxFree_int32_T(&iwork);
    if (rtIsNaN(x->data[idx->data[idx->size[0] - 1] - 1])) {
      y = x->data[idx->data[idx->size[0] - 1] - 1];
    } else if (midm1 << 1 == x->size[0]) {
      if (((x->data[idx->data[midm1 - 1] - 1] < 0.0) && (x->data[idx->data[midm1]
            - 1] >= 0.0)) || rtIsInf(x->data[idx->data[midm1 - 1] - 1]) ||
          rtIsInf(x->data[idx->data[midm1] - 1])) {
        y = (x->data[idx->data[midm1 - 1] - 1] + x->data[idx->data[midm1] - 1]) /
          2.0;
      } else {
        y = x->data[idx->data[midm1 - 1] - 1] + (x->data[idx->data[midm1] - 1] -
          x->data[idx->data[midm1 - 1] - 1]) / 2.0;
      }
    } else {
      y = x->data[idx->data[midm1] - 1];
    }

    emxFree_int32_T(&idx);
  }

  return y;
}

//
// File trailer for median.cpp
//
// [EOF]
//
