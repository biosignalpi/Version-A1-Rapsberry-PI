/*
 * hrvanalysis.h
 *
 *  Created on: Nov 23, 2015
 *      Author: martin
 */

#ifndef HRVANALYSIS_H_
#define HRVANALYSIS_H_

#include "HRV/rtwtypes.h"
#include "HRV/timeDomainHRV.h"
#include "HRV/rt_nonfinite.h"
#include "HRV/timeDomainHRV_types.h"
#include "HRV/freqDomainHRV.h"
#include "HRV/freqDomainHRV_types.h"


#include <QVector>

/**
 * @addtogroup HRV-Analysis
 * @brief Classes and Functions used for HRV-Analysis
 * @author Martin
 * @todo Add a function/class that takes a DataStream object as input and performs all the steps of the HRV Analysis
 * taking ECG-Data as input and returning calculated HRV-Data.
 * @{ */
/**
     *@file hrvanalysis.h
     *  @brief Collection of functions used to interact with the Matlab Coder generated HRV-functions.
     *
     * @todo add the ability to use a DataStream object as input for the HRV-functions.
     */


/**
     * @brief Performs the Statistical Time Domain calculations for HRV Analysis
     * @param[in] ibiData QVector containing double with ibi information.
     * @param[out] output struct0_T containing all the calculated metrics
     *
     * @todo Add Ectopic Intervall Detection and Ectopic Interval Correction for the ibiData
     *
 */
    void performTimeDomainHrv(const QVector<double>* ibiData, struct0_T *output);

    /**
     * @brief Performs calculations for Frequency Domain HRV Analysis
     * @param[in] ibiData QVector containing double with ibi information.
     * @param[in] timeData QVector containing double with time information.
     * @param[out] output struct0_T containing the calculated metrics needed to plot a Lomb-periodogram
     *
     * @todo Add Ectopic Intervall Detection and Ectopic Interval Correction for the ibiData
     * @todo Add Detrend for the ibiData
     *
     */
    void performFreqDomainHrv(const QVector<double>* ibiData,const QVector<double>* timeData, structFreq_T *output);
	// Function Declarations for timeDomainHRV



    /**
         * @brief Creates the emxArray_real_T needed for performTimeDomainHrv()
         * The emxArray_real_T is the input vector to the Matlab-Coder function called
         * by performTimeDomainHrv()
         * @return ibiVector with default values
         */
	    static emxArray_real_T *argInit_Unboundedx2_real_T();
        /**
         * @brief Creates the emxArray_real_T needed for performTimeDomainHrv()
         * The emxArray_real_T is the input vector to the Matlab-Coder function called
         * by performTimeDomainHrv()
         * @param ibiData QVector containing IBI information
         * @return ibiVector with the values extracted from ibiData
         */
        static emxArray_real_T *argInit_Unboundedx2_real_T(const QVector<double>* ibiData);
        /**
         * @brief Creates the emxArray_real_T needed for performTimeDomainHrv()
         * The emxArray_real_T is the input vector to the Matlab-Coder function called
         * by performFreqDomainHrv()
         * @param ibiData QVector containing IBI information
         * @param timeData QVector containing time information to go along with the IBI information
         * @return ibiVector with the values extracted from ibiData and timeData
         */
        static emxArray_real_T *argInit_Unboundedx2_real_T(const QVector<double>* ibiData,const QVector<double>*timeData);





/** @} */


#endif /* HRVANALYSIS_H_ */
