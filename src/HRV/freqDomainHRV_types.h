//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: freqDomainHRV_types.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 25-Nov-2015 14:25:38
//
#ifndef __FREQDOMAINHRV_TYPES_H__
#define __FREQDOMAINHRV_TYPES_H__

// Include Files
#include "rtwtypes.h"

// Type Definitions
#ifndef struct_emxArray__common
#define struct_emxArray__common

struct emxArray__common
{
  void *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray__common

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_real_T

typedef struct {
  double aVLF;
  double aLF;
  double aHF;
  double aTotal;
  double pVLF;
  double pLF;
  double pHF;
  double nLF;
  double nHF;
  double LFHF;
  double peakVLF;
  double peakLF;
  double peakHF;
} struct2_T;

typedef struct {
  struct2_T hrv;
  double f[512];
  double psd[512];
} struct1_T;

typedef struct {
  struct2_T hrv;
  double psd[512];
  double f[512];
} struct3_T;

typedef struct {
  struct1_T welch;
  struct1_T ar;
  struct3_T lomb;
} structFreq_T;

#endif

//
// File trailer for freqDomainHRV_types.h
//
// [EOF]
//
