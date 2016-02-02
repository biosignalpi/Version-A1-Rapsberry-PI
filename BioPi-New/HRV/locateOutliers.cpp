//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: locateOutliers.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 28-Dec-2015 15:01:17
//

// Include Files
#include "rt_nonfinite.h"
#include "preProcessIBI.h"
#include "locateOutliers.h"
#include "preProcessIBI_emxutil.h"
#include "abs.h"
#include "repmat.h"
#include "mean.h"
#include "mldivide.h"

// Custom Source Code
/** Created in Matlab Coder by Martin, files generated from preProcessIBI */

// Function Definitions 

// 
// % Erased all parts not wanted for codegeneration /Martin %% 
// Arguments    : emxArray_real_T *s 
//                emxArray_boolean_T *outliers 
//                emxArray_boolean_T *outliers2 
// Return Type  : void 
//
void locateOutliers(emxArray_real_T *s, emxArray_boolean_T *outliers, emxArray_boolean_T *outliers2)
{
    int ia;
    int ic;
    emxArray_real_T *b_y1;
    int orderForDim;
    int iyLead;
    double work_data_idx_0;
    int m;
    double tmp1;
    double tmp2;
    emxArray_real_T *SigmaMat;
    emxArray_int32_T *r0;
    emxArray_int32_T *r1;
    emxArray_real_T *a;
    unsigned int s_idx_0;
    emxArray_real_T *C;
    int br;
    double mu;
    emxArray_real_T *b_s;
    /* locateOutliers: locates artifacts/outliers from data series */
    /*  */
    /*   Inputs:  s = array containg data series */
    /*            method = artifact removal method to use. */
    /*   methods: 'percent' = percentage filter: locates data > x percent diff than previous data point.                */
    /*            'sd' = standard deviation filter: locates data > x stdev away from mean. */
    /*            'above' = Threshold filter: locates data > threshold value */
    /*            'below' = Threshold filter: locates data < threshold value */
    /*            'median' = median filter. Outliers are located. */
    /* Outputs:   outliers = logical array of whether s is artifact/outlier or not */
    /*                        eg. - [0 0 0 1 0], 1=artifact, 0=normal */
    /*                         */
    /* Examples: */
    /*    Locate outliers with 20% percentage filter: */
    /*        outliers = locateOutlers(s,'percent',0.2) */
    /*    Locate outliers that are above a threshold of 0.5: */
    /*        outliers = locateOutlers(s,'thresh','above',0.5) */
    /*    Locate outliers with median filter: */
    /*        outliers = locateOutlers(s,'median',4,5) */
    /*  */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
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
    /*  along with Foobar.  If not, see <http://www.gnu.org/licenses/>. */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    ia = outliers->size[0];
    outliers->size[0] = s->size[0];
    emxEnsureCapacity((emxArray__common *)outliers, ia, (int)sizeof(boolean_T));
    ic = s->size[0];
    for (ia = 0; ia < ic; ia++) {
        outliers->data[ia] = false;
    }
    /* preallocate         */
    if (1 > s->size[0] - 1) {
        ic = 0;
    } else {
        ic = s->size[0] - 1;
    }
    emxInit_real_T(&b_y1, 1);
    if (s->size[0] == 0) {
        ia = b_y1->size[0];
        b_y1->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)b_y1, ia, (int)sizeof(double));
    } else {
        if (s->size[0] - 1 <= 1) {
            orderForDim = s->size[0] - 1;
        } else {
            orderForDim = 1;
        }
        if (orderForDim < 1) {
            ia = b_y1->size[0];
            b_y1->size[0] = 0;
            emxEnsureCapacity((emxArray__common *)b_y1, ia, (int)sizeof(double));
        } else {
            orderForDim = s->size[0] - 1;
            ia = b_y1->size[0];
            b_y1->size[0] = orderForDim;
            emxEnsureCapacity((emxArray__common *)b_y1, ia, (int)sizeof(double));
            if (!(b_y1->size[0] == 0)) {
                orderForDim = 1;
                iyLead = 0;
                work_data_idx_0 = s->data[0];
                for (m = 2; m <= s->size[0]; m++) {
                    tmp1 = s->data[orderForDim];
                    tmp2 = work_data_idx_0;
                    work_data_idx_0 = tmp1;
                    tmp1 -= tmp2;
                    orderForDim++;
                    b_y1->data[iyLead] = tmp1;
                    iyLead++;
                }
            }
        }
    }
    emxInit_real_T(&SigmaMat, 1);
    b_abs(b_y1, SigmaMat);
    /* percent chage from previous */
    /* find index of values where pChange > perLimit */
    orderForDim = s->size[0];
    if (2 > orderForDim) {
        ia = 0;
        orderForDim = 0;
    } else {
        ia = 1;
        orderForDim = s->size[0];
    }
    emxInit_int32_T(&r0, 2);
    iyLead = r0->size[0] * r0->size[1];
    r0->size[0] = 1;
    r0->size[1] = orderForDim - ia;
    emxEnsureCapacity((emxArray__common *)r0, iyLead, (int)sizeof(int));
    orderForDim -= ia;
    for (iyLead = 0; iyLead < orderForDim; iyLead++) {
        r0->data[r0->size[0] * iyLead] = ia + iyLead;
    }
    emxInit_int32_T1(&r1, 1);
    ia = r1->size[0];
    r1->size[0] = ic;
    emxEnsureCapacity((emxArray__common *)r1, ia, (int)sizeof(int));
    for (ia = 0; ia < ic; ia++) {
        r1->data[ia] = 1 + ia;
    }
    ic = r0->size[0] * r0->size[1];
    for (ia = 0; ia < ic; ia++) {
        outliers->data[r0->data[ia]] = (SigmaMat->data[ia] / s->data[r1->data[ia] - 1] > 0.2);
    }
    emxFree_int32_T(&r1);
    emxFree_int32_T(&r0);
    emxInit_real_T1(&a, 2);
    /*  Reference:  */
    /*  Clifford, G. (2002). "Characterizing Artefact in the Normal  */
    /*  Human 24-Hour RR Time Series to Aid Identification and Artificial  */
    /*  Replication of Circadian Variations in Human Beat to Beat Heart Rate  */
    /*  using a Simple Threshold." */
    /*  */
    /*  Aubert, A. E., D. Ramaekers, et al. (1999). "The analysis of heart  */
    /*  rate variability in unrestrained rats. Validation of method and  */
    /*  results." Comput Methods Programs Biomed 60(3): 197-213. */
    /* convert to logical array */
    /* preallocate   */
    iyLead = s->size[0];
    s_idx_0 = (unsigned int)s->size[0];
    ia = a->size[0] * a->size[1];
    a->size[0] = (int)s_idx_0;
    a->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)a, ia, (int)sizeof(double));
    for (orderForDim = 1; orderForDim <= iyLead; orderForDim++) {
        a->data[orderForDim - 1] = (double)orderForDim / (double)iyLead;
        a->data[(orderForDim + a->size[0]) - 1] = 1.0;
    }
    mldivide(a, s, b_y1);
    emxInit_real_T(&C, 1);
    if (b_y1->size[0] == 1) {
        ia = C->size[0];
        C->size[0] = a->size[0];
        emxEnsureCapacity((emxArray__common *)C, ia, (int)sizeof(double));
        ic = a->size[0];
        for (ia = 0; ia < ic; ia++) {
            C->data[ia] = 0.0;
            for (iyLead = 0; iyLead < 2; iyLead++) {
                C->data[ia] += a->data[ia + a->size[0] * iyLead] * b_y1->data[iyLead];
            }
        }
    } else {
        s_idx_0 = (unsigned int)a->size[0];
        ia = C->size[0];
        C->size[0] = (int)s_idx_0;
        emxEnsureCapacity((emxArray__common *)C, ia, (int)sizeof(double));
        m = a->size[0];
        orderForDim = C->size[0];
        ia = C->size[0];
        C->size[0] = orderForDim;
        emxEnsureCapacity((emxArray__common *)C, ia, (int)sizeof(double));
        for (ia = 0; ia < orderForDim; ia++) {
            C->data[ia] = 0.0;
        }
        if (a->size[0] == 0) {
        } else {
            orderForDim = 0;
            while ((m > 0) && (orderForDim <= 0)) {
                for (ic = 1; ic <= m; ic++) {
                    C->data[ic - 1] = 0.0;
                }
                orderForDim = m;
            }
            br = 0;
            orderForDim = 0;
            while ((m > 0) && (orderForDim <= 0)) {
                orderForDim = 0;
                for (iyLead = br; iyLead + 1 <= br + 2; iyLead++) {
                    if (b_y1->data[iyLead] != 0.0) {
                        ia = orderForDim;
                        for (ic = 0; ic + 1 <= m; ic++) {
                            ia++;
                            C->data[ic] += b_y1->data[iyLead] * a->data[ia - 1];
                        }
                    }
                    orderForDim += m;
                }
                br += 2;
                orderForDim = m;
            }
        }
    }
    emxFree_real_T(&a);
    ia = s->size[0];
    emxEnsureCapacity((emxArray__common *)s, ia, (int)sizeof(double));
    ic = s->size[0];
    for (ia = 0; ia < ic; ia++) {
        s->data[ia] -= C->data[ia];
    }
    emxFree_real_T(&C);
    mu = mean(s);
    /* mean */
    orderForDim = s->size[0];
    if (s->size[0] > 1) {
        iyLead = s->size[0] - 1;
    } else {
        iyLead = s->size[0];
    }
    if (s->size[0] == 0) {
        tmp2 = 0.0;
    } else {
        ia = 0;
        work_data_idx_0 = s->data[0];
        for (ic = 2; ic <= orderForDim; ic++) {
            ia++;
            work_data_idx_0 += s->data[ia];
        }
        work_data_idx_0 /= (double)s->size[0];
        ia = 0;
        tmp1 = s->data[0] - work_data_idx_0;
        tmp2 = tmp1 * tmp1;
        for (ic = 2; ic <= orderForDim; ic++) {
            ia++;
            tmp1 = s->data[ia] - work_data_idx_0;
            tmp2 += tmp1 * tmp1;
        }
        tmp2 /= (double)iyLead;
    }
    emxInit_real_T(&b_s, 1);
    /* standard deviation */
    /*  Create a matrix of mean values by replicating the mu vector for n rows */
    repmat(mu, (double)s->size[0], b_y1);
    /*  Create a matrix of standard deviation values by replicating the sigma vector for n rows */
    repmat(std::sqrt(tmp2), (double)s->size[0], SigmaMat);
    /*  Create a matrix of zeros and ones, where ones indicate the location of outliers */
    ia = b_s->size[0];
    b_s->size[0] = s->size[0];
    emxEnsureCapacity((emxArray__common *)b_s, ia, (int)sizeof(double));
    ic = s->size[0];
    for (ia = 0; ia < ic; ia++) {
        b_s->data[ia] = s->data[ia] - b_y1->data[ia];
    }
    b_abs(b_s, b_y1);
    ia = outliers2->size[0];
    outliers2->size[0] = b_y1->size[0];
    emxEnsureCapacity((emxArray__common *)outliers2, ia, (int)sizeof(boolean_T));
    ic = b_y1->size[0];
    emxFree_real_T(&b_s);
    for (ia = 0; ia < ic; ia++) {
        outliers2->data[ia] = (b_y1->data[ia] > 3.0 * SigmaMat->data[ia]);
    }
    emxFree_real_T(&b_y1);
    emxFree_real_T(&SigmaMat);
    /*  Reference:  */
    /*  Aubert, A. E., D. Ramaekers, et al. (1999). "The analysis of heart  */
    /*  rate variability in unrestrained rats. Validation of method and  */
    /*  results." Comput Methods Programs Biomed 60(3): 197-213. */
    /* convert to logical array */
}
// 
// File trailer for locateOutliers.cpp 
//  
// [EOF] 
//
