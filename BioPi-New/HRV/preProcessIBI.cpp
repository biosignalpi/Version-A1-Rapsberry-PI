//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: preProcessIBI.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 04-Jan-2016 12:02:09
//

// Include Files
#include "rt_nonfinite.h"
#include "preProcessIBI.h"
#include "timeDomainHRV_emxutil.h"
#include "abs.h"
#include "repmat.h"
#include "mldivide.h"

// Custom Source Code
/** Created in Matlab Coder by Martin, files generated from preProcessIBI */

// Function Declarations 
static void eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T *idx);
static void sdFilter(emxArray_real_T *s, emxArray_boolean_T *outliers);

// Function Definitions 

// 
// Arguments    : emxArray_real_T *x 
//                const emxArray_boolean_T *idx 
// Return Type  : void 
//
static void eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T *idx)
{
    int nrowx;
    int i;
    int k;
    int nrows;
    emxArray_real_T *b_x;
    nrowx = x->size[0];
    i = 0;
    for (k = 1; k <= idx->size[0]; k++) {
        i += idx->data[k - 1];
    }
    nrows = x->size[0] - i;
    i = 0;
    for (k = 1; k <= nrowx; k++) {
        if ((k > idx->size[0]) || (!idx->data[k - 1])) {
            x->data[i] = x->data[k - 1];
            i++;
        }
    }
    if (1 > nrows) {
        i = 0;
    } else {
        i = nrows;
    }
    emxInit_real_T(&b_x, 1);
    nrows = b_x->size[0];
    b_x->size[0] = i;
    emxEnsureCapacity((emxArray__common *)b_x, nrows, (int)sizeof(double));
    for (nrows = 0; nrows < i; nrows++) {
        b_x->data[nrows] = x->data[nrows];
    }
    nrows = x->size[0];
    x->size[0] = b_x->size[0];
    emxEnsureCapacity((emxArray__common *)x, nrows, (int)sizeof(double));
    i = b_x->size[0];
    for (nrows = 0; nrows < i; nrows++) {
        x->data[nrows] = b_x->data[nrows];
    }
    emxFree_real_T(&b_x);
}

// 
// sdFilter: Locate outliers based on standard deviation 
// Arguments    : emxArray_real_T *s 
//                emxArray_boolean_T *outliers 
// Return Type  : void 
//
static void sdFilter(emxArray_real_T *s, emxArray_boolean_T *outliers)
{
    emxArray_real_T *a;
    int n;
    unsigned int s_idx_0;
    int ia;
    int ar;
    emxArray_real_T *MeanMat;
    emxArray_real_T *C;
    int m;
    int ix;
    int br;
    double y;
    double b_y;
    double xbar;
    double r;
    emxArray_real_T *SigmaMat;
    emxArray_real_T *b_s;
    emxInit_real_T1(&a, 2);
    n = s->size[0];
    s_idx_0 = (unsigned int)s->size[0];
    ia = a->size[0] * a->size[1];
    a->size[0] = (int)s_idx_0;
    a->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)a, ia, (int)sizeof(double));
    for (ar = 1; ar <= n; ar++) {
        a->data[ar - 1] = (double)ar / (double)n;
        a->data[(ar + a->size[0]) - 1] = 1.0;
    }
    emxInit_real_T(&MeanMat, 1);
    mldivide(a, s, MeanMat);
    emxInit_real_T(&C, 1);
    if (MeanMat->size[0] == 1) {
        ia = C->size[0];
        C->size[0] = a->size[0];
        emxEnsureCapacity((emxArray__common *)C, ia, (int)sizeof(double));
        ar = a->size[0];
        for (ia = 0; ia < ar; ia++) {
            C->data[ia] = 0.0;
            for (n = 0; n < 2; n++) {
                C->data[ia] += a->data[ia + a->size[0] * n] * MeanMat->data[n];
            }
        }
    } else {
        s_idx_0 = (unsigned int)a->size[0];
        ia = C->size[0];
        C->size[0] = (int)s_idx_0;
        emxEnsureCapacity((emxArray__common *)C, ia, (int)sizeof(double));
        m = a->size[0];
        ar = C->size[0];
        ia = C->size[0];
        C->size[0] = ar;
        emxEnsureCapacity((emxArray__common *)C, ia, (int)sizeof(double));
        for (ia = 0; ia < ar; ia++) {
            C->data[ia] = 0.0;
        }
        if (a->size[0] == 0) {
        } else {
            ar = 0;
            while ((m > 0) && (ar <= 0)) {
                for (ix = 1; ix <= m; ix++) {
                    C->data[ix - 1] = 0.0;
                }
                ar = m;
            }
            br = 0;
            ar = 0;
            while ((m > 0) && (ar <= 0)) {
                ar = 0;
                for (n = br; n + 1 <= br + 2; n++) {
                    if (MeanMat->data[n] != 0.0) {
                        ia = ar;
                        for (ix = 0; ix + 1 <= m; ix++) {
                            ia++;
                            C->data[ix] += MeanMat->data[n] * a->data[ia - 1];
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
    ia = s->size[0];
    emxEnsureCapacity((emxArray__common *)s, ia, (int)sizeof(double));
    ar = s->size[0];
    for (ia = 0; ia < ar; ia++) {
        s->data[ia] -= C->data[ia];
    }
    if (s->size[0] == 0) {
        y = 0.0;
    } else {
        y = s->data[0];
        for (ar = 2; ar <= s->size[0]; ar++) {
            y += s->data[ar - 1];
        }
    }
    /* mean */
    n = s->size[0];
    if (s->size[0] > 1) {
        ia = s->size[0] - 1;
    } else {
        ia = s->size[0];
    }
    if (s->size[0] == 0) {
        b_y = 0.0;
    } else {
        ix = 0;
        xbar = s->data[0];
        for (ar = 2; ar <= n; ar++) {
            ix++;
            xbar += s->data[ix];
        }
        xbar /= (double)s->size[0];
        ix = 0;
        r = s->data[0] - xbar;
        b_y = r * r;
        for (ar = 2; ar <= n; ar++) {
            ix++;
            r = s->data[ix] - xbar;
            b_y += r * r;
        }
        b_y /= (double)ia;
    }
    emxInit_real_T(&SigmaMat, 1);
    emxInit_real_T(&b_s, 1);
    /* standard deviation */
    /*  Create a matrix of mean values by replicating the mu vector  */
    /*  for n rows */
    repmat(y / (double)s->size[0], (double)s->size[0], MeanMat);
    /*  Create a matrix of standard deviation values by replicating  */
    /*  the sigma vector for n rows */
    repmat(std::sqrt(b_y), (double)s->size[0], SigmaMat);
    /*  Create a matrix of zeros and ones, where ones indicate the  */
    /*  location of outliers */
    ia = b_s->size[0];
    b_s->size[0] = s->size[0];
    emxEnsureCapacity((emxArray__common *)b_s, ia, (int)sizeof(double));
    ar = s->size[0];
    for (ia = 0; ia < ar; ia++) {
        b_s->data[ia] = s->data[ia] - MeanMat->data[ia];
    }
    emxFree_real_T(&MeanMat);
    b_abs(b_s, C);
    ia = outliers->size[0];
    outliers->size[0] = C->size[0];
    emxEnsureCapacity((emxArray__common *)outliers, ia, (int)sizeof(boolean_T));
    ar = C->size[0];
    emxFree_real_T(&b_s);
    for (ia = 0; ia < ar; ia++) {
        outliers->data[ia] = (C->data[ia] > 3.0 * SigmaMat->data[ia]);
    }
    emxFree_real_T(&C);
    emxFree_real_T(&SigmaMat);
    /*  Reference:  */
    /*  Aubert, A. E., D. Ramaekers, et al. (1999). "The analysis of heart  */
    /*  rate variability in unrestrained rats. Validation of method and  */
    /*  results." Comput Methods Programs Biomed 60(3): 197-213. */
}

// 
// preProcessIBI: detects ectopic IBI, corrects ectopic IBI, and then  
//  detrends IBI 
//  
//  TODO: build function description and usage 
// Arguments    : const emxArray_real_T *ibi 
//                emxArray_real_T *nibi 
//                emxArray_boolean_T *art 
// Return Type  : void 
//
void preProcessIBI(const emxArray_real_T *ibi, emxArray_real_T *nibi, emxArray_boolean_T *art)
{
    emxArray_real_T *y;
    int loop_ub;
    int i0;
    int ixLead;
    int iyLead;
    emxArray_real_T *b_y1;
    int i1;
    double work_data_idx_0;
    int m;
    double tmp1;
    double tmp2;
    emxArray_real_T *x;
    emxArray_int32_T *r0;
    emxArray_int32_T *r1;
    emxArray_real_T *b_y;
    emxArray_boolean_T *artSD;
    emxInit_real_T(&y, 1);
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Copyright (C) 2010, John T. Ramshur, jramshur@gmail.com */
    /*   */
    /*  This file is part of HRVAS */
    /*  */
    /*  HRVAS is free software: you can redistribute it and/or modify */
    /*  it under the terms of the GNU General Public License as published by */
    /*  the Free Software Foundation, either version 3 of the License, or */
    /*  (at your option) any later version. */
    /*   */
    /*  HRVAS is distributed in the hope that it will be useful, */
    /*  but WITHOUT ANY WARRANTY; without even the implied warranty of */
    /*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
    /*  GNU General Public License for more details. */
    /*   */
    /*  You should have received a copy of the GNU General Public License */
    /*  along with HRVAS.  If not, see <http://www.gnu.org/licenses/>. */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*     %% correct ectopic ibi */
    loop_ub = ibi->size[0];
    i0 = y->size[0];
    y->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(double));
    for (i0 = 0; i0 < loop_ub; i0++) {
        y->data[i0] = ibi->data[i0 + ibi->size[0]];
    }
    /* locate ectopic */
    /*    %%     artPer=locateOutliers(t,y,'percent',0.2); */
    ixLead = ibi->size[0];
    i0 = art->size[0];
    art->size[0] = ixLead;
    emxEnsureCapacity((emxArray__common *)art, i0, (int)sizeof(boolean_T));
    for (i0 = 0; i0 < ixLead; i0++) {
        art->data[i0] = false;
    }
    /* preallocate         */
    i0 = ibi->size[0];
    if (1 > i0 - 1) {
        loop_ub = 0;
    } else {
        loop_ub = ibi->size[0] - 1;
    }
    i0 = ibi->size[0];
    iyLead = ibi->size[0];
    emxInit_real_T(&b_y1, 1);
    if (iyLead == 0) {
        i0 = b_y1->size[0];
        b_y1->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)b_y1, i0, (int)sizeof(double));
    } else {
        if (i0 - 1 <= 1) {
            i1 = i0 - 1;
        } else {
            i1 = 1;
        }
        if (i1 < 1) {
            i0 = b_y1->size[0];
            b_y1->size[0] = 0;
            emxEnsureCapacity((emxArray__common *)b_y1, i0, (int)sizeof(double));
        } else {
            iyLead = b_y1->size[0];
            b_y1->size[0] = i0 - 1;
            emxEnsureCapacity((emxArray__common *)b_y1, iyLead, (int)sizeof(double));
            if (!(b_y1->size[0] == 0)) {
                ixLead = 1;
                iyLead = 0;
                work_data_idx_0 = ibi->data[ibi->size[0]];
                for (m = 2; m <= i0; m++) {
                    tmp1 = ibi->data[ixLead + ibi->size[0]];
                    tmp2 = work_data_idx_0;
                    work_data_idx_0 = tmp1;
                    tmp1 -= tmp2;
                    ixLead++;
                    b_y1->data[iyLead] = tmp1;
                    iyLead++;
                }
            }
        }
    }
    emxInit_real_T(&x, 1);
    b_abs(b_y1, x);
    /* percent chage from previous */
    /* find index of values where pChange > perLimit */
    i0 = ibi->size[0];
    if (2 > i0) {
        i0 = 0;
        iyLead = 0;
    } else {
        i0 = 1;
        iyLead = ibi->size[0];
    }
    emxInit_int32_T(&r0, 2);
    ixLead = r0->size[0] * r0->size[1];
    r0->size[0] = 1;
    r0->size[1] = iyLead - i0;
    emxEnsureCapacity((emxArray__common *)r0, ixLead, (int)sizeof(int));
    ixLead = iyLead - i0;
    for (iyLead = 0; iyLead < ixLead; iyLead++) {
        r0->data[r0->size[0] * iyLead] = i0 + iyLead;
    }
    emxInit_int32_T1(&r1, 1);
    i0 = r1->size[0];
    r1->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)r1, i0, (int)sizeof(int));
    for (i0 = 0; i0 < loop_ub; i0++) {
        r1->data[i0] = 1 + i0;
    }
    loop_ub = r0->size[0] * r0->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
        art->data[r0->data[i0]] = (x->data[i0] / y->data[r1->data[i0] - 1] > 0.2);
    }
    emxFree_int32_T(&r1);
    emxFree_real_T(&x);
    emxFree_int32_T(&r0);
    emxInit_real_T(&b_y, 1);
    /*  Reference:  */
    /*  Clifford, G. (2002). "Characterizing Artefact in the Normal  */
    /*  Human 24-Hour RR Time Series to Aid Identification and Artificial  */
    /*  Replication of Circadian Variations in Human Beat to Beat Heart */
    /*  Rate using a Simple Threshold." */
    /*  */
    /*  Aubert, A. E., D. Ramaekers, et al. (1999). "The analysis of heart  */
    /*  rate variability in unrestrained rats. Validation of method and  */
    /*  results." Comput Methods Programs Biomed 60(3): 197-213. */
    /* convert to logical array */
    /*    %%     artSD=locateOutliers(t,y,'sd',3); */
    i0 = b_y->size[0];
    b_y->size[0] = y->size[0];
    emxEnsureCapacity((emxArray__common *)b_y, i0, (int)sizeof(double));
    loop_ub = y->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
        b_y->data[i0] = y->data[i0];
    }
    emxInit_boolean_T(&artSD, 1);
    sdFilter(b_y, artSD);
    i0 = art->size[0];
    emxEnsureCapacity((emxArray__common *)art, i0, (int)sizeof(boolean_T));
    loop_ub = art->size[0];
    emxFree_real_T(&b_y);
    for (i0 = 0; i0 < loop_ub; i0++) {
        art->data[i0] = (art->data[i0] || artSD->data[i0]);
    }
    emxFree_boolean_T(&artSD);
    /* combine all logical arrays     */
    /* replace ectopic */
    /* replaceOutliers: replaces artifacts/outliers from data series */
    /*  */
    /* Inputs:    t = time */
    /*            y = ibi values */
    /*            outliers = logical array of outliers. 0=normal, 1=outlier */
    /*            method = artifact replacement method to use. */
    /*    methods:    'remove' = Outliers are removed */
    /*                'mean' = Outliers are replaced with mean value from  */
    /*                         nearest +- m ibi values. */
    /*                'spline' = Outliers are replaced by cubic spline */
    /*                           interpolation */
    /*                'median' = Outliers are replaced with median value from */
    /*                           nearest +- m ibi values. */
    /* Outputs:   t2, y2 = arrays with replaced artifacts */
    /* Examples:  */
    /*    remove outliers from ibi series */
    /*        [t2 y2] = replaceOutlers(t,y, outlierArray,'remove') */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Copyright (C) 2010, John T. Ramshur, jramshur@gmail.com */
    /*   */
    /*  This file is part of HRVAS */
    /*  */
    /*  HRVAS is free software: you can redistribute it and/or modify */
    /*  it under the terms of the GNU General Public License as published by */
    /*  the Free Software Foundation, either version 3 of the License, or */
    /*  (at your option) any later version. */
    /*   */
    /*  HRVAS is distributed in the hope that it will be useful, */
    /*  but WITHOUT ANY WARRANTY; without even the implied warranty of */
    /*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
    /*  GNU General Public License for more details. */
    /*   */
    /*  You should have received a copy of the GNU General Public License */
    /*  along with HRVAS.  If not, see <http://www.gnu.org/licenses/>. */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* remove outliers */
    eml_null_assignment(y, art);
    loop_ub = ibi->size[0];
    i0 = b_y1->size[0];
    b_y1->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)b_y1, i0, (int)sizeof(double));
    for (i0 = 0; i0 < loop_ub; i0++) {
        b_y1->data[i0] = ibi->data[i0];
    }
    eml_null_assignment(b_y1, art);
    ixLead = b_y1->size[0];
    iyLead = y->size[0];
    i0 = nibi->size[0] * nibi->size[1];
    nibi->size[0] = ixLead;
    nibi->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)nibi, i0, (int)sizeof(double));
    for (i0 = 0; i0 < ixLead; i0++) {
        nibi->data[i0] = b_y1->data[i0];
    }
    emxFree_real_T(&b_y1);
    for (i0 = 0; i0 < iyLead; i0++) {
        nibi->data[i0 + nibi->size[0]] = y->data[i0];
    }
    emxFree_real_T(&y);
}
// 
// File trailer for preProcessIBI.cpp 
//  
// [EOF] 
//
