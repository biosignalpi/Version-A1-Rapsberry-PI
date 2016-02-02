//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 28-Dec-2015 15:01:17
//

// Include Files
#include "rt_nonfinite.h"
#include "preProcessIBI.h"
#include "repmat.h"
#include "preProcessIBI_emxutil.h"

// Custom Source Code
/** Created in Matlab Coder by Martin, files generated from preProcessIBI */

// Function Definitions 

// 
// Arguments    : double a 
//                double varargin_1 
//                emxArray_real_T *b 
// Return Type  : void 
//
void repmat(double a, double varargin_1, emxArray_real_T *b)
{
    int i1;
    int loop_ub;
    i1 = b->size[0];
    b->size[0] = (int)varargin_1;
    emxEnsureCapacity((emxArray__common *)b, i1, (int)sizeof(double));
    loop_ub = (int)varargin_1;
    for (i1 = 0; i1 < loop_ub; i1++) {
        b->data[i1] = a;
    }
}
// 
// File trailer for repmat.cpp 
//  
// [EOF] 
//
