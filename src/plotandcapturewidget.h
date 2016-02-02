/*
 * plotandcapturewidget.h
 *
 *  Created on: Oct 29, 2015
 *      Author: martin
 */

#ifndef PLOTANDCAPTUREWIDGET_H_
#define PLOTANDCAPTUREWIDGET_H_

#include <QtWidgets>
#include <QString>
#include <qwt_plot.h>
#include <QElapsedTimer>
#include "devicemanager.h"
#include "datalogger.h"
#include "datastream.h"


class QLabel;
class QPushButton;
class Plot;

/**
 * @brief Widget used for capture and plotting of data from the connected DeviceManager
 *
 * @author Martin
 * @author Jonatan
 * @todo Move comments from .cpp file to header file (.h)
 */
class PlotAndCaptureWidget: public QWidget {

	Q_OBJECT

public:
	PlotAndCaptureWidget(QWidget * = NULL);
	virtual ~PlotAndCaptureWidget();
	void plotSample(double);



public slots:
	void startCapture();
	void stopCapture();
	void plotSampleVector(QVector<QVector<QPointF> >);
	void updateStatus(QString);

    /**
     * @brief Take a snapshot of the PLOT.
     *
     * @todo prevent overwriting previous snapshots
     */
	void takeScreen();



private:
	void setupComponents();
	void setupActions();
	void setupLayout();

	QGroupBox *sampleRateControlGroup;
	QGroupBox *sourceControlGroup;
	QGroupBox *channelControlGroup;
	QPushButton *startButton;
	QPushButton *stopButton;
	QPushButton *applySettingsButton;
	QPushButton *takeScreenshot;
	QButtonGroup *channelControlButtonGroup;
	QLabel *currentStatusLabel;
	QLineEdit *nameTextBox;
	QLineEdit *recordingNameTextBox;

	 QElapsedTimer d_clock;
	    double currentTime;
	    double timeInterval;

	    DeviceManager* device;
        DataStream* stream;
    DataLogger* logger;



	int counter, plottedPoints, loopCounter;
	QRadioButton *leadIButton, *leadIIButton, *leadIIIButton, *respButton;


	QVector<Plot *> d_plots;


};

#endif /* PLOTANDCAPTUREWIDGET_H_ */
