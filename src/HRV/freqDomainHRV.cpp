//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: freqDomainHRV.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 25-Nov-2015 14:25:38
//

// Include Files
#include "rt_nonfinite.h"
#include "freqDomainHRV.h"
#include "sum.h"
#include "power.h"
#include "sin.h"
#include "freqDomainHRV_emxutil.h"
#include "cos.h"
#include "trapz.h"
#include "mean.h"
#include "linspace.h"
#include "mldivide.h"

// Function Declarations
static void b_zipeaks(const double y[11], double pks_data[], int pks_size[2],
                      double locs_data[], int locs_size[2]);
static void c_zipeaks(const double y[25], double pks_data[], int pks_size[2],
                      double locs_data[], int locs_size[2]);
static void calcAreas(double PSD[512], double *output2_hrv_aVLF, double
                      *output2_hrv_aLF, double *output2_hrv_aHF, double
                      *output2_hrv_aTotal, double *output2_hrv_pVLF, double
                      *output2_hrv_pLF, double *output2_hrv_pHF, double
                      *output2_hrv_nLF, double *output2_hrv_nHF, double
                      *output2_hrv_LFHF, double *output2_hrv_peakVLF, double
                      *output2_hrv_peakLF, double *output2_hrv_peakHF, double
                      output2_psd[512], double output2_f[512]);
static void emptyData(double *output_hrv_aVLF, double *output_hrv_aLF, double
                      *output_hrv_aHF, double *output_hrv_aTotal, double
                      *output_hrv_pVLF, double *output_hrv_pLF, double
                      *output_hrv_pHF, double *output_hrv_nLF, double
                      *output_hrv_nHF, double *output_hrv_LFHF, double
                      *output_hrv_peakVLF, double *output_hrv_peakLF, double
                      *output_hrv_peakHF, double output_f[512], double
                      output_psd[512]);
static double rt_atan2d_snf(double u0, double u1);
static double rt_roundd_snf(double u);
static void zipeaks(const double y[5], double pks_data[], int pks_size[2],
                    double locs_data[], int locs_size[2]);

// Function Definitions

//
// zippeaks: finds local maxima of input signal y
// Usage:  peak=zipeaks(y);
// Returns 2x(number of maxima) array
// pks = value at maximum
// locs = index value for maximum
//
// Reference:  2009, George Zipfel (Mathworks File Exchange #24797)
// Arguments    : const double y[11]
//                double pks_data[]
//                int pks_size[2]
//                double locs_data[]
//                int locs_size[2]
// Return Type  : void
//
static void b_zipeaks(const double y[11], double pks_data[], int pks_size[2],
                      double locs_data[], int locs_size[2])
{
  double yD[11];
  int k;
  double x;
  double b_x;
  double c_x;
  double d_x;
  double e_x;
  int i;
  int partialTrueCount;

  // check dimentions
  // Find locations of local maxima
  // yD=1 at maxima, yD=0 otherwise, end point maxima excluded
  yD[0] = 0.0;
  for (k = 0; k < 9; k++) {
    x = y[1 + k] - y[2 + k];
    b_x = y[k] - y[1 + k];
    if (x < 0.0) {
      c_x = -1.0;
    } else if (x > 0.0) {
      c_x = 1.0;
    } else if (x == 0.0) {
      c_x = 0.0;
    } else {
      c_x = x;
    }

    if (b_x < 0.0) {
      d_x = -1.0;
    } else if (b_x > 0.0) {
      d_x = 1.0;
    } else if (b_x == 0.0) {
      d_x = 0.0;
    } else {
      d_x = b_x;
    }

    x = (c_x - d_x) - 0.1;
    if (x < 0.0) {
      e_x = -1.0;
    } else if (x > 0.0) {
      e_x = 1.0;
    } else if (x == 0.0) {
      e_x = 0.0;
    } else {
      e_x = x;
    }

    yD[k + 1] = e_x + 1.0;
  }

  yD[10] = 0.0;

  // Indices of maxima and corresponding values of y
  k = 0;
  for (i = 0; i < 11; i++) {
    if (yD[i] != 0.0) {
      k++;
    }
  }

  locs_size[0] = 1;
  locs_size[1] = k;
  partialTrueCount = 0;
  k = 0;
  for (i = 0; i < 11; i++) {
    if (yD[i] != 0.0) {
      locs_data[partialTrueCount] = 1.0 + (double)i;
      partialTrueCount++;
    }

    if (yD[i] != 0.0) {
      k++;
    }
  }

  pks_size[0] = 1;
  pks_size[1] = k;
  partialTrueCount = 0;
  for (i = 0; i < 11; i++) {
    if (yD[i] != 0.0) {
      pks_data[partialTrueCount] = y[i];
      partialTrueCount++;
    }
  }
}

//
// zippeaks: finds local maxima of input signal y
// Usage:  peak=zipeaks(y);
// Returns 2x(number of maxima) array
// pks = value at maximum
// locs = index value for maximum
//
// Reference:  2009, George Zipfel (Mathworks File Exchange #24797)
// Arguments    : const double y[25]
//                double pks_data[]
//                int pks_size[2]
//                double locs_data[]
//                int locs_size[2]
// Return Type  : void
//
static void c_zipeaks(const double y[25], double pks_data[], int pks_size[2],
                      double locs_data[], int locs_size[2])
{
  double yD[25];
  int k;
  double x;
  double b_x;
  double c_x;
  double d_x;
  double e_x;
  int i;
  int partialTrueCount;

  // check dimentions
  // Find locations of local maxima
  // yD=1 at maxima, yD=0 otherwise, end point maxima excluded
  yD[0] = 0.0;
  for (k = 0; k < 23; k++) {
    x = y[1 + k] - y[2 + k];
    b_x = y[k] - y[1 + k];
    if (x < 0.0) {
      c_x = -1.0;
    } else if (x > 0.0) {
      c_x = 1.0;
    } else if (x == 0.0) {
      c_x = 0.0;
    } else {
      c_x = x;
    }

    if (b_x < 0.0) {
      d_x = -1.0;
    } else if (b_x > 0.0) {
      d_x = 1.0;
    } else if (b_x == 0.0) {
      d_x = 0.0;
    } else {
      d_x = b_x;
    }

    x = (c_x - d_x) - 0.1;
    if (x < 0.0) {
      e_x = -1.0;
    } else if (x > 0.0) {
      e_x = 1.0;
    } else if (x == 0.0) {
      e_x = 0.0;
    } else {
      e_x = x;
    }

    yD[k + 1] = e_x + 1.0;
  }

  yD[24] = 0.0;

  // Indices of maxima and corresponding values of y
  k = 0;
  for (i = 0; i < 25; i++) {
    if (yD[i] != 0.0) {
      k++;
    }
  }

  locs_size[0] = 1;
  locs_size[1] = k;
  partialTrueCount = 0;
  k = 0;
  for (i = 0; i < 25; i++) {
    if (yD[i] != 0.0) {
      locs_data[partialTrueCount] = 1.0 + (double)i;
      partialTrueCount++;
    }

    if (yD[i] != 0.0) {
      k++;
    }
  }

  pks_size[0] = 1;
  pks_size[1] = k;
  partialTrueCount = 0;
  for (i = 0; i < 25; i++) {
    if (yD[i] != 0.0) {
      pks_data[partialTrueCount] = y[i];
      partialTrueCount++;
    }
  }
}

//
// calcAreas - Calulates areas/energy under the PSD curve within the freq
// bands defined by VLF, LF, and HF. Returns areas/energies as ms^2,
// percentage, and normalized units. Also returns LF/HF ratio.
//
// Inputs:
//    PSD: PSD vector
//    F: Freq vector
//    VLF, LF, HF: array containing VLF, LF, and HF freq limits
//    flagNormalize: option to normalize PSD to max(PSD)
// Output:
//
// Usage:
//
//
//    Modified from Gary Clifford's ECG Toolbox: calc_lfhf.m
// Arguments    : double PSD[512]
//                double *output2_hrv_aVLF
//                double *output2_hrv_aLF
//                double *output2_hrv_aHF
//                double *output2_hrv_aTotal
//                double *output2_hrv_pVLF
//                double *output2_hrv_pLF
//                double *output2_hrv_pHF
//                double *output2_hrv_nLF
//                double *output2_hrv_nHF
//                double *output2_hrv_LFHF
//                double *output2_hrv_peakVLF
//                double *output2_hrv_peakLF
//                double *output2_hrv_peakHF
//                double output2_psd[512]
//                double output2_f[512]
// Return Type  : void
//
static void calcAreas(double PSD[512], double *output2_hrv_aVLF, double
                      *output2_hrv_aLF, double *output2_hrv_aHF, double
                      *output2_hrv_aTotal, double *output2_hrv_pVLF, double
                      *output2_hrv_pLF, double *output2_hrv_pHF, double
                      *output2_hrv_nLF, double *output2_hrv_nHF, double
                      *output2_hrv_LFHF, double *output2_hrv_peakVLF, double
                      *output2_hrv_peakLF, double *output2_hrv_peakHF, double
                      output2_psd[512], double output2_f[512])
{
  int ixstart;
  double mtmp;
  int ix;
  boolean_T exitg7;
  int ipks_size[2];
  double ipks_data[5];
  int pks_size[2];
  double pks_data[5];
  int n;
  int itmp;
  boolean_T exitg6;
  double peakVLF;
  boolean_T exitg5;
  static const signed char iv0[5] = { 0, 1, 2, 3, 4 };

  double b_ipks_data[11];
  double b_pks_data[11];
  boolean_T exitg4;
  double peakLF;
  boolean_T exitg3;
  static const signed char iv1[11] = { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

  double c_ipks_data[25];
  double c_pks_data[25];
  boolean_T exitg2;
  double peakHF;
  boolean_T exitg1;
  static const signed char iv2[25] = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };

  double aVLF;
  double aLF;
  double dv0[25];
  double aHF;
  double aTotal;

  // normalize PSD if needed
  ixstart = 1;
  mtmp = PSD[0];
  if (rtIsNaN(PSD[0])) {
    ix = 2;
    exitg7 = false;
    while ((!exitg7) && (ix < 513)) {
      ixstart = ix;
      if (!rtIsNaN(PSD[ix - 1])) {
        mtmp = PSD[ix - 1];
        exitg7 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 512) {
    while (ixstart + 1 < 513) {
      if (PSD[ixstart] > mtmp) {
        mtmp = PSD[ixstart];
      }

      ixstart++;
    }
  }

  for (ixstart = 0; ixstart < 512; ixstart++) {
    PSD[ixstart] /= mtmp;
  }

  //  find the indexes corresponding to the VLF, LF, and HF bands
  // Find peaks
  // VLF Peak
  zipeaks(*(double (*)[5])&PSD[0], pks_data, pks_size, ipks_data, ipks_size);
  if (!(pks_size[1] == 0)) {
    ixstart = 1;
    n = pks_size[1];
    mtmp = pks_data[0];
    itmp = 0;
    if (pks_size[1] > 1) {
      if (rtIsNaN(pks_data[0])) {
        ix = 2;
        exitg6 = false;
        while ((!exitg6) && (ix <= n)) {
          ixstart = ix;
          if (!rtIsNaN(pks_data[ix - 1])) {
            mtmp = pks_data[ix - 1];
            itmp = ix - 1;
            exitg6 = true;
          } else {
            ix++;
          }
        }
      }

      if (ixstart < pks_size[1]) {
        while (ixstart + 1 <= n) {
          if (pks_data[ixstart] > mtmp) {
            mtmp = pks_data[ixstart];
            itmp = ixstart;
          }

          ixstart++;
        }
      }
    }

    peakVLF = 0.009765625 * (double)((int)ipks_data[itmp] - 1);
  } else {
    ixstart = 1;
    mtmp = PSD[0];
    itmp = 0;
    if (rtIsNaN(PSD[0])) {
      ix = 2;
      exitg5 = false;
      while ((!exitg5) && (ix < 6)) {
        ixstart = ix;
        if (!rtIsNaN(PSD[ix - 1])) {
          mtmp = PSD[ix - 1];
          itmp = ix - 1;
          exitg5 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 5) {
      while (ixstart + 1 < 6) {
        if (PSD[iv0[ixstart]] > mtmp) {
          mtmp = PSD[ixstart];
          itmp = ixstart;
        }

        ixstart++;
      }
    }

    peakVLF = 0.009765625 * (double)itmp;
  }

  // LF Peak
  b_zipeaks(*(double (*)[11])&PSD[5], b_pks_data, pks_size, b_ipks_data,
            ipks_size);
  if (!(pks_size[1] == 0)) {
    ixstart = 1;
    n = pks_size[1];
    mtmp = b_pks_data[0];
    itmp = 0;
    if (pks_size[1] > 1) {
      if (rtIsNaN(b_pks_data[0])) {
        ix = 2;
        exitg4 = false;
        while ((!exitg4) && (ix <= n)) {
          ixstart = ix;
          if (!rtIsNaN(b_pks_data[ix - 1])) {
            mtmp = b_pks_data[ix - 1];
            itmp = ix - 1;
            exitg4 = true;
          } else {
            ix++;
          }
        }
      }

      if (ixstart < pks_size[1]) {
        while (ixstart + 1 <= n) {
          if (b_pks_data[ixstart] > mtmp) {
            mtmp = b_pks_data[ixstart];
            itmp = ixstart;
          }

          ixstart++;
        }
      }
    }

    peakLF = 0.048828125 + 0.009765625 * (double)((int)b_ipks_data[itmp] - 1);
  } else {
    ixstart = 1;
    mtmp = PSD[5];
    itmp = 0;
    if (rtIsNaN(PSD[5])) {
      ix = 2;
      exitg3 = false;
      while ((!exitg3) && (ix < 12)) {
        ixstart = ix;
        if (!rtIsNaN(PSD[ix + 4])) {
          mtmp = PSD[ix + 4];
          itmp = ix - 1;
          exitg3 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 11) {
      while (ixstart + 1 < 12) {
        if (PSD[iv1[ixstart]] > mtmp) {
          mtmp = PSD[5 + ixstart];
          itmp = ixstart;
        }

        ixstart++;
      }
    }

    peakLF = 0.048828125 + 0.009765625 * (double)itmp;
  }

  // HF Peak
  c_zipeaks(*(double (*)[25])&PSD[16], c_pks_data, pks_size, c_ipks_data,
            ipks_size);
  if (!(pks_size[1] == 0)) {
    ixstart = 1;
    n = pks_size[1];
    mtmp = c_pks_data[0];
    itmp = 0;
    if (pks_size[1] > 1) {
      if (rtIsNaN(c_pks_data[0])) {
        ix = 2;
        exitg2 = false;
        while ((!exitg2) && (ix <= n)) {
          ixstart = ix;
          if (!rtIsNaN(c_pks_data[ix - 1])) {
            mtmp = c_pks_data[ix - 1];
            itmp = ix - 1;
            exitg2 = true;
          } else {
            ix++;
          }
        }
      }

      if (ixstart < pks_size[1]) {
        while (ixstart + 1 <= n) {
          if (c_pks_data[ixstart] > mtmp) {
            mtmp = c_pks_data[ixstart];
            itmp = ixstart;
          }

          ixstart++;
        }
      }
    }

    peakHF = 0.15625 + 0.009765625 * (double)((int)c_ipks_data[itmp] - 1);
  } else {
    ixstart = 1;
    mtmp = PSD[16];
    itmp = 0;
    if (rtIsNaN(PSD[16])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 26)) {
        ixstart = ix;
        if (!rtIsNaN(PSD[ix + 15])) {
          mtmp = PSD[ix + 15];
          itmp = ix - 1;
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 25) {
      while (ixstart + 1 < 26) {
        if (PSD[iv2[ixstart]] > mtmp) {
          mtmp = PSD[16 + ixstart];
          itmp = ixstart;
        }

        ixstart++;
      }
    }

    peakHF = 0.15625 + 0.009765625 * (double)itmp;
  }

  //  calculate raw areas (power under curve), within the freq bands (ms^2)
  for (ixstart = 0; ixstart < 5; ixstart++) {
    pks_data[ixstart] = 0.009765625 * (double)ixstart;
  }

  aVLF = trapz(pks_data, *(double (*)[5])&PSD[0]);
  for (ixstart = 0; ixstart < 11; ixstart++) {
    b_pks_data[ixstart] = 0.048828125 + 0.009765625 * (double)ixstart;
  }

  aLF = b_trapz(b_pks_data, *(double (*)[11])&PSD[5]);
  for (ixstart = 0; ixstart < 25; ixstart++) {
    dv0[ixstart] = 0.15625 + 0.009765625 * (double)ixstart;
  }

  aHF = c_trapz(dv0, *(double (*)[25])&PSD[16]);
  aTotal = (aVLF + aLF) + aHF;

  // calculate areas relative to the total area (%)
  // calculate normalized areas (relative to HF+LF, n.u.)
  // calculate LF/HF ratio
  // create output structure
  *output2_hrv_aVLF = rt_roundd_snf(aVLF * 1000.0) / 1000.0;
  *output2_hrv_aLF = rt_roundd_snf(aLF * 1000.0) / 1000.0;
  *output2_hrv_aHF = rt_roundd_snf(aHF * 1000.0) / 1000.0;
  *output2_hrv_aTotal = rt_roundd_snf(aTotal * 1000.0) / 1000.0;
  *output2_hrv_pVLF = rt_roundd_snf(aVLF / aTotal * 100.0 * 10.0) / 10.0;
  *output2_hrv_pLF = rt_roundd_snf(aLF / aTotal * 100.0 * 10.0) / 10.0;
  *output2_hrv_pHF = rt_roundd_snf(aHF / aTotal * 100.0 * 10.0) / 10.0;
  *output2_hrv_nLF = rt_roundd_snf(aLF / (aLF + aHF) * 1000.0) / 1000.0;
  *output2_hrv_nHF = rt_roundd_snf(aHF / (aLF + aHF) * 1000.0) / 1000.0;
  *output2_hrv_LFHF = rt_roundd_snf(aLF / aHF * 1000.0) / 1000.0;
  *output2_hrv_peakVLF = rt_roundd_snf(peakVLF * 100.0) / 100.0;
  *output2_hrv_peakLF = rt_roundd_snf(peakLF * 100.0) / 100.0;
  *output2_hrv_peakHF = rt_roundd_snf(peakHF * 100.0) / 100.0;
  for (ixstart = 0; ixstart < 512; ixstart++) {
    output2_psd[ixstart] = PSD[ixstart];
    output2_f[ixstart] = 0.009765625 * (double)ixstart;
  }
}

//
// create output structure of zeros
// Arguments    : double *output_hrv_aVLF
//                double *output_hrv_aLF
//                double *output_hrv_aHF
//                double *output_hrv_aTotal
//                double *output_hrv_pVLF
//                double *output_hrv_pLF
//                double *output_hrv_pHF
//                double *output_hrv_nLF
//                double *output_hrv_nHF
//                double *output_hrv_LFHF
//                double *output_hrv_peakVLF
//                double *output_hrv_peakLF
//                double *output_hrv_peakHF
//                double output_f[512]
//                double output_psd[512]
// Return Type  : void
//
static void emptyData(double *output_hrv_aVLF, double *output_hrv_aLF, double
                      *output_hrv_aHF, double *output_hrv_aTotal, double
                      *output_hrv_pVLF, double *output_hrv_pLF, double
                      *output_hrv_pHF, double *output_hrv_nLF, double
                      *output_hrv_nHF, double *output_hrv_LFHF, double
                      *output_hrv_peakVLF, double *output_hrv_peakLF, double
                      *output_hrv_peakHF, double output_f[512], double
                      output_psd[512])
{
  //  function plotPSD(aH,F,PSD,VLF,LF,HF,limX,limY)
  //
  //      color.vlf=[.5 .5 1];    %vlf color color.lf=[.7 .5 1];     %lf color
  //      color.hf=[.5 1 1];      %hf color
  //
  //      % find the indexes corresponding to the VLF, LF, and HF bands iVLF=
  //      find( (F>=VLF(1)) & (F<VLF(2)) ); iLF = find( (F>=LF(1)) & (F<LF(2))
  //      ); iHF = find( (F>=HF(1)) & (F<HF(2)) );
  //
  //      %plot area under PSD curve area(aH,F(:),PSD(:),'FaceColor',[.8 .8
  //      .8]); hold(aH);
  //      area(aH,F(iVLF(1):iVLF(end)+1),PSD(iVLF(1):iVLF(end)+1), ...
  //          'FaceColor',color.vlf);
  //      area(aH,F(iLF(1):iLF(end)+1),PSD(iLF(1):iLF(end)+1), ...
  //          'FaceColor',color.lf);
  //      area(aH,F(iHF(1):iHF(end)+1),PSD(iHF(1):iHF(end)+1), ...
  //          'FaceColor',color.hf);
  //
  //      if ~isempty(limX)
  //          set(aH,'xlim',limX)
  //      else
  //          limX=[min(F) max(F)];
  //      end if ~isempty(limY)
  //          set(aH,'ylim',limY)
  //      else
  //          limY=[min(PSD) max(PSD)];
  //      end
  //
  //      %draw vertical lines around freq bands line1=line([VLF(2)
  //      VLF(2)],[limY(1) limY(2)]); set(line1,'color',[1 0 0],'parent',aH);
  //      line2=line([LF(2) LF(2)],[limY(1) limY(2)]); set(line2,'color',[1 0
  //      0],'parent',aH); line3=line([HF(2) HF(2)],[limY(1) limY(2)]);
  //      set(line3,'color',[1 0 0],'parent',aH);
  //
  //      hold(aH)
  //
  //  end
  //
  *output_hrv_aVLF = 0.0;
  *output_hrv_aLF = 0.0;
  *output_hrv_aHF = 0.0;
  *output_hrv_aTotal = 0.0;
  *output_hrv_pVLF = 0.0;
  *output_hrv_pLF = 0.0;
  *output_hrv_pHF = 0.0;
  *output_hrv_nLF = 0.0;
  *output_hrv_nHF = 0.0;
  *output_hrv_LFHF = 0.0;
  *output_hrv_peakVLF = 0.0;
  *output_hrv_peakLF = 0.0;
  *output_hrv_peakHF = 0.0;

  // PSD with all zeros
  // % linspace(0.0,maxF-deltaF,nfft)
  linspace(4.990234375, output_f);
  memset(&output_psd[0], 0, sizeof(double) << 9);
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2((double)b_u0, (double)b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
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
// zippeaks: finds local maxima of input signal y
// Usage:  peak=zipeaks(y);
// Returns 2x(number of maxima) array
// pks = value at maximum
// locs = index value for maximum
//
// Reference:  2009, George Zipfel (Mathworks File Exchange #24797)
// Arguments    : const double y[5]
//                double pks_data[]
//                int pks_size[2]
//                double locs_data[]
//                int locs_size[2]
// Return Type  : void
//
static void zipeaks(const double y[5], double pks_data[], int pks_size[2],
                    double locs_data[], int locs_size[2])
{
  double yD[5];
  int k;
  double x;
  double b_x;
  double c_x;
  double d_x;
  double e_x;
  int i;
  int partialTrueCount;

  // check dimentions
  // Find locations of local maxima
  // yD=1 at maxima, yD=0 otherwise, end point maxima excluded
  yD[0] = 0.0;
  for (k = 0; k < 3; k++) {
    x = y[1 + k] - y[2 + k];
    b_x = y[k] - y[1 + k];
    if (x < 0.0) {
      c_x = -1.0;
    } else if (x > 0.0) {
      c_x = 1.0;
    } else if (x == 0.0) {
      c_x = 0.0;
    } else {
      c_x = x;
    }

    if (b_x < 0.0) {
      d_x = -1.0;
    } else if (b_x > 0.0) {
      d_x = 1.0;
    } else if (b_x == 0.0) {
      d_x = 0.0;
    } else {
      d_x = b_x;
    }

    x = (c_x - d_x) - 0.1;
    if (x < 0.0) {
      e_x = -1.0;
    } else if (x > 0.0) {
      e_x = 1.0;
    } else if (x == 0.0) {
      e_x = 0.0;
    } else {
      e_x = x;
    }

    yD[k + 1] = e_x + 1.0;
  }

  yD[4] = 0.0;

  // Indices of maxima and corresponding values of y
  k = 0;
  for (i = 0; i < 5; i++) {
    if (yD[i] != 0.0) {
      k++;
    }
  }

  locs_size[0] = 1;
  locs_size[1] = k;
  partialTrueCount = 0;
  k = 0;
  for (i = 0; i < 5; i++) {
    if (yD[i] != 0.0) {
      locs_data[partialTrueCount] = 1.0 + (double)i;
      partialTrueCount++;
    }

    if (yD[i] != 0.0) {
      k++;
    }
  }

  pks_size[0] = 1;
  pks_size[1] = k;
  partialTrueCount = 0;
  for (i = 0; i < 5; i++) {
    if (yD[i] != 0.0) {
      pks_data[partialTrueCount] = y[i];
      partialTrueCount++;
    }
  }
}

//
// ,methods,flagPlot)
// freqDomainHRV - calculates freq domain HRV using FFT, AR, and Lomb-Scargle
// methods
//
// Inputs:    ibi = 2Dim array of time (s) and inter-beat interval (s)
//            AR_order = order of AR model
//            window = # of samples in window
//            noverlap = # of samples to overlap
//            fs = cubic spline interpolation rate / resample rate (Hz)
//            nfft = # of points in the frequency axis
//            methods = cell array of strings that defines the methods used to
//                calculate freqDomain. The default is all to use
//                all three methods.
//                methods={'welch','ar','lomb'}
//            flagPlot = flag to tell function to plot PSD. 1=plot,
//            0=don't plot, default is 0.
// Outputs:   output is a structure containg all HRV. One field for each
//            PSD method.
//            Output units include:
//                peakHF,LF,VLF (Hz)
//                aHF,aLF,aVLF (ms^2)
//                pHF,pLF,pVLF (%)
//                nHF,nLF,nVLF (%)
//                PSD (ms^2/Hz)
//                F (Hz)
// Usage:  (1) To compute freq. domain HRV on a ibi data set named dIBI
//         using VLF=[0.0-0.16], LF =[0.16-0.6], HF=[0.6 3],
//         AR model order = 16, welch window width = 256,
//         # of overlap pnts in welch window (50%) = 128, # of pnts in fft = 512,
//         IBI resample rate = 10Hz
//
//         Use: output = freqDomainHRV(sampledata,[0 .16],[.16 .6],[.6 3], ...
//                        16, 256, 128, 512, 10);
//
//         (2) To do the above and also plot all three power
//         spectrum densities (PSD)
//
//         Use: output = freqDomainHRV(sampledata,[0 .16],[.16 .6],[.6 3], ...
//                        16,256,128,512,10,{'welch','ar','lomb'},1);
//             function output = freqDomainHRV(ibi,VLF,LF,HF,AR_order,window, ...
//     noverlap,nfft,fs) %,methods,flagPlot)
// Arguments    : const emxArray_real_T *ibi
//                struct0_T *output
// Return Type  : void
//
void freqDomainHRV(const emxArray_real_T *ibi, structFreq_T *output)
{
  emxArray_real_T *t;
  int ib;
  int ic;
  emxArray_real_T *y;
  emxArray_real_T *a;
  int ar;
  unsigned int y_idx_0;
  int ia;
  emxArray_real_T *twt;
  emxArray_real_T *wtmt;
  int m;
  int br;
  double B;
  emxArray_real_T *z;
  double psdTmp[512];
  emxArray_real_T *r0;
  emxArray_real_T *r1;
  emxArray_real_T *b_z;
  emxArray_real_T *c_z;
  emxArray_real_T *d_z;
  double w;
  double b_a;
  double x;
  double tau;
  double b_B;
  emxInit_real_T(&t, 1);

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
  // check input
  //      if nargin<9
  //          error('Not enough input arguments!')
  //      elseif nargin<10
  //          methods={'welch','ar','lomb'};
  //          flagPlot=false;
  //      elseif nargin<11
  //      end
  ib = ibi->size[0];
  ic = t->size[0];
  t->size[0] = ib;
  emxEnsureCapacity((emxArray__common *)t, ic, (int)sizeof(double));
  for (ic = 0; ic < ib; ic++) {
    t->data[ic] = ibi->data[ic];
  }

  emxInit_real_T(&y, 1);

  // time (s)
  // ibi (s)
  // convert ibi to ms
  // assumes ibi units are seconds
  // prepare y
  ib = ibi->size[0];
  ic = y->size[0];
  y->size[0] = ib;
  emxEnsureCapacity((emxArray__common *)y, ic, (int)sizeof(double));
  for (ic = 0; ic < ib; ic++) {
    y->data[ic] = ibi->data[ic + ibi->size[0]] * 1000.0;
  }

  emxInit_real_T1(&a, 2);
  ar = y->size[0];
  y_idx_0 = (unsigned int)y->size[0];
  ic = a->size[0] * a->size[1];
  a->size[0] = (int)y_idx_0;
  a->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)a, ic, (int)sizeof(double));
  for (ia = 1; ia <= ar; ia++) {
    a->data[ia - 1] = (double)ia / (double)ar;
    a->data[(ia + a->size[0]) - 1] = 1.0;
  }

  emxInit_real_T(&twt, 1);
  mldivide(a, y, twt);
  emxInit_real_T(&wtmt, 1);
  if (twt->size[0] == 1) {
    ic = wtmt->size[0];
    wtmt->size[0] = a->size[0];
    emxEnsureCapacity((emxArray__common *)wtmt, ic, (int)sizeof(double));
    ib = a->size[0];
    for (ic = 0; ic < ib; ic++) {
      wtmt->data[ic] = 0.0;
      for (ar = 0; ar < 2; ar++) {
        wtmt->data[ic] += a->data[ic + a->size[0] * ar] * twt->data[ar];
      }
    }
  } else {
    y_idx_0 = (unsigned int)a->size[0];
    ic = wtmt->size[0];
    wtmt->size[0] = (int)y_idx_0;
    emxEnsureCapacity((emxArray__common *)wtmt, ic, (int)sizeof(double));
    m = a->size[0];
    ar = wtmt->size[0];
    ic = wtmt->size[0];
    wtmt->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)wtmt, ic, (int)sizeof(double));
    for (ic = 0; ic < ar; ic++) {
      wtmt->data[ic] = 0.0;
    }

    if (a->size[0] == 0) {
    } else {
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          wtmt->data[ic - 1] = 0.0;
        }

        ar = m;
      }

      br = 0;
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        ar = 0;
        for (ib = br; ib + 1 <= br + 2; ib++) {
          if (twt->data[ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              wtmt->data[ic] += twt->data[ib] * a->data[ia - 1];
            }
          }

          ar += m;
        }

        br += 2;
        ar = m;
      }
    }
  }

  emxFree_real_T(&a);
  ic = y->size[0];
  emxEnsureCapacity((emxArray__common *)y, ic, (int)sizeof(double));
  ib = y->size[0];
  for (ic = 0; ic < ib; ic++) {
    y->data[ic] -= wtmt->data[ic];
  }

  B = mean(y);
  ic = y->size[0];
  emxEnsureCapacity((emxArray__common *)y, ic, (int)sizeof(double));
  ib = y->size[0];
  for (ic = 0; ic < ib; ic++) {
    y->data[ic] -= B;
  }

  emxInit_real_T(&z, 1);

  // Welch FFT
  emptyData(&output->welch.hrv.aVLF, &output->welch.hrv.aLF,
            &output->welch.hrv.aHF, &output->welch.hrv.aTotal,
            &output->welch.hrv.pVLF, &output->welch.hrv.pLF,
            &output->welch.hrv.pHF, &output->welch.hrv.nLF,
            &output->welch.hrv.nHF, &output->welch.hrv.LFHF,
            &output->welch.hrv.peakVLF, &output->welch.hrv.peakLF,
            &output->welch.hrv.peakHF, output->welch.f, output->welch.psd);

  // AR
  emptyData(&output->ar.hrv.aVLF, &output->ar.hrv.aLF, &output->ar.hrv.aHF,
            &output->ar.hrv.aTotal, &output->ar.hrv.pVLF, &output->ar.hrv.pLF,
            &output->ar.hrv.pHF, &output->ar.hrv.nLF, &output->ar.hrv.nHF,
            &output->ar.hrv.LFHF, &output->ar.hrv.peakVLF,
            &output->ar.hrv.peakLF, &output->ar.hrv.peakHF, output->ar.f,
            output->ar.psd);

  // Lomb
  // calLomb - Calculates the PSD using Lomb-Scargle method.
  //
  // Inputs:
  // Outputs:
  //  function [PSD,F]=calcWelch(t,y,window,noverlap,nfft,fs)
  //  %calFFT - Calculates the PSD using Welch method.
  //  %
  //  %Inputs:
  //  %Outputs:
  //
  //      %Prepare y
  //      t2 = t(1):1/fs:t(length(t));%time values for interp.
  //      y=interp1(t,y,t2','spline')'; %cubic spline interpolation
  //      y=y-mean(y); %remove mean
  //
  //      %Calculate Welch PSD using hamming windowing
  //      [PSD,F] = pwelch(y,window,noverlap,(nfft*2)-1,fs,'onesided');
  //
  //  end
  //
  //  function [PSD,F]=calcAR(t,y,fs,nfft,AR_order)
  //  %calAR - Calculates the PSD using Auto Regression model.
  //  %
  //  %Inputs:
  //  %Outputs:
  //
  //      %Prepare y
  //      t2 = t(1):1/fs:t(length(t)); %time values for interp.
  //      y=interp1(t, y, t2)';
  //      %%y=interp1(t, y, t2,'spline')'; %cubic spline interpolation
  //      y=y-mean(y); %remove mean
  //      y = y.*hamming(length(y)); %hamming window
  //
  //      %Calculate PSD
  //      %Method 1
  //  %     [A, variance] = arburg(y,AR_order); %AR using Burg method
  //  %     [H,F] = freqz(1,A,nfft,fs);
  //  %     PSD=(abs(H).^2).*(variance/fs); %malik, p.67
  //      %Method 2
  //      [PSD,F]=pburg(y,AR_order,(nfft*2)-1,fs,'onesided');
  //      %Method 3
  //  %      h=spectrum.burg;
  //  %      hpsd = psd(h, y, 'NFFT', nfft, 'Fs', 2);
  //  %      F=hpsd.Frequencies;
  //  %      PSD=hpsd.Data;
  //
  //  end
  //
  // Calculate PSD
  //
  //   [Pn] = lomb(t, y, f)
  //
  //   Uses Lomb's method to compute normalized
  //   periodogram values "Pn" as a function of
  //   supplied vector of frequencies "f" for
  //   input vectors "t" (time) and "y" (observations).
  //   Also returned is probability "Prob" of same
  //   length as Pn (and f) that the null hypothesis
  //   is valid. If f is not supplied it assumes
  //   f =  [1/1024 : 1/1024 : 0.5/min(diff(t))];		
  //   x and y must be the same length.
  //  See also:
  //
  //  [1] N.R. Lomb, ``Least-squares frequency analysis of
  //  unequally spaced data,'' Astrophysical and Space Science,
  //  (39) pp. 447--462, 1976.   ... and
  //
  //  [2] J.~D. Scargle, ``Studies in astronomical time series analysis.
  //  II. Statistical aspects of spectral analysis of unevenly spaced data,''
  //  Astrophysical Journal, vol. 263, pp. 835--853, 1982.
  //
  //  [3] T. Thong, "Lomb-Welch Periodogram for Non-uniform Sampling",
  //  Proceedings for the 26th anual international conference of the IEEE EMBS,
  //  Sept 1-5, 2004.
  //  check inputs
  //  subtract mean, compute variance, initialize Pn
  B = mean(y);
  ic = z->size[0];
  z->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)z, ic, (int)sizeof(double));
  ib = y->size[0];
  for (ic = 0; ic < ib; ic++) {
    z->data[ic] = y->data[ic] - B;
  }

  memset(&psdTmp[0], 0, sizeof(double) << 9);
  emxInit_real_T(&r0, 1);

  // 	now do main loop for all frequencies
  emxInit_real_T(&r1, 1);
  emxInit_real_T(&b_z, 1);
  emxInit_real_T(&c_z, 1);
  emxInit_real_T(&d_z, 1);
  for (ia = 0; ia < 512; ia++) {
    w = 6.2831853071795862 * (0.009765625 * (double)ia);
    if (w > 0.0) {
      b_a = 2.0 * w;
      ic = twt->size[0];
      twt->size[0] = t->size[0];
      emxEnsureCapacity((emxArray__common *)twt, ic, (int)sizeof(double));
      ib = t->size[0];
      for (ic = 0; ic < ib; ic++) {
        twt->data[ic] = b_a * t->data[ic];
      }

      ic = r0->size[0];
      r0->size[0] = twt->size[0];
      emxEnsureCapacity((emxArray__common *)r0, ic, (int)sizeof(double));
      ib = twt->size[0];
      for (ic = 0; ic < ib; ic++) {
        r0->data[ic] = twt->data[ic];
      }

      b_sin(r0);
      B = sum(r0);
      b_cos(twt);
      x = sum(twt);
      tau = rt_atan2d_snf(B, x) / 2.0 / w;
      ic = wtmt->size[0];
      wtmt->size[0] = t->size[0];
      emxEnsureCapacity((emxArray__common *)wtmt, ic, (int)sizeof(double));
      ib = t->size[0];
      for (ic = 0; ic < ib; ic++) {
        wtmt->data[ic] = w * (t->data[ic] - tau);
      }

      ic = r0->size[0];
      r0->size[0] = wtmt->size[0];
      emxEnsureCapacity((emxArray__common *)r0, ic, (int)sizeof(double));
      ib = wtmt->size[0];
      for (ic = 0; ic < ib; ic++) {
        r0->data[ic] = wtmt->data[ic];
      }

      b_cos(r0);
      ic = twt->size[0];
      twt->size[0] = wtmt->size[0];
      emxEnsureCapacity((emxArray__common *)twt, ic, (int)sizeof(double));
      ib = wtmt->size[0];
      for (ic = 0; ic < ib; ic++) {
        twt->data[ic] = wtmt->data[ic];
      }

      b_sin(twt);
      ic = d_z->size[0];
      d_z->size[0] = z->size[0];
      emxEnsureCapacity((emxArray__common *)d_z, ic, (int)sizeof(double));
      ib = z->size[0];
      for (ic = 0; ic < ib; ic++) {
        d_z->data[ic] = z->data[ic] * r0->data[ic];
      }

      b_a = sum(d_z);
      ic = r0->size[0];
      r0->size[0] = wtmt->size[0];
      emxEnsureCapacity((emxArray__common *)r0, ic, (int)sizeof(double));
      ib = wtmt->size[0];
      for (ic = 0; ic < ib; ic++) {
        r0->data[ic] = wtmt->data[ic];
      }

      b_cos(r0);
      power(r0, r1);
      B = sum(r1);
      ic = c_z->size[0];
      c_z->size[0] = z->size[0];
      emxEnsureCapacity((emxArray__common *)c_z, ic, (int)sizeof(double));
      ib = z->size[0];
      for (ic = 0; ic < ib; ic++) {
        c_z->data[ic] = z->data[ic] * twt->data[ic];
      }

      x = sum(c_z);
      b_sin(wtmt);
      power(wtmt, r0);
      b_B = sum(r0);
      psdTmp[ia] = b_a * b_a / B + x * x / b_B;
    } else {
      ic = b_z->size[0];
      b_z->size[0] = z->size[0];
      emxEnsureCapacity((emxArray__common *)b_z, ic, (int)sizeof(double));
      ib = z->size[0];
      for (ic = 0; ic < ib; ic++) {
        b_z->data[ic] = z->data[ic] * t->data[ic];
      }

      b_a = sum(b_z);
      power(t, r0);
      B = sum(r0);
      psdTmp[ia] = b_a * b_a / B;
    }
  }

  emxFree_real_T(&d_z);
  emxFree_real_T(&c_z);
  emxFree_real_T(&b_z);
  emxFree_real_T(&r1);
  emxFree_real_T(&r0);
  emxFree_real_T(&wtmt);
  emxFree_real_T(&twt);
  emxFree_real_T(&z);
  emxFree_real_T(&t);

  //  return denormalized spectrum (see T. Thong)
  ar = y->size[0];
  emxFree_real_T(&y);
  for (ic = 0; ic < 512; ic++) {
    psdTmp[ic] /= (double)ar;
  }

  // calc lomb psd
  calcAreas(psdTmp, &output->lomb.hrv.aVLF, &output->lomb.hrv.aLF,
            &output->lomb.hrv.aHF, &output->lomb.hrv.aTotal,
            &output->lomb.hrv.pVLF, &output->lomb.hrv.pLF, &output->lomb.hrv.pHF,
            &output->lomb.hrv.nLF, &output->lomb.hrv.nHF, &output->lomb.hrv.LFHF,
            &output->lomb.hrv.peakVLF, &output->lomb.hrv.peakLF,
            &output->lomb.hrv.peakHF, output->lomb.psd, output->lomb.f);

  // plot all three psd  NOT USED in C++
  //      if flagPlot figure; h1=subplot(3,1,1);
  //      plotPSD(h1,output.welch.f,output.welch.psd,VLF,LF,HF,[0 0.6],[]);
  //      legend('welch') h2=subplot(3,1,2);
  //      plotPSD(h2,output.ar.f,output.ar.psd,VLF,LF,HF,[0 0.6],[]);
  //      legend('AR') h3=subplot(3,1,3);
  //      plotPSD(h3,output.lomb.f,output.lomb.psd,VLF,LF,HF,[0 0.6],[]);
  //      legend('Lomb-Scargle') end
}

//
// File trailer for freqDomainHRV.cpp
//
// [EOF]
//
