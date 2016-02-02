/*
 * convertecgtoibi.h
 *
 *  Created on: Nov 5, 2015
 *      Author: martin
 */

#ifndef CONVERTECGTOIBI_H_
#define CONVERTECGTOIBI_H_

#include <QThread>
#include <QVector>
#include <QPointF>
#include <QTime>

/**
 * @addtogroup HRV-Analysis
 * @{ */
/**
 * @brief Converts textfile with ECG-data into IBI file
 *
 *
 * @author Martin
 * @todo take different sort of files as input
 *
*/
class ConvertEcgToIbi : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief ConvertEcgToIbi
     * @param[in] fileName String containing the name of the file to process
     *
     */
    ConvertEcgToIbi(QString fileName, QObject *parent = NULL);
    virtual void run();

signals:
    /**
       * @brief sendFileData
       * @param qrsPeaks Vector containing R-R information
       * @param timeData Vector containing time information for the R-R data.
       *
       */
      void sendFileData(QVector<double> qrsPeaks, QVector<double> timeData);

private:

    QString fname;
    double sampRate=128;  ///< Important parameter defines the samplingrate for the HRV-Analysis @todo Making it possible setting it in Run-time instead of compiletime
    /**
     * @brief saves IbiVector given as input to a textfile with the ending _RR.txt
     *@param[in] IbiVector
     */
    void saveAsIbiFile(QVector<double>*);
    /**
     * @brief Function for beatDetection of the given QVector
     * Uses QRSDet from eplimited.com
    *@param input
    * @param output
     * @todo Fix so that the detection start without delay
     * @bug QRSDet needs about 10s before it can detect Peaks
    */
    void extractRtoR(QVector<int>*,QVector<double>*);
    QTime time;
};
/**
 * @brief QRSDet
 * Function used for the QRS-detection
 * @return
 */
int QRSDet(int,int);

/** @} */

#endif // ConvertEcgToIbi_H
