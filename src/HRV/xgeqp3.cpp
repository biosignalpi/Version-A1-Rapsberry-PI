//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgeqp3.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 25-Nov-2015 14:25:38
//

// Include Files
#include "rt_nonfinite.h"
#include "freqDomainHRV.h"
#include "xgeqp3.h"
#include "xnrm2.h"
#include "xscal.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *A
//                double tau_data[]
//                int tau_size[1]
//                int jpvt[2]
// Return Type  : void
//
void xgeqp3(emxArray_real_T *A, double tau_data[], int tau_size[1], int jpvt[2])
{
  int m;
  int mn;
  int i0;
  int k;
  double vn1[2];
  double vn2[2];
  double work[2];
  int j;
  double xnorm;
  int i;
  int i_i;
  int mmi;
  int ix;
  int iy;
  double t;
  double absxk;
  double beta1;
  int lastv;
  int lastc;
  boolean_T exitg2;
  int exitg1;
  int jy;
  m = A->size[0];
  if (A->size[0] <= 2) {
    mn = A->size[0];
  } else {
    mn = 2;
  }

  tau_size[0] = mn;
  for (i0 = 0; i0 < 2; i0++) {
    jpvt[i0] = 1 + i0;
  }

  if (A->size[0] == 0) {
  } else {
    k = 1;
    for (j = 0; j < 2; j++) {
      work[j] = 0.0;
      xnorm = xnrm2(m, A, k);
      vn2[j] = xnorm;
      k += m;
      vn1[j] = xnorm;
    }

    for (i = 0; i + 1 <= mn; i++) {
      i_i = i + i * m;
      mmi = (m - i) - 1;
      k = 0;
      if ((2 - i > 1) && (std::abs(vn1[1]) > std::abs(vn1[i]))) {
        k = 1;
      }

      j = i + k;
      if (j + 1 != i + 1) {
        ix = m * j;
        iy = m * i;
        for (k = 1; k <= m; k++) {
          xnorm = A->data[ix];
          A->data[ix] = A->data[iy];
          A->data[iy] = xnorm;
          ix++;
          iy++;
        }

        k = jpvt[j];
        jpvt[j] = jpvt[i];
        jpvt[i] = k;
        vn1[j] = vn1[i];
        vn2[j] = vn2[i];
      }

      if (i + 1 < m) {
        t = A->data[i_i];
        absxk = 0.0;
        if (1 + mmi <= 0) {
        } else {
          xnorm = b_xnrm2(mmi, A, i_i + 2);
          if (xnorm != 0.0) {
            beta1 = hypot(A->data[i_i], xnorm);
            if (A->data[i_i] >= 0.0) {
              beta1 = -beta1;
            }

            if (std::abs(beta1) < 1.0020841800044864E-292) {
              j = 0;
              do {
                j++;
                xscal(mmi, 9.9792015476736E+291, A, i_i + 2);
                beta1 *= 9.9792015476736E+291;
                t *= 9.9792015476736E+291;
              } while (!(std::abs(beta1) >= 1.0020841800044864E-292));

              xnorm = b_xnrm2(mmi, A, i_i + 2);
              beta1 = hypot(t, xnorm);
              if (t >= 0.0) {
                beta1 = -beta1;
              }

              absxk = (beta1 - t) / beta1;
              xscal(mmi, 1.0 / (t - beta1), A, i_i + 2);
              for (k = 1; k <= j; k++) {
                beta1 *= 1.0020841800044864E-292;
              }

              t = beta1;
            } else {
              absxk = (beta1 - A->data[i_i]) / beta1;
              xscal(mmi, 1.0 / (A->data[i_i] - beta1), A, i_i + 2);
              t = beta1;
            }
          }
        }

        tau_data[i] = absxk;
        A->data[i_i] = t;
      } else {
        tau_data[i] = 0.0;
      }

      if (i + 1 < 2) {
        t = A->data[i_i];
        A->data[i_i] = 1.0;
        if (tau_data[0] != 0.0) {
          lastv = 1 + mmi;
          k = i_i + mmi;
          while ((lastv > 0) && (A->data[k] == 0.0)) {
            lastv--;
            k--;
          }

          lastc = 1;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            k = m;
            do {
              exitg1 = 0;
              if (k + 1 <= m + lastv) {
                if (A->data[k] != 0.0) {
                  exitg1 = 1;
                } else {
                  k++;
                }
              } else {
                lastc = 0;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = 0;
          lastc = 0;
        }

        if (lastv > 0) {
          if (lastc == 0) {
          } else {
            work[0] = 0.0;
            iy = 0;
            j = 1 + m;
            while ((m > 0) && (j <= 1 + m)) {
              ix = i_i;
              xnorm = 0.0;
              i0 = (j + lastv) - 1;
              for (k = j; k <= i0; k++) {
                xnorm += A->data[k - 1] * A->data[ix];
                ix++;
              }

              work[iy] += xnorm;
              iy++;
              j += m;
            }
          }

          if (-tau_data[0] == 0.0) {
          } else {
            iy = m;
            jy = 0;
            j = 1;
            while (j <= lastc) {
              if (work[jy] != 0.0) {
                xnorm = work[jy] * -tau_data[0];
                ix = i_i;
                i0 = lastv + iy;
                for (k = iy; k + 1 <= i0; k++) {
                  A->data[k] += A->data[ix] * xnorm;
                  ix++;
                }
              }

              jy++;
              iy += m;
              j = 2;
            }
          }
        }

        A->data[i_i] = t;
      }

      j = i + 2;
      while (j < 3) {
        k = (i + m) + 1;
        if (vn1[1] != 0.0) {
          xnorm = std::abs(A->data[i + A->size[0]]) / vn1[1];
          xnorm = 1.0 - xnorm * xnorm;
          if (xnorm < 0.0) {
            xnorm = 0.0;
          }

          beta1 = vn1[1] / vn2[1];
          beta1 = xnorm * (beta1 * beta1);
          if (beta1 <= 1.4901161193847656E-8) {
            if (i + 1 < m) {
              xnorm = 0.0;
              if (mmi < 1) {
              } else if (mmi == 1) {
                xnorm = std::abs(A->data[k]);
              } else {
                beta1 = 2.2250738585072014E-308;
                j = k + mmi;
                while (k + 1 <= j) {
                  absxk = std::abs(A->data[k]);
                  if (absxk > beta1) {
                    t = beta1 / absxk;
                    xnorm = 1.0 + xnorm * t * t;
                    beta1 = absxk;
                  } else {
                    t = absxk / beta1;
                    xnorm += t * t;
                  }

                  k++;
                }

                xnorm = beta1 * std::sqrt(xnorm);
              }

              vn1[1] = xnorm;
              vn2[1] = xnorm;
            } else {
              vn1[1] = 0.0;
              vn2[1] = 0.0;
            }
          } else {
            vn1[1] *= std::sqrt(xnorm);
          }
        }

        j = 3;
      }
    }
  }
}

//
// File trailer for xgeqp3.cpp
//
// [EOF]
//
