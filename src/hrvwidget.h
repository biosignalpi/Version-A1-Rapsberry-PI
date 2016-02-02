/*
 * hrvwidget.h
 *
 *  Created on: Nov 2, 2015
 *      Author: martin
 */

#ifndef HRVWidget_H_
#define HRVWidget_H_

#include <QWidget>
#include <QListWidget>

#include <qwt_plot_curve.h>
#include <qwt_plot.h>

#include "hrvanalysis.h"
#include "HRV/rtwtypes.h"
#include "HRV/timeDomainHRV.h"
#include "HRV/rt_nonfinite.h"
#include "HRV/timeDomainHRV_types.h"
#include "HRV/freqDomainHRV_types.h"

class Plot;
class QLabel;
class QProgressBar;
class SliderWidget;
class QComboBox;
class QPushButton;
class QTextBrowser;



/**
  @class HrvWidget
 * @brief Widget responsible for the graphical interface of the HRV Analysis
 *
 * @author Martin
 * @todo Might be neccessary to set a upper limit for how large files to
 * analyze. The qrs detection is the most computional demanding function called
 * by HrvWidget
 * @todo Add a seperate HeaderTextArea to display information from Header textfile if that exists.
 * @todo Add the ability to use it for different sampling frequency sampling frequency is set in compile-time. Value set in QRSDET.h and convertecgtoibi.h
 * @bug Might crash or work incorrectly for "wrong" formated ECG-files
 *
 *
 */
class HrvWidget : public QWidget
{
    Q_OBJECT

public:
    HrvWidget(QWidget * = NULL);


private:
    void setupComponents();  ///< widget function for setting up and creating the Components used in the Widget
    void setupActions(); ///< widget function for setting up the
    void setupLayout();

    /**
     * @brief If the file exists the function reads the information and calls the functions needed for all of the HRV-Analysis.
     * @param[in] filename QString with the name of the file to look for IBI data.
     *
     */
    void performHRV(QString fileName);
    void printHRV(const struct0_T *); ///< @brief Prints the Time Domain Metrics @param[in] output struct0_T object containing results from performTimeDomainHRV
    void printHRV(const structFreq_T *); ///< @brief Prints the Freq Domain Metrics @param[in] output structFreq_T object containing results from performFreqDomainHRV
    void psdPlot(const structFreq_T *); ///< @brief Constructs a Lomb-Plot from the calculated data @param[in] output structFreq_T object containing results from performTimeDomainHRV
    void saveFreqHrv(const structFreq_T *); ///< @brief Function to save lomb.f and lomb.psd into a textfile @param[in] output structFreq_T object containing results from performFreqDomainHRV @deprecated

    QListWidget *ecgFilesWidget;

    QVector<Plot *> d_plots;
    QVector<QVector<QPointF> > ecgVals;
    QLabel *tlbl;
    QProgressBar *progBar;
    SliderWidget *startingPointSlider;
    QComboBox *timeframeComboBox;
    QTimer *playTimer;

    int recordingTime;
    int nFrames;
    int currentFrame;
    double freq[102], psd[102];

    QPushButton *getFilesButton;
    QPushButton *resetPlotButton;
    QTextBrowser *headerTextArea;

     QTextBrowser *mainTextArea;
    QwtPlot *lombPlot;
    QwtPlotCurve *myCurve;



private slots:
    void fileFinished();
    /**
     * @brief Displays a list of .txt .bdf and .edf files available in the same directory as the application
     */
    void getEcgFileList();
    /**
     * @brief Called when a file is double-clicked, send the filename to ConvertEcgToIbi
     * Send the file to ConvertEcgToIbi for processing,
     * this is performed in a different thread to prevent locking the GUI
     */
    void fileSelected(QListWidgetItem*);
    void clearPlot();
    /**
     * @brief Performs HRV-Analysis on the provided data
     * Called by the signal ConvertEcgToIbi::sendFileData(QVector<double> qrsPeaks, QVector<double> timeData)
     *
     * @param ibiData IBI information in seconds
     * @param timeData time information in seconds
     * @return Populates the widget with HRV-Analysis information when it is done.
     */
    void performHRV(QVector<double> ibiData, QVector<double> timeData);


};



#endif /* HRVWidget_H_ */
