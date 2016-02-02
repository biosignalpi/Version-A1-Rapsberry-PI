//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: replaceOutliers.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 29-Dec-2015 12:14:51
//

// Include Files
#include "rt_nonfinite.h"
#include "preProcessIBI.h"
#include "replaceOutliers.h"
#include "mean.h"
#include "preProcessIBI_emxutil.h"

// Custom Source Code
/** Created in Matlab Coder by Martin, files generated from preProcessIBI */

// Function Definitions 

// 
// MARTIN%, method, opt1, opt2) 
// replaceOutliers: replaces artifacts/outliers from data series 
//  
// Inputs:    t = time 
//            y = ibi values 
//            outliers = logical array of outliers. 0=normal, 1=outlier 
//            method = artifact replacement method to use. 
//    methods:    'remove' = Outliers are removed 
//                'mean' = Outliers are replaced with mean value from nearest +- m ibi values. 
//                'spline' = Outliers are replaced by cubic spline interpolation 
//                'median' = Outliers are replaced with median value from nearest +- m ibi values. 
// Outputs:   t2, y2 = arrays with replaced artifacts 
// Examples:  
//    remove outliers from ibi series 
//        [t2 y2] = replaceOutlers(t,y, outlierArray,'remove') 
// Arguments    : emxArray_real_T *y 
//                const emxArray_boolean_T *outliers 
//                emxArray_real_T *y2 
// Return Type  : void 
//
void replaceOutliers(emxArray_real_T *y, const emxArray_boolean_T *outliers, emxArray_real_T *y2)
{
    int i4;
    int ii;
    emxArray_int32_T *b_ii;
    int nx;
    int idx;
    boolean_T exitg1;
    boolean_T guard1 = false;
    emxArray_real_T *i;
    emxArray_boolean_T *r2;
    emxArray_boolean_T *r3;
    double b_y;
    emxArray_int32_T *r4;
    int unnamed_idx_1;
    int b_index;
    emxArray_real_T *tmpy;
    emxArray_int32_T *r5;
    emxArray_boolean_T *r6;
    emxArray_real_T *b_tmpy;
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
    /* MARTIN%   if nargin < 3 */
    /* MARTIN%       error('Not enough input arguments') */
    /* MARTIN%   elseif nargin < 4 */
    /* MARTIN%       opt2=nan; */
    /* MARTIN%   elseif nargin < 5 */
    /* MARTIN%       opt2=nan; */
    /* MARTIN%   end         */
    /* MARTIN%   switch lower(method) */
    /* MARTIN%       case 'remove' %remove outliers */
    /* MARTIN%           y2=y; */
    /* MARTIN%           t2=t; */
    /* MARTIN%           y2(outliers,:) = []; */
    /* MARTIN%           t2(outliers,:) = []; */
    /* MARTIN%       case 'mean' %mean replacement             */
    i4 = y2->size[0];
    y2->size[0] = y->size[0];
    emxEnsureCapacity((emxArray__common *)y2, i4, (int)sizeof(double));
    ii = y->size[0];
    for (i4 = 0; i4 < ii; i4++) {
        y2->data[i4] = y->data[i4];
    }
    emxInit_int32_T1(&b_ii, 1);
    /* preallowcate newIBI series with old values */
    /* number of ibi */
    /* check input argument */
    /* calculate half window width */
    nx = outliers->size[0];
    idx = 0;
    i4 = b_ii->size[0];
    b_ii->size[0] = outliers->size[0];
    emxEnsureCapacity((emxArray__common *)b_ii, i4, (int)sizeof(int));
    ii = 1;
    exitg1 = false;
    while ((!exitg1) && (ii <= nx)) {
        guard1 = false;
        if (outliers->data[ii - 1]) {
            idx++;
            b_ii->data[idx - 1] = ii;
            if (idx >= nx) {
                exitg1 = true;
            } else {
                guard1 = true;
            }
        } else {
            guard1 = true;
        }
        if (guard1) {
            ii++;
        }
    }
    if (outliers->size[0] == 1) {
        if (idx == 0) {
            i4 = b_ii->size[0];
            b_ii->size[0] = 0;
            emxEnsureCapacity((emxArray__common *)b_ii, i4, (int)sizeof(int));
        }
    } else {
        i4 = b_ii->size[0];
        if (1 > idx) {
            b_ii->size[0] = 0;
        } else {
            b_ii->size[0] = idx;
        }
        emxEnsureCapacity((emxArray__common *)b_ii, i4, (int)sizeof(int));
    }
    emxInit_real_T(&i, 1);
    i4 = i->size[0];
    i->size[0] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)i, i4, (int)sizeof(double));
    ii = b_ii->size[0];
    for (i4 = 0; i4 < ii; i4++) {
        i->data[i4] = b_ii->data[i4];
    }
    emxInit_boolean_T(&r2, 1);
    /* index location of outliers                         */
    i4 = r2->size[0];
    r2->size[0] = i->size[0];
    emxEnsureCapacity((emxArray__common *)r2, i4, (int)sizeof(boolean_T));
    ii = i->size[0];
    for (i4 = 0; i4 < ii; i4++) {
        r2->data[i4] = (i->data[i4] > 3.0);
    }
    emxInit_boolean_T(&r3, 1);
    b_y = (double)y->size[0] - 2.0;
    i4 = r3->size[0];
    r3->size[0] = i->size[0];
    emxEnsureCapacity((emxArray__common *)r3, i4, (int)sizeof(boolean_T));
    ii = i->size[0];
    for (i4 = 0; i4 < ii; i4++) {
        r3->data[i4] = (i->data[i4] < b_y);
    }
    /* index location of outliers within range */
    idx = r2->size[0] - 1;
    ii = 0;
    for (nx = 0; nx <= idx; nx++) {
        if (r2->data[nx] && r3->data[nx]) {
            ii++;
        }
    }
    i4 = b_ii->size[0];
    b_ii->size[0] = ii;
    emxEnsureCapacity((emxArray__common *)b_ii, i4, (int)sizeof(int));
    ii = 0;
    for (nx = 0; nx <= idx; nx++) {
        if (r2->data[nx] && r3->data[nx]) {
            b_ii->data[ii] = nx + 1;
            ii++;
        }
    }
    emxInit_int32_T(&r4, 2);
    i4 = r4->size[0] * r4->size[1];
    r4->size[0] = 1;
    r4->size[1] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)r4, i4, (int)sizeof(int));
    ii = b_ii->size[0];
    for (i4 = 0; i4 < ii; i4++) {
        r4->data[r4->size[0] * i4] = (int)i->data[b_ii->data[i4] - 1];
    }
    ii = r4->size[0] * r4->size[1];
    for (i4 = 0; i4 < ii; i4++) {
        y->data[r4->data[i4] - 1] = rtNaN;
    }
    emxFree_int32_T(&r4);
    idx = r2->size[0] - 1;
    ii = 0;
    for (nx = 0; nx <= idx; nx++) {
        if (r2->data[nx] && r3->data[nx]) {
            ii++;
        }
    }
    i4 = b_ii->size[0];
    b_ii->size[0] = ii;
    emxEnsureCapacity((emxArray__common *)b_ii, i4, (int)sizeof(int));
    ii = 0;
    for (nx = 0; nx <= idx; nx++) {
        if (r2->data[nx] && r3->data[nx]) {
            b_ii->data[ii] = nx + 1;
            ii++;
        }
    }
    unnamed_idx_1 = b_ii->size[0];
    b_index = 0;
    emxInit_real_T(&tmpy, 1);
    emxInit_int32_T1(&r5, 1);
    emxInit_boolean_T(&r6, 1);
    emxInit_real_T(&b_tmpy, 1);
    while (b_index <= unnamed_idx_1 - 1) {
        idx = r2->size[0] - 1;
        ii = 0;
        for (nx = 0; nx <= idx; nx++) {
            if (r2->data[nx] && r3->data[nx]) {
                ii++;
            }
        }
        i4 = b_ii->size[0];
        b_ii->size[0] = ii;
        emxEnsureCapacity((emxArray__common *)b_ii, i4, (int)sizeof(int));
        ii = 0;
        for (nx = 0; nx <= idx; nx++) {
            if (r2->data[nx] && r3->data[nx]) {
                b_ii->data[ii] = nx + 1;
                ii++;
            }
        }
        if (i->data[b_ii->data[b_index] - 1] - 2.0 > i->data[b_ii->data[b_index] - 1] + 2.0) {
            i4 = 0;
            nx = 0;
        } else {
            i4 = (int)(i->data[b_ii->data[b_index] - 1] - 2.0) - 1;
            nx = (int)(i->data[b_ii->data[b_index] - 1] + 2.0);
        }
        ii = tmpy->size[0];
        tmpy->size[0] = nx - i4;
        emxEnsureCapacity((emxArray__common *)tmpy, ii, (int)sizeof(double));
        ii = nx - i4;
        for (nx = 0; nx < ii; nx++) {
            tmpy->data[nx] = y->data[i4 + nx];
        }
        i4 = r6->size[0];
        r6->size[0] = tmpy->size[0];
        emxEnsureCapacity((emxArray__common *)r6, i4, (int)sizeof(boolean_T));
        ii = tmpy->size[0];
        for (i4 = 0; i4 < ii; i4++) {
            r6->data[i4] = rtIsNaN(tmpy->data[i4]);
        }
        i4 = r6->size[0];
        emxEnsureCapacity((emxArray__common *)r6, i4, (int)sizeof(boolean_T));
        ii = r6->size[0];
        for (i4 = 0; i4 < ii; i4++) {
            r6->data[i4] = !r6->data[i4];
        }
        idx = r6->size[0] - 1;
        ii = 0;
        for (nx = 0; nx <= idx; nx++) {
            if (r6->data[nx]) {
                ii++;
            }
        }
        i4 = r5->size[0];
        r5->size[0] = ii;
        emxEnsureCapacity((emxArray__common *)r5, i4, (int)sizeof(int));
        ii = 0;
        for (nx = 0; nx <= idx; nx++) {
            if (r6->data[nx]) {
                r5->data[ii] = nx + 1;
                ii++;
            }
        }
        i4 = b_tmpy->size[0];
        b_tmpy->size[0] = r5->size[0];
        emxEnsureCapacity((emxArray__common *)b_tmpy, i4, (int)sizeof(double));
        ii = r5->size[0];
        for (i4 = 0; i4 < ii; i4++) {
            b_tmpy->data[i4] = tmpy->data[r5->data[i4] - 1];
        }
        y2->data[(int)i->data[b_ii->data[b_index] - 1] - 1] = mean(b_tmpy);
        /* replace with mean, ignore NaN values */
        b_index++;
    }
    emxFree_real_T(&b_tmpy);
    emxFree_boolean_T(&r6);
    emxFree_int32_T(&b_ii);
    emxFree_int32_T(&r5);
    emxFree_boolean_T(&r3);
    emxFree_boolean_T(&r2);
    emxFree_real_T(&tmpy);
    emxFree_real_T(&i);
    /* MARTIN%       case {'spline','cubic'} %Cubic spline replacment             */
    /* MARTIN%           y(outliers) = NaN; %replace outliers with nan */
    /* MARTIN%           t2=t;             */
    /* MARTIN%           y2=interp1(t2,y,t2,'spline','extrap'); */
    /* MARTIN%       case 'median' %medianFilter */
    /* MARTIN%           y2=y; %preallowcate newIBI series with old values */
    /* MARTIN%           t2=t; */
    /* MARTIN%           l=length(y); %number of ibi */
    /* MARTIN%           if ~isnan(opt1) %check input argument */
    /* MARTIN%                m=floor((opt1-1)/2); %calculate half window width */
    /* MARTIN%           end */
    /* MARTIN%            */
    /* MARTIN%           i=find(outliers); %index location of outliers */
    /* MARTIN%            i=(i(i>m+1 & i<l-m))'; %index location of outliers within range */
    /* MARTIN%           y(i)=nan; */
    /* MARTIN%            for n=i; */
    /* MARTIN%                tmpy=y(n-m:n+m); */
    /* MARTIN%                y2(n)=median(tmpy(~isnan(tmpy))); %replace with median, ignore NaN values */
    /* MARTIN%            end */
    /*  Reference: */
    /*  Thuraisingham, R. A. (2006). "Preprocessing RR interval time */
    /*  series for heart rate variability analysis and estimates of */
    /*  standard deviation of RR intervals." Comput.Methods */
    /*  Programs Biomed. */
    /* MARTIN%        otherwise % do nothing */
    /* MARTIN%            y2=y; */
    /* MARTIN%            t2=t;             */
    /* MARTIN%    end */
}
// 
// File trailer for replaceOutliers.cpp 
//  
// [EOF] 
//
