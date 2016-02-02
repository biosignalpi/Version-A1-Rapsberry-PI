//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mldivide.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 25-Nov-2015 14:25:38
//

// Include Files
#include "rt_nonfinite.h"
#include "freqDomainHRV.h"
#include "mldivide.h"
#include "freqDomainHRV_emxutil.h"
#include "xgeqp3.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *A
//                const emxArray_real_T *B
//                emxArray_real_T *Y
// Return Type  : void
//
void mldivide(const emxArray_real_T *A, const emxArray_real_T *B,
              emxArray_real_T *Y)
{
  emxArray_real_T *b_A;
  emxArray_real_T *b_B;
  int minmn;
  int maxmn;
  double x_data[4];
  int jpvt[2];
  int j;
  double tol;
  int i;
  int tau_size[1];
  double tau_data[2];
  int rankR;
  double b_Y[2];
  emxInit_real_T1(&b_A, 2);
  emxInit_real_T(&b_B, 1);
  if ((A->size[0] == 0) || (B->size[0] == 0)) {
    minmn = Y->size[0];
    Y->size[0] = 2;
    emxEnsureCapacity((emxArray__common *)Y, minmn, (int)sizeof(double));
    for (minmn = 0; minmn < 2; minmn++) {
      Y->data[minmn] = 0.0;
    }
  } else if (A->size[0] == 2) {
    maxmn = A->size[0] * A->size[1];
    for (minmn = 0; minmn < maxmn; minmn++) {
      x_data[minmn] = A->data[minmn];
    }

    for (minmn = 0; minmn < 2; minmn++) {
      jpvt[minmn] = 1 + minmn;
    }

    minmn = 0;
    if (std::abs(A->data[1]) > std::abs(A->data[0])) {
      minmn = 1;
    }

    if (A->data[minmn] != 0.0) {
      if (minmn != 0) {
        jpvt[0] = 2;
        maxmn = A->size[0] * A->size[1];
        for (minmn = 0; minmn < maxmn; minmn++) {
          x_data[minmn] = A->data[minmn];
        }

        minmn = 0;
        maxmn = 1;
        for (j = 0; j < 2; j++) {
          tol = x_data[minmn];
          x_data[minmn] = x_data[maxmn];
          x_data[maxmn] = tol;
          minmn += 2;
          maxmn += 2;
        }
      }

      x_data[1] /= x_data[0];
    }

    if (x_data[2] != 0.0) {
      x_data[3] += x_data[1] * -x_data[2];
    }

    minmn = Y->size[0];
    Y->size[0] = B->size[0];
    emxEnsureCapacity((emxArray__common *)Y, minmn, (int)sizeof(double));
    maxmn = B->size[0];
    for (minmn = 0; minmn < maxmn; minmn++) {
      Y->data[minmn] = B->data[minmn];
    }

    if (jpvt[0] != 1) {
      Y->data[0] = B->data[1];
      Y->data[1] = B->data[0];
    }

    for (j = 0; j < 2; j++) {
      minmn = j << 1;
      if (Y->data[j] != 0.0) {
        i = j + 2;
        while (i < 3) {
          Y->data[1] -= Y->data[j] * x_data[minmn + 1];
          i = 3;
        }
      }
    }

    for (j = 1; j >= 0; j += -1) {
      minmn = j << 1;
      if (Y->data[j] != 0.0) {
        Y->data[j] /= x_data[j + minmn];
        i = 1;
        while (i <= j) {
          Y->data[0] -= Y->data[1] * x_data[minmn];
          i = 2;
        }
      }
    }
  } else {
    minmn = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)b_A, minmn, (int)sizeof(double));
    maxmn = A->size[0] * A->size[1];
    for (minmn = 0; minmn < maxmn; minmn++) {
      b_A->data[minmn] = A->data[minmn];
    }

    xgeqp3(b_A, tau_data, tau_size, jpvt);
    rankR = 0;
    if (b_A->size[0] < 2) {
      minmn = b_A->size[0];
      maxmn = 2;
    } else {
      minmn = 2;
      maxmn = b_A->size[0];
    }

    if (minmn > 0) {
      tol = (double)maxmn * std::abs(b_A->data[0]) * 2.2204460492503131E-16;
      while ((rankR < minmn) && (std::abs(b_A->data[rankR + b_A->size[0] * rankR])
              >= tol)) {
        rankR++;
      }
    }

    for (i = 0; i < 2; i++) {
      b_Y[i] = 0.0;
    }

    minmn = b_B->size[0];
    b_B->size[0] = B->size[0];
    emxEnsureCapacity((emxArray__common *)b_B, minmn, (int)sizeof(double));
    maxmn = B->size[0];
    for (minmn = 0; minmn < maxmn; minmn++) {
      b_B->data[minmn] = B->data[minmn];
    }

    minmn = b_A->size[0];
    maxmn = b_A->size[0];
    if (maxmn <= 2) {
    } else {
      maxmn = 2;
    }

    for (j = 0; j + 1 <= maxmn; j++) {
      if (tau_data[j] != 0.0) {
        tol = b_B->data[j];
        for (i = j + 1; i + 1 <= minmn; i++) {
          tol += b_A->data[i + b_A->size[0] * j] * b_B->data[i];
        }

        tol *= tau_data[j];
        if (tol != 0.0) {
          b_B->data[j] -= tol;
          for (i = j + 1; i + 1 <= minmn; i++) {
            b_B->data[i] -= b_A->data[i + b_A->size[0] * j] * tol;
          }
        }
      }
    }

    for (i = 0; i + 1 <= rankR; i++) {
      b_Y[jpvt[i] - 1] = b_B->data[i];
    }

    for (j = rankR - 1; j + 1 > 0; j--) {
      b_Y[jpvt[j] - 1] /= b_A->data[j + b_A->size[0] * j];
      i = 1;
      while (i <= j) {
        b_Y[jpvt[0] - 1] -= b_Y[jpvt[j] - 1] * b_A->data[b_A->size[0] * j];
        i = 2;
      }
    }

    minmn = Y->size[0];
    Y->size[0] = 2;
    emxEnsureCapacity((emxArray__common *)Y, minmn, (int)sizeof(double));
    for (minmn = 0; minmn < 2; minmn++) {
      Y->data[minmn] = b_Y[minmn];
    }
  }

  emxFree_real_T(&b_B);
  emxFree_real_T(&b_A);
}

//
// File trailer for mldivide.cpp
//
// [EOF]
//
