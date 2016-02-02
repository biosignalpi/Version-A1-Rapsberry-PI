#include "meanFilter.h"

double filterVal(double val)
{
    static double x[100];
    int n = 100;
    double mean = 0.0;

    for (int ii = 0; ii<n-1; ii++) {
        x[ii] = x[ii+1];
    }

    x[n-1] = val;

    for (int ii = 0; ii<n-1; ii++) {
        mean += x[ii];
    }

    return mean/n;
}

double filterEcgVal(double val)
{
    static double x[201];
    static double y[100];

    double mean = 0.0;

    x[200] = y[0];

    for (int ii = 0; ii<99; ii++) {
        y[ii] = y[ii+1];
    }

    y[99] = val;

    for (int ii = 0; ii<201; ii++) {
        mean += x[ii];
    }

    return x[100]-mean/201;
}
