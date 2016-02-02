//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: preProcessIBI_emxAPI.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 28-Dec-2015 15:01:17
//

// Include Files
#include "rt_nonfinite.h"
#include "preProcessIBI.h"
#include "preProcessIBI_emxAPI.h"
#include "preProcessIBI_emxutil.h"

// Custom Source Code
/** Created in Matlab Coder by Martin, files generated from preProcessIBI */

// Function Definitions 

// 
// Arguments    : int numDimensions 
//                int *size 
// Return Type  : emxArray_boolean_T * 
//
emxArray_boolean_T *emxCreateND_boolean_T(int numDimensions, int *size)
{
    emxArray_boolean_T *emx;
    int numEl;
    int i;
    emxInit_boolean_T(&emx, numDimensions);
    numEl = 1;
    for (i = 0; i < numDimensions; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }
    emx->data = (boolean_T *)calloc((unsigned int)numEl, sizeof(boolean_T));
    emx->numDimensions = numDimensions;
    emx->allocatedSize = numEl;
    return emx;
}

// 
// Arguments    : int numDimensions 
//                int *size 
// Return Type  : emxArray_real_T * 
//
emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size)
{
    emxArray_real_T *emx;
    int numEl;
    int i;
    emxInit_real_T1(&emx, numDimensions);
    numEl = 1;
    for (i = 0; i < numDimensions; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }
    emx->data = (double *)calloc((unsigned int)numEl, sizeof(double));
    emx->numDimensions = numDimensions;
    emx->allocatedSize = numEl;
    return emx;
}

// 
// Arguments    : boolean_T *data 
//                int numDimensions 
//                int *size 
// Return Type  : emxArray_boolean_T * 
//
emxArray_boolean_T *emxCreateWrapperND_boolean_T(boolean_T *data, int numDimensions, int *size)
{
    emxArray_boolean_T *emx;
    int numEl;
    int i;
    emxInit_boolean_T(&emx, numDimensions);
    numEl = 1;
    for (i = 0; i < numDimensions; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }
    emx->data = data;
    emx->numDimensions = numDimensions;
    emx->allocatedSize = numEl;
    emx->canFreeData = false;
    return emx;
}

// 
// Arguments    : double *data 
//                int numDimensions 
//                int *size 
// Return Type  : emxArray_real_T * 
//
emxArray_real_T *emxCreateWrapperND_real_T(double *data, int numDimensions, int *size)
{
    emxArray_real_T *emx;
    int numEl;
    int i;
    emxInit_real_T1(&emx, numDimensions);
    numEl = 1;
    for (i = 0; i < numDimensions; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }
    emx->data = data;
    emx->numDimensions = numDimensions;
    emx->allocatedSize = numEl;
    emx->canFreeData = false;
    return emx;
}

// 
// Arguments    : boolean_T *data 
//                int rows 
//                int cols 
// Return Type  : emxArray_boolean_T * 
//
emxArray_boolean_T *emxCreateWrapper_boolean_T(boolean_T *data, int rows, int cols)
{
    emxArray_boolean_T *emx;
    int size[2];
    int numEl;
    int i;
    size[0] = rows;
    size[1] = cols;
    emxInit_boolean_T(&emx, 2);
    numEl = 1;
    for (i = 0; i < 2; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }
    emx->data = data;
    emx->numDimensions = 2;
    emx->allocatedSize = numEl;
    emx->canFreeData = false;
    return emx;
}

// 
// Arguments    : double *data 
//                int rows 
//                int cols 
// Return Type  : emxArray_real_T * 
//
emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols)
{
    emxArray_real_T *emx;
    int size[2];
    int numEl;
    int i;
    size[0] = rows;
    size[1] = cols;
    emxInit_real_T1(&emx, 2);
    numEl = 1;
    for (i = 0; i < 2; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }
    emx->data = data;
    emx->numDimensions = 2;
    emx->allocatedSize = numEl;
    emx->canFreeData = false;
    return emx;
}

// 
// Arguments    : int rows 
//                int cols 
// Return Type  : emxArray_boolean_T * 
//
emxArray_boolean_T *emxCreate_boolean_T(int rows, int cols)
{
    emxArray_boolean_T *emx;
    int size[2];
    int numEl;
    int i;
    size[0] = rows;
    size[1] = cols;
    emxInit_boolean_T(&emx, 2);
    numEl = 1;
    for (i = 0; i < 2; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }
    emx->data = (boolean_T *)calloc((unsigned int)numEl, sizeof(boolean_T));
    emx->numDimensions = 2;
    emx->allocatedSize = numEl;
    return emx;
}

// 
// Arguments    : int rows 
//                int cols 
// Return Type  : emxArray_real_T * 
//
emxArray_real_T *emxCreate_real_T(int rows, int cols)
{
    emxArray_real_T *emx;
    int size[2];
    int numEl;
    int i;
    size[0] = rows;
    size[1] = cols;
    emxInit_real_T1(&emx, 2);
    numEl = 1;
    for (i = 0; i < 2; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }
    emx->data = (double *)calloc((unsigned int)numEl, sizeof(double));
    emx->numDimensions = 2;
    emx->allocatedSize = numEl;
    return emx;
}

// 
// Arguments    : emxArray_boolean_T *emxArray 
// Return Type  : void 
//
void emxDestroyArray_boolean_T(emxArray_boolean_T *emxArray)
{
    emxFree_boolean_T(&emxArray);
}

// 
// Arguments    : emxArray_real_T *emxArray 
// Return Type  : void 
//
void emxDestroyArray_real_T(emxArray_real_T *emxArray)
{
    emxFree_real_T(&emxArray);
}

// 
// Arguments    : emxArray_boolean_T **pEmxArray 
//                int numDimensions 
// Return Type  : void 
//
void emxInitArray_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions)
{
    emxInit_boolean_T(pEmxArray, numDimensions);
}

// 
// Arguments    : emxArray_real_T **pEmxArray 
//                int numDimensions 
// Return Type  : void 
//
void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
    emxInit_real_T1(pEmxArray, numDimensions);
}
// 
// File trailer for preProcessIBI_emxAPI.cpp 
//  
// [EOF] 
//
