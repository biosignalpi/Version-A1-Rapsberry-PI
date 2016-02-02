//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeDomainHRV.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 18-Nov-2015 10:29:30
//

// Include Files
#include "rt_nonfinite.h"
#include "timeDomainHRV.h"
#include "mean.h"
#include "timeDomainHRV_emxutil.h"
#include "sum.h"
#include "hist.h"
#include "histc.h"
#include "linspace.h"
#include "std.h"
#include "abs.h"
#include "diff.h"
#include "median.h"

// Function Declarations
static double RMSSD(const emxArray_real_T *ibi);
static double SDNNi(const emxArray_real_T *ibi, int t);
static int mul_s32_s32_s32_sat(int a, int b);
static void mul_wide_s32(int in0, int in1, unsigned int *ptrOutBitsHi, unsigned
  int *ptrOutBitsLo);
static void pNNx(const emxArray_real_T *ibi, int x, double *p, double *n);
static double rt_roundd_snf(double u);
static double tinn(const emxArray_real_T *ibi);

// Function Definitions

//
// RMSSD: root mean square of successive RR differences
// Arguments    : const emxArray_real_T *ibi
// Return Type  : double
//
static double RMSSD(const emxArray_real_T *ibi)
{
  double output;
  emxArray_real_T *differences;
  emxArray_real_T *y;
  unsigned int differences_idx_0;
  int k;
  double A;
  emxInit_real_T(&differences, 1);
  emxInit_real_T(&y, 1);
  diff(ibi, y);
  b_abs(y, differences);

  // successive ibi diffs
  differences_idx_0 = (unsigned int)differences->size[0];
  k = y->size[0];
  y->size[0] = (int)differences_idx_0;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
  for (k = 0; k + 1 <= differences->size[0]; k++) {
    y->data[k] = differences->data[k] * differences->data[k];
  }

  A = sum(y);
  output = std::sqrt(A / (double)differences->size[0]);
  emxFree_real_T(&y);
  emxFree_real_T(&differences);
  return output;
}

//
// SDNNi: SDNN index is the mean of all the standard deviations of
// NN (normal RR) intervals for all windows of lenght t.
// Arguments    : const emxArray_real_T *ibi
//                int t
// Return Type  : double
//
static double SDNNi(const emxArray_real_T *ibi, int t)
{
  double output;
  emxArray_real_T *tmp;
  unsigned int a;
  int i1;
  double A;
  int y;
  int i0;
  int i2;
  emxArray_real_T *b_ibi;
  emxArray_real_T *c_ibi;
  int b_i1;
  emxInit_real_T(&tmp, 1);
  a = 0U;
  i1 = 1;
  A = sum(ibi);
  A = rt_roundd_snf(A / (double)t);
  if (A < 2.147483648E+9) {
    if (A >= -2.147483648E+9) {
      y = (int)A;
    } else {
      y = MIN_int32_T;
    }
  } else if (A >= 2.147483648E+9) {
    y = MAX_int32_T;
  } else {
    y = 0;
  }

  i0 = tmp->size[0];
  tmp->size[0] = y;
  emxEnsureCapacity((emxArray__common *)tmp, i0, (int)sizeof(double));
  for (i0 = 0; i0 < y; i0++) {
    tmp->data[i0] = 0.0;
  }

  i2 = 1;
  emxInit_real_T(&b_ibi, 1);
  emxInit_real_T(&c_ibi, 1);
  while (i2 - 1 <= ibi->size[0] - 1) {
    if (i1 > i2) {
      i0 = 0;
      b_i1 = 0;
    } else {
      i0 = i1 - 1;
      b_i1 = i2;
    }

    y = c_ibi->size[0];
    c_ibi->size[0] = b_i1 - i0;
    emxEnsureCapacity((emxArray__common *)c_ibi, y, (int)sizeof(double));
    y = b_i1 - i0;
    for (b_i1 = 0; b_i1 < y; b_i1++) {
      c_ibi->data[b_i1] = ibi->data[i0 + b_i1];
    }

    if (sum(c_ibi) >= t) {
      a++;
      if (i1 > i2) {
        i0 = 0;
        b_i1 = 0;
      } else {
        i0 = i1 - 1;
        b_i1 = i2;
      }

      y = b_ibi->size[0];
      b_ibi->size[0] = b_i1 - i0;
      emxEnsureCapacity((emxArray__common *)b_ibi, y, (int)sizeof(double));
      y = b_i1 - i0;
      for (b_i1 = 0; b_i1 < y; b_i1++) {
        b_ibi->data[b_i1] = ibi->data[i0 + b_i1];
      }

      tmp->data[(int)a - 1] = b_std(b_ibi);
      i1 = i2;
    }

    i2++;
  }

  emxFree_real_T(&c_ibi);
  emxFree_real_T(&b_ibi);
  output = mean(tmp);
  emxFree_real_T(&tmp);
  return output;
}

//
// Arguments    : int a
//                int b
// Return Type  : int
//
static int mul_s32_s32_s32_sat(int a, int b)
{
  int result;
  unsigned int u32_clo;
  unsigned int u32_chi;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  if (((int)u32_chi > 0) || ((u32_chi == 0U) && (u32_clo >= 2147483648U))) {
    result = MAX_int32_T;
  } else if (((int)u32_chi < -1) || (((int)u32_chi == -1) && (u32_clo <
               2147483648U))) {
    result = MIN_int32_T;
  } else {
    result = (int)u32_clo;
  }

  return result;
}

//
// Arguments    : int in0
//                int in1
//                unsigned int *ptrOutBitsHi
//                unsigned int *ptrOutBitsLo
// Return Type  : void
//
static void mul_wide_s32(int in0, int in1, unsigned int *ptrOutBitsHi, unsigned
  int *ptrOutBitsLo)
{
  unsigned int absIn0;
  unsigned int absIn1;
  int negativeProduct;
  int in0Hi;
  int in0Lo;
  int in1Hi;
  int in1Lo;
  unsigned int productLoHi;
  unsigned int productLoLo;
  unsigned int outBitsLo;
  if (in0 < 0) {
    absIn0 = (unsigned int)-in0;
  } else {
    absIn0 = (unsigned int)in0;
  }

  if (in1 < 0) {
    absIn1 = (unsigned int)-in1;
  } else {
    absIn1 = (unsigned int)in1;
  }

  negativeProduct = !((in0 == 0) || ((in1 == 0) || ((in0 > 0) == (in1 > 0))));
  in0Hi = (int)(absIn0 >> 16U);
  in0Lo = (int)(absIn0 & 65535U);
  in1Hi = (int)(absIn1 >> 16U);
  in1Lo = (int)(absIn1 & 65535U);
  absIn0 = (unsigned int)in0Hi * in1Hi;
  absIn1 = (unsigned int)in0Hi * in1Lo;
  productLoHi = (unsigned int)in0Lo * in1Hi;
  productLoLo = (unsigned int)in0Lo * in1Lo;
  in0Hi = 0;
  outBitsLo = productLoLo + (productLoHi << 16U);
  if (outBitsLo < productLoLo) {
    in0Hi = 1;
  }

  productLoLo = outBitsLo;
  outBitsLo += absIn1 << 16U;
  if (outBitsLo < productLoLo) {
    in0Hi++;
  }

  absIn0 = ((in0Hi + absIn0) + (productLoHi >> 16U)) + (absIn1 >> 16U);
  if (negativeProduct) {
    absIn0 = ~absIn0;
    outBitsLo = ~outBitsLo;
    outBitsLo++;
    if (outBitsLo == 0U) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = outBitsLo;
}

//
// pNNx: percentage of successive/adjacent NN intervals differing by x (ms)
// or more
// Arguments    : const emxArray_real_T *ibi
//                int x
//                double *p
//                double *n
// Return Type  : void
//
static void pNNx(const emxArray_real_T *ibi, int x, double *p, double *n)
{
  emxArray_real_T *differences;
  emxArray_boolean_T *b_x;
  emxArray_real_T *r0;
  int k;
  int loop_ub;
  emxInit_real_T(&differences, 1);
  emxInit_boolean_T(&b_x, 1);
  emxInit_real_T(&r0, 1);
  diff(ibi, r0);
  b_abs(r0, differences);

  // successive ibi diffs (ms)
  k = b_x->size[0];
  b_x->size[0] = differences->size[0];
  emxEnsureCapacity((emxArray__common *)b_x, k, (int)sizeof(boolean_T));
  loop_ub = differences->size[0];
  emxFree_real_T(&r0);
  for (k = 0; k < loop_ub; k++) {
    b_x->data[k] = (differences->data[k] > x);
  }

  if (b_x->size[0] == 0) {
    *n = 0.0;
  } else {
    *n = b_x->data[0];
    for (k = 2; k <= b_x->size[0]; k++) {
      *n += (double)b_x->data[k - 1];
    }
  }

  emxFree_boolean_T(&b_x);
  *p = *n / (double)differences->size[0] * 100.0;
  emxFree_real_T(&differences);
}

//
// Arguments    : double u
// Return Type  : double
//
static double rt_roundd_snf(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

//
// tinn: triangular interpolation of NN interval histogram
// Reference: Standards of Measurement, Physiological Interpretation,
// and Clinical Use
//            Circulation. 1996; 93(5):1043-1065.
// Arguments    : const emxArray_real_T *ibi
// Return Type  : double
//
static double tinn(const emxArray_real_T *ibi)
{
  double output;
  double xout[32];
  double nout[32];
  int ixstart;
  double delta1;
  int iy;
  boolean_T exitg4;
  int idx;
  int ii_data[32];
  signed char ii_size[2];
  int i2;
  static const signed char iv0[2] = { 1, 32 };

  boolean_T exitg3;
  boolean_T guard2 = false;
  int peakindex_size[2];
  double peakindex_data[32];
  int i3;
  double peaki;
  emxArray_real_T *d;
  unsigned int i;
  int m;
  emxArray_real_T *r1;
  double b_m;
  int n;
  double b_n;
  double q[32];
  double y[32];
  double b_q;
  double ylast;
  boolean_T exitg2;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_real_T *b_i;

  // calculate histogram of ibi using nbin bins
  hist(ibi, nout, xout);
  ixstart = 1;
  delta1 = nout[0];
  if (rtIsNaN(nout[0])) {
    iy = 2;
    exitg4 = false;
    while ((!exitg4) && (iy < 33)) {
      ixstart = iy;
      if (!rtIsNaN(nout[iy - 1])) {
        delta1 = nout[iy - 1];
        exitg4 = true;
      } else {
        iy++;
      }
    }
  }

  if (ixstart < 32) {
    while (ixstart + 1 < 33) {
      if (nout[ixstart] > delta1) {
        delta1 = nout[ixstart];
      }

      ixstart++;
    }
  }

  idx = 0;
  for (i2 = 0; i2 < 2; i2++) {
    ii_size[i2] = iv0[i2];
  }

  iy = 1;
  exitg3 = false;
  while ((!exitg3) && (iy < 33)) {
    guard2 = false;
    if (nout[iy - 1] == delta1) {
      idx++;
      ii_data[idx - 1] = iy;
      if (idx >= 32) {
        exitg3 = true;
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }

    if (guard2) {
      iy++;
    }
  }

  if (1 > idx) {
    i2 = 0;
  } else {
    i2 = idx;
  }

  peakindex_size[0] = 1;
  peakindex_size[1] = i2;
  iy = ii_size[0] * i2;
  for (i2 = 0; i2 < iy; i2++) {
    peakindex_data[i2] = ii_data[i2];
  }

  if (1 > idx) {
    i3 = 0;
  } else {
    i3 = idx;
  }

  if (i3 > 1) {
    // if more than one equal peak
    delta1 = b_mean(peakindex_data, peakindex_size);
    peaki = rt_roundd_snf(delta1);

    //  use round(mean)
  } else {
    peaki = peakindex_data[0];
  }

  //  Check the location of peak bin. If it occurs on first bin we cannot
  //  computer TINN. Thus return NaN and exit function.
  if (peaki == 1.0) {
    //  if peak occurs on first bin
    output = rtNaN;

    //  set output as nan
  } else {
    emxInit_real_T1(&d, 2);
    i = 1U;
    i2 = d->size[0] * d->size[1];
    d->size[0] = (int)((peaki - 1.0) * (32.0 - peaki));
    d->size[1] = 3;
    emxEnsureCapacity((emxArray__common *)d, i2, (int)sizeof(double));
    iy = (int)((peaki - 1.0) * (32.0 - peaki)) * 3;
    for (i2 = 0; i2 < iy; i2++) {
      d->data[i2] = 0.0;
    }

    // create variable to hold difference values
    m = 0;
    emxInit_real_T1(&r1, 2);
    while (m <= (int)-(1.0 + (-1.0 - (peaki - 1.0))) - 1) {
      b_m = (peaki - 1.0) + -(double)m;
      for (n = 0; n < (int)(32.0 + (1.0 - (peaki + 1.0))); n++) {
        b_n = (peaki + 1.0) + (double)n;

        // define triangle that fits the histogram
        memset(&q[0], 0, sizeof(double) << 5);
        if (1.0 > b_m) {
          iy = 0;
        } else {
          iy = (int)b_m;
        }

        for (i2 = 0; i2 < iy; i2++) {
          ii_data[i2] = i2;
        }

        for (i2 = 0; i2 < iy; i2++) {
          q[ii_data[i2]] = 0.0;
        }

        if (b_n > 32.0) {
          i2 = 0;
          idx = -1;
        } else {
          i2 = (int)b_n - 1;
          idx = 31;
        }

        iy = idx - i2;
        for (ixstart = 0; ixstart <= iy; ixstart++) {
          ii_data[ixstart] = i2 + ixstart;
        }

        iy = (idx - i2) + 1;
        for (i2 = 0; i2 < iy; i2++) {
          q[ii_data[i2]] = 0.0;
        }

        if (b_m > peaki) {
          i2 = 0;
        } else {
          i2 = (int)b_m - 1;
        }

        delta1 = (peaki - b_m) + 1.0;
        if (delta1 < 0.0) {
          delta1 = 0.0;
        }

        idx = r1->size[0] * r1->size[1];
        r1->size[0] = 1;
        r1->size[1] = (int)std::floor(delta1);
        emxEnsureCapacity((emxArray__common *)r1, idx, (int)sizeof(double));
        if (r1->size[1] >= 1) {
          r1->data[r1->size[1] - 1] = nout[(int)peaki - 1];
          if (r1->size[1] >= 2) {
            r1->data[0] = 0.0;
            if (r1->size[1] >= 3) {
              delta1 = nout[(int)peaki - 1] / ((double)r1->size[1] - 1.0);
              idx = r1->size[1];
              for (ixstart = 0; ixstart <= idx - 3; ixstart++) {
                r1->data[1 + ixstart] = (1.0 + (double)ixstart) * delta1;
              }
            }
          }
        }

        iy = r1->size[1];
        for (idx = 0; idx < iy; idx++) {
          q[i2 + idx] = r1->data[r1->size[0] * idx];
        }

        if (peaki > b_n) {
          i2 = 0;
        } else {
          i2 = (int)peaki - 1;
        }

        delta1 = (b_n - peaki) + 1.0;
        if (delta1 < 0.0) {
          delta1 = 0.0;
        }

        idx = r1->size[0] * r1->size[1];
        r1->size[0] = 1;
        r1->size[1] = (int)std::floor(delta1);
        emxEnsureCapacity((emxArray__common *)r1, idx, (int)sizeof(double));
        if (r1->size[1] >= 1) {
          r1->data[r1->size[1] - 1] = 0.0;
          if (r1->size[1] >= 2) {
            r1->data[0] = nout[(int)peaki - 1];
            if (r1->size[1] >= 3) {
              delta1 = (0.0 - nout[(int)peaki - 1]) / ((double)r1->size[1] - 1.0);
              idx = r1->size[1];
              for (ixstart = 0; ixstart <= idx - 3; ixstart++) {
                r1->data[1 + ixstart] = nout[(int)peaki - 1] + (1.0 + (double)
                  ixstart) * delta1;
              }
            }
          }
        }

        iy = r1->size[1];
        for (idx = 0; idx < iy; idx++) {
          q[i2 + idx] = r1->data[r1->size[0] * idx];
        }

        // integrate squared difference
        for (ixstart = 0; ixstart < 32; ixstart++) {
          b_q = nout[ixstart] - q[ixstart];
          y[ixstart] = b_q * b_q;
        }

        delta1 = 0.0;
        iy = 0;
        ylast = y[0];
        for (ixstart = 0; ixstart < 31; ixstart++) {
          iy++;
          delta1 += (ylast + y[iy]) / 2.0;
          ylast = y[iy];
        }

        d->data[(int)i - 1] = delta1;
        d->data[((int)i + d->size[0]) - 1] = b_m;
        d->data[((int)i + (d->size[0] << 1)) - 1] = b_n;

        // plot(D); hold on; plot(q,'r'); hold off;
        // title(['d^2 = ' num2str(d(i,1))])
        i++;
      }

      m++;
    }

    emxFree_real_T(&r1);

    // find where minimum square diff occured
    ixstart = 1;
    n = d->size[0];
    delta1 = d->data[0];
    i2 = d->size[0];
    if (i2 > 1) {
      if (rtIsNaN(delta1)) {
        iy = 2;
        exitg2 = false;
        while ((!exitg2) && (iy <= n)) {
          ixstart = iy;
          if (!rtIsNaN(d->data[iy - 1])) {
            delta1 = d->data[iy - 1];
            exitg2 = true;
          } else {
            iy++;
          }
        }
      }

      i2 = d->size[0];
      if (ixstart < i2) {
        while (ixstart + 1 <= n) {
          if (d->data[ixstart] < delta1) {
            delta1 = d->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    emxInit_boolean_T(&x, 1);
    iy = d->size[0];
    i2 = x->size[0];
    x->size[0] = iy;
    emxEnsureCapacity((emxArray__common *)x, i2, (int)sizeof(boolean_T));
    for (i2 = 0; i2 < iy; i2++) {
      x->data[i2] = (d->data[i2] == delta1);
    }

    emxInit_int32_T(&ii, 1);
    ixstart = x->size[0];
    idx = 0;
    i2 = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)ii, i2, (int)sizeof(int));
    iy = 1;
    exitg1 = false;
    while ((!exitg1) && (iy <= ixstart)) {
      guard1 = false;
      if (x->data[iy - 1]) {
        idx++;
        ii->data[idx - 1] = iy;
        if (idx >= ixstart) {
          exitg1 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        iy++;
      }
    }

    if (x->size[0] == 1) {
      if (idx == 0) {
        i2 = ii->size[0];
        ii->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)ii, i2, (int)sizeof(int));
      }
    } else {
      i2 = ii->size[0];
      if (1 > idx) {
        ii->size[0] = 0;
      } else {
        ii->size[0] = idx;
      }

      emxEnsureCapacity((emxArray__common *)ii, i2, (int)sizeof(int));
    }

    emxFree_boolean_T(&x);
    emxInit_real_T(&b_i, 1);
    i2 = b_i->size[0];
    b_i->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)b_i, i2, (int)sizeof(double));
    iy = ii->size[0];
    for (i2 = 0; i2 < iy; i2++) {
      b_i->data[i2] = ii->data[i2];
    }

    emxFree_int32_T(&ii);

    // make sure there is only one choise
    // calculate TINN in (ms)
    output = std::abs(xout[(int)d->data[((int)b_i->data[0] + (d->size[0] << 1))
                      - 1] - 1] - xout[(int)d->data[((int)b_i->data[0] + d->
      size[0]) - 1] - 1]);

    // plot
    //      X=xout(peaki); M=xout(m); N=xout(n); Y=nout(peaki);
    //      figure;
    //      hist(ibi,nbin)
    //      xlimits=get(gca,'xlim');
    //      hold on;
    //      plot(xout,nout,'k')
    //      line([M X N M],[0 Y 0 0],'color','r','linewidth',1.5,'LineStyle','--') 
    //      line([X X],[0 1000],'LineStyle','-.','color','k')
    //      line([0 2000],[Y Y],'LineStyle','-.','color','k')
    //      colormap white
    //
    //      xlabel('IBI (ms)');
    //      ylabel('Number of IBI')
    //      legend({'Histogram','D(t)','q(t)'})
    //      set(gca,'xtick',[xout(m) xout(peaki) xout(n)], ...
    //        'xticklabel',{'N','X','M'}, ...
    //        'ytick',Y,'yticklabel','Y')
    //      set(gca,'xlim',xlimits);
    emxFree_real_T(&b_i);
    emxFree_real_T(&d);
  }

  return output;
}

//
// timeDomainHRV: calculates time-domain hrv of ibi interval series
//  ibi = 2dim ibi array
//  win = window size to use for sdnni (s)
//  xx = value to use for NNx and pNNx (ms)
// Arguments    : const emxArray_real_T *ibi
//                int win
//                int xx
//                struct0_T *output
// Return Type  : void
//
void timeDomainHRV(const emxArray_real_T *ibi, int win, int xx, struct0_T
                   *output)
{
  emxArray_real_T *b_ibi;
  int ixstart;
  int ix;
  int n;
  double miny;
  boolean_T exitg3;
  boolean_T exitg2;
  emxArray_real_T *tmp;
  double b_n;
  double p;
  int y;
  unsigned int a;
  int i1;
  int i2;
  emxArray_real_T *c_ibi;
  emxArray_real_T *d_ibi;
  double c_n[32];
  int e_ibi[1];
  emxArray_real_T f_ibi;
  double maxy;
  double edges[33];
  int exponent;
  int g_ibi[1];
  double nn[33];
  boolean_T exitg1;
  emxInit_real_T(&b_ibi, 1);

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
  //  Copyright (C) 2010, John T. Ramshur, jramshur@gmail.com
  //
  //  This file is part of HRVAS
  //
  //  HRVAS is free software: you can redistribute it and/or modify
  //  it under the terms of the GNU General Public License as published by
  //  the Free Software Foundation, either version 3 of the License, or
  //  (at your option) any later version.
  //
  //  HRVAS is distributed in the hope that it will be useful,
  //  but WITHOUT ANY WARRANTY; without even the implied warranty of
  //  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  //  GNU General Public License for more details.
  //
  //  You should have received a copy of the GNU General Public License
  //  along with HRVAS.  If not, see <http://www.gnu.org/licenses/>.
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
  // check inputs
  ixstart = ibi->size[0];
  ix = b_ibi->size[0];
  b_ibi->size[0] = ixstart;
  emxEnsureCapacity((emxArray__common *)b_ibi, ix, (int)sizeof(double));
  for (ix = 0; ix < ixstart; ix++) {
    b_ibi->data[ix] = ibi->data[ix + ibi->size[0]] * 1000.0;
  }

  // convert ibi to ms
  // assumes ibi units are seconds
  //     if abs(range(ibi))<50 %assume ibi units are seconds
  //             ibi=ibi.*1000; %convert ibi to ms
  //     end
  //     if abs(range(diff(t)))>50 %assume time unites are ms
  //         t=t./1000; %convert time to s
  //     end
  //
  //     if t<1000 %assume win units are (s)
  //         t=t*1000; %convert to (ms)
  //     end
  // calculate and round to nearest 1 decimal point
  ixstart = 1;
  n = b_ibi->size[0];
  miny = b_ibi->data[0];
  if (b_ibi->size[0] > 1) {
    if (rtIsNaN(b_ibi->data[0])) {
      ix = 2;
      exitg3 = false;
      while ((!exitg3) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(b_ibi->data[ix - 1])) {
          miny = b_ibi->data[ix - 1];
          exitg3 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < b_ibi->size[0]) {
      while (ixstart + 1 <= n) {
        if (b_ibi->data[ixstart] > miny) {
          miny = b_ibi->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  output->max = rt_roundd_snf(miny * 10.0) / 10.0;
  ixstart = 1;
  n = b_ibi->size[0];
  miny = b_ibi->data[0];
  if (b_ibi->size[0] > 1) {
    if (rtIsNaN(b_ibi->data[0])) {
      ix = 2;
      exitg2 = false;
      while ((!exitg2) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(b_ibi->data[ix - 1])) {
          miny = b_ibi->data[ix - 1];
          exitg2 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < b_ibi->size[0]) {
      while (ixstart + 1 <= n) {
        if (b_ibi->data[ixstart] < miny) {
          miny = b_ibi->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  emxInit_real_T(&tmp, 1);
  output->min = rt_roundd_snf(miny * 10.0) / 10.0;
  miny = mean(b_ibi) * 10.0;
  output->mean = rt_roundd_snf(miny) / 10.0;
  miny = median(b_ibi) * 10.0;
  output->median = rt_roundd_snf(miny) / 10.0;
  miny = b_std(b_ibi) * 10.0;
  output->SDNN = rt_roundd_snf(miny) / 10.0;
  miny = SDNNi(b_ibi, mul_s32_s32_s32_sat(win, 1000)) * 10.0;
  output->SDANN = rt_roundd_snf(miny) / 10.0;
  pNNx(b_ibi, xx, &p, &b_n);
  output->NNx = rt_roundd_snf(b_n * 10.0) / 10.0;
  output->pNNx = rt_roundd_snf(p * 10.0) / 10.0;
  miny = RMSSD(b_ibi) * 10.0;
  output->RMSSD = rt_roundd_snf(miny) / 10.0;
  y = mul_s32_s32_s32_sat(win, 1000);

  // SDANN: SDANN index is the std of all the mean NN intervals from each
  // segment of lenght t.
  a = 0U;
  i1 = 1;
  miny = sum(b_ibi);
  miny = rt_roundd_snf(miny / (double)y);
  if (miny < 2.147483648E+9) {
    if (miny >= -2.147483648E+9) {
      ixstart = (int)miny;
    } else {
      ixstart = MIN_int32_T;
    }
  } else if (miny >= 2.147483648E+9) {
    ixstart = MAX_int32_T;
  } else {
    ixstart = 0;
  }

  ix = tmp->size[0];
  tmp->size[0] = ixstart;
  emxEnsureCapacity((emxArray__common *)tmp, ix, (int)sizeof(double));
  for (ix = 0; ix < ixstart; ix++) {
    tmp->data[ix] = 0.0;
  }

  i2 = 0;
  emxInit_real_T(&c_ibi, 1);
  emxInit_real_T(&d_ibi, 1);
  while (i2 <= b_ibi->size[0] - 1) {
    if (i1 > 1.0 + (double)i2) {
      ix = 0;
      n = 0;
    } else {
      ix = i1 - 1;
      n = i2 + 1;
    }

    ixstart = d_ibi->size[0];
    d_ibi->size[0] = n - ix;
    emxEnsureCapacity((emxArray__common *)d_ibi, ixstart, (int)sizeof(double));
    ixstart = n - ix;
    for (n = 0; n < ixstart; n++) {
      d_ibi->data[n] = b_ibi->data[ix + n];
    }

    if (sum(d_ibi) >= y) {
      a++;
      if (i1 > 1.0 + (double)i2) {
        ix = 0;
        n = 0;
      } else {
        ix = i1 - 1;
        n = i2 + 1;
      }

      ixstart = c_ibi->size[0];
      c_ibi->size[0] = n - ix;
      emxEnsureCapacity((emxArray__common *)c_ibi, ixstart, (int)sizeof(double));
      ixstart = n - ix;
      for (n = 0; n < ixstart; n++) {
        c_ibi->data[n] = b_ibi->data[ix + n];
      }

      tmp->data[(int)a - 1] = mean(c_ibi);
      i1 = i2 + 1;
    }

    i2++;
  }

  emxFree_real_T(&d_ibi);
  emxFree_real_T(&c_ibi);
  miny = b_std(tmp);
  output->SDNNi = rt_roundd_snf(miny * 10.0) / 10.0;

  // heart rate
  ix = tmp->size[0];
  tmp->size[0] = b_ibi->size[0];
  emxEnsureCapacity((emxArray__common *)tmp, ix, (int)sizeof(double));
  ixstart = b_ibi->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    tmp->data[ix] = 60.0 / (b_ibi->data[ix] / 1000.0);
  }

  miny = mean(tmp) * 10.0;
  output->meanHR = rt_roundd_snf(miny) / 10.0;
  miny = b_std(tmp) * 10.0;
  output->sdHR = rt_roundd_snf(miny) / 10.0;

  // GEOMETRIC HRV
  // calculate number of bins to use in histogram
  // 1/128 seconds. Reference: (1996) Heart rate variability:
  // standards of measurement, physiological interpretation and
  // clinical use.
  // temp
  // hrvti: HRV triangular index
  // calculate samples in bin (n) and x location of bins (xout)
  ixstart = b_ibi->size[0];
  emxFree_real_T(&tmp);
  if (ixstart == 0) {
    memset(&c_n[0], 0, sizeof(double) << 5);
  } else {
    e_ibi[0] = b_ibi->size[0];
    f_ibi = *b_ibi;
    f_ibi.size = (int *)&e_ibi;
    f_ibi.numDimensions = 1;
    MinAndMaxNoNonFinites(&f_ibi, &miny, &maxy);
    if (miny == maxy) {
      miny = (miny - 16.0) - 0.5;
      maxy = (maxy + 16.0) - 0.5;
    }

    linspace(miny, maxy, edges);
    edges[0] = rtMinusInf;
    edges[32] = rtInf;
    for (ixstart = 0; ixstart < 31; ixstart++) {
      miny = std::abs(edges[ixstart + 1]);
      if ((!rtIsInf(miny)) && (!rtIsNaN(miny))) {
        if (miny <= 2.2250738585072014E-308) {
          miny = 4.94065645841247E-324;
        } else {
          frexp(miny, &exponent);
          miny = std::ldexp(1.0, exponent - 53);
        }
      } else {
        miny = rtNaN;
      }

      edges[ixstart + 1] += miny;
    }

    g_ibi[0] = b_ibi->size[0];
    f_ibi = *b_ibi;
    f_ibi.size = (int *)&g_ibi;
    f_ibi.numDimensions = 1;
    histc(&f_ibi, edges, nn);
    memcpy(&c_n[0], &nn[0], sizeof(double) << 5);
    c_n[31] += nn[32];
  }

  ixstart = 1;
  miny = c_n[0];
  if (rtIsNaN(c_n[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 33)) {
      ixstart = ix;
      if (!rtIsNaN(c_n[ix - 1])) {
        miny = c_n[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 32) {
    while (ixstart + 1 < 33) {
      if (c_n[ixstart] > miny) {
        miny = c_n[ixstart];
      }

      ixstart++;
    }
  }

  // hrv ti
  output->HRVTi = rt_roundd_snf((double)b_ibi->size[0] / miny * 10.0) / 10.0;
  miny = tinn(b_ibi) * 10.0;
  output->TINN = rt_roundd_snf(miny) / 10.0;
  emxFree_real_T(&b_ibi);
}

//
// File trailer for timeDomainHRV.cpp
//
// [EOF]
//
