/*
 * hrvanalysis.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: martin
 */

#include "hrvanalysis.h"

#include <cmath>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <QDebug>



#include "HRV/timeDomainHRV_emxAPI.h"
#include "HRV/timeDomainHRV_terminate.h"
#include "HRV/timeDomainHRV_initialize.h"

#include "HRV/freqDomainHRV_emxAPI.h"
#include "HRV/freqDomainHRV_terminate.h"
#include "HRV/freqDomainHRV_initialize.h"


#include "HRV/preProcessIBI_terminate.h"
#include "HRV/preProcessIBI_initialize.h"
#include "HRV/preProcessIBI.h"
#include "HRV/preProcessIBI_types.h"


void performTimeDomainHrv(const QVector<double>* ibiData, struct0_T *output) {
	timeDomainHRV_initialize();
    preProcessIBI_initialize();

    emxArray_real_T *ibi, *nibi;
     emxArray_boolean_T *art;

    emxInitArray_real_T(&nibi, 2);
    emxInitArray_boolean_T(&art, 1);


	// Initialize function 'timeDomainHRV' input arguments.
	// Initialize function input argument 'ibi'.
	int i;
	ibi = argInit_Unboundedx2_real_T(ibiData);
    preProcessIBI(ibi, nibi, art);
	// Call the entry-point 'timeDomainHRV'.
	qDebug() << "Terminate Matlab function" << endl;
    timeDomainHRV(nibi, 100, 10, output);
	qDebug() << "Terminate Matlab function" << endl;
	emxDestroyArray_real_T(ibi);
    emxDestroyArray_real_T(nibi);
    emxDestroyArray_boolean_T(art);
	//	  qDebug() << "Terminate Matlab function" << endl;

	timeDomainHRV_terminate();
    preProcessIBI_terminate();
}
void performFreqDomainHrv(const QVector<double>* ibiData,const QVector<double>* timeData, structFreq_T *output) {
	freqDomainHRV_initialize();
    preProcessIBI_initialize();
    emxArray_real_T *ibi, *nibi;
    emxArray_boolean_T *art;

    emxInitArray_real_T(&nibi, 2);
    emxInitArray_boolean_T(&art, 1);
	// Initialize function 'timeDomainHRV' input arguments.
	// Initialize function input argument 'ibi'.
	int i;
	ibi = argInit_Unboundedx2_real_T(ibiData,timeData);
    preProcessIBI(ibi, nibi, art);
	// Call the entry-point 'timeDomainHRV'.
	qDebug() << "Terminate Matlab function" << endl;
    freqDomainHRV(nibi,output);
	qDebug() << "Terminate Matlab function" << endl;
	emxDestroyArray_real_T(ibi);
    emxDestroyArray_real_T(nibi);
    emxDestroyArray_boolean_T(art);
	//	  qDebug() << "Terminate Matlab function" << endl;

	freqDomainHRV_terminate();
    preProcessIBI_terminate();

}

emxArray_real_T *argInit_Unboundedx2_real_T(const QVector<double>* ibiData,const QVector<double>* timeData)
{

	emxArray_real_T *result;
	int iv1[2] = { ibiData->length(), 2 };

	int idx0;
	int idx1;

	// Set the size of the array.
	// Change this size to the value that the application requires.
	result = emxCreateND_real_T(2, *(int (*)[2])&iv1[0]);

	//   result = emxCreateND_real_T(2, *(int (*)[ibiData->length()])&iv1[0]);

	// Loop over the array to initialize each element.
	qDebug() << result->size[0U] << endl
			<< result->size[0] << endl
			<< ibiData->length() <<endl
			<< iv1[0] <<endl;
	int index=0;
	for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
		for (idx1 = 0; idx1 < 2; idx1++) {
			// Set the value of the array element.
			// Change this value to the value that the application requires.
			if (idx1==0)
				result->data[idx0 + result->size[0] * idx1] = (timeData->at(index)*1000);
			else
				result->data[idx0 + result->size[0] * idx1] = (ibiData->at(index++)*1000);
		}
	}

	qDebug() << "Created ibiFile in argInit_Unboundedx2_real_T" << endl;
	return result;
}

emxArray_real_T *argInit_Unboundedx2_real_T(const QVector<double>* ibiData)
{

	emxArray_real_T *result;
	int iv1[2] = { ibiData->length(), 2 };

	int idx0;
	int idx1;

	// Set the size of the array.
	// Change this size to the value that the application requires.
	result = emxCreateND_real_T(2, *(int (*)[2])&iv1[0]);

	//   result = emxCreateND_real_T(2, *(int (*)[ibiData->length()])&iv1[0]);

	// Loop over the array to initialize each element.
	qDebug() << result->size[0U] << endl
			<< result->size[0] << endl
			<< ibiData->length() <<endl
			<< iv1[0] <<endl;
	int timeCount=0,index=0;

	for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
		for (idx1 = 0; idx1 < 2; idx1++) {
			// Set the value of the array element.
			// Change this value to the value that the application requires.
			if (idx1==0) {
				result->data[idx0 + result->size[0] * idx1] = timeCount;
				timeCount+=ibiData->at(index);
			}
			else
				result->data[idx0 + result->size[0] * idx1] = (ibiData->at(index++));
		}
	}
	return result;
}

emxArray_real_T *argInit_Unboundedx2_real_T()
{

	emxArray_real_T *result;
	static int iv1[2] = { 2, 2 };

	int idx0;
	int idx1;

	// Set the size of the array.
	// Change this size to the value that the application requires.
	result = emxCreateND_real_T(2, *(int (*)[100])&iv1[0]);

	// Loop over the array to initialize each element.
	for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
		for (idx1 = 0; idx1 < 2; idx1++) {
			// Set the value of the array element.
			// Change this value to the value that the application requires.
            result->data[idx0 + result->size[0] * idx1] = 1.075;
		}
	}

	qDebug() << "Created ibiFile in argInit_Unboundedx2_real_T" << endl;
	return result;
}

