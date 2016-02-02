//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeDomainHRV_types.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 18-Nov-2015 10:29:30
//
#ifndef __TIMEDOMAINHRV_TYPES_H__
#define __TIMEDOMAINHRV_TYPES_H__

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

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T

struct emxArray_boolean_T
{
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_boolean_T

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_int32_T

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
  double max;
  double min;
  double mean;
  double median;
  double SDNN;
  double SDANN;
  double NNx;
  double pNNx;
  double RMSSD;
  double SDNNi;
  double meanHR;
  double sdHR;
  double HRVTi;
  double TINN;
} struct0_T;

#endif

//
// File trailer for timeDomainHRV_types.h
//
// [EOF]
//
