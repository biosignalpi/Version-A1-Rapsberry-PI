/*
 * plotandcapturewidget.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: martin
 */

#include "plotandcapturewidget.h"
#include "plot.h"
#include "datalogger.h"


PlotAndCaptureWidget::PlotAndCaptureWidget(QWidget *parent):
QWidget(parent), plottedPoints(0)
{
 			d_plots.append(new Plot("Lead I", this));
			d_plots.append(new Plot("Lead II", this));
			d_plots.append(new Plot("Lead III", this));
			d_plots.append(new Plot("Respiration", this));

			d_plots[0]->setCurveColor(Qt::red);
			d_plots[1]->setCurveColor(Qt::blue);
			d_plots[2]->setCurveColor(Qt::green);
			d_plots[3]->setCurveColor(Qt::black);


			counter = 0;
			loopCounter = 0;
			currentTime = 0.0;
			timeInterval = 10.0;
			d_clock.start();


            device=new DeviceManager();
            stream=new DataStream();
               logger=new DataLogger();

      //         QThread *sampleT = new QThread;
      //         device->moveToThread(sampleT);
			    setupComponents();
			    setupActions();
			    setupLayout();




}


void PlotAndCaptureWidget::takeScreen() {
    //QPixmap pixmap = d_plot->grab();
    QPixmap pixmap = this->grab();
    pixmap.save("screen.png");
}

/**
 *
 */
void PlotAndCaptureWidget::updateStatus(QString status) {
	currentStatusLabel->setText(status);
}




PlotAndCaptureWidget::~PlotAndCaptureWidget() {
	// TODO Auto-generated destructor stub
	delete device;
	delete stream;
    delete logger;
}

void PlotAndCaptureWidget::startCapture()
{

        device->init(1, *stream);
        connect(device, SIGNAL(sendSampleVector(QVector<QVector<QPointF> >)), this, SLOT(plotSampleVector(QVector<QVector<QPointF> >)),Qt::QueuedConnection);
        connect(device, SIGNAL(updateStatus(QString)), this, SLOT(updateStatus(QString)),Qt::QueuedConnection);
    stopButton->setEnabled(true);
    startButton->setDisabled(true);
    currentStatusLabel->setText("Recording...");


    	device->startCapture();
  
}

/**
 * Stop the ECG capture, this will stop the sampling thread so no more samples will
 * be collected. The collected samples will be saved and the status label will
 * be updated accordingly.
 */
void PlotAndCaptureWidget::stopCapture()
{


		device->stop();
    stream->size();
    stopButton->setEnabled(false);
    currentStatusLabel->setText("Stopped!");

    logger->save(*stream);
    startButton->setEnabled(true);
}

void PlotAndCaptureWidget::plotSampleVector(QVector<QVector<QPointF> > sampleVector)
{

   // qDebug()<<sampleVector;
    const int sampleSize = sampleVector.length();
    QPointF last = sampleVector.at(sampleSize-1).at(0);
    const double elapsedTime = last.x();

    if (elapsedTime > currentTime+timeInterval)
    {
        for (int ii = 0; ii<4; ii++) {
            d_plots[ii]->IncrementInterval();
            d_plots[ii]->ClearPlot();
        }
//        d_plot->IncrementInterval();
//        d_plot->ClearPlot();

//        currentTime += timeInterval;
    }

    for (int ii = 0; ii < sampleSize; ii++) {
        for (int jj = 0; jj<4; jj++) {
            d_plots[jj]->AppendPoint(sampleVector.at(ii).at(jj));
        }
//        d_plot->AppendPoint(sampleVector.at(ii).at(0));
    }

    for (int ii = 0; ii<4; ii++) {
        d_plots[ii]->DrawCurveSegment(sampleSize);
    }
//    d_plot->DrawCurveSegment(sampleSize);

}

void PlotAndCaptureWidget::setupComponents()
{
    //Status label
    currentStatusLabel = new QLabel("Off");


    //=====START CHANNEL CONTROL COMPONENTS=====
    channelControlGroup = new QGroupBox("Channel control");
    channelControlButtonGroup = new QButtonGroup;
    leadIButton = new QRadioButton("Lead I");
    leadIIButton = new QRadioButton("Lead II");
    leadIIIButton = new QRadioButton("Lead III");
    respButton = new QRadioButton("Respiration");
    channelControlButtonGroup->addButton(leadIButton, 1);
    channelControlButtonGroup->addButton(leadIIButton, 2);
    channelControlButtonGroup->addButton(leadIIIButton, 3);
    channelControlButtonGroup->addButton(respButton, 4);
    leadIButton->setChecked(true);
    //=====END CHANNEL CONTROL COMPONENTS=====

    //Buttons
    startButton = new QPushButton(tr("Start ECG capture"));
    startButton->show();
    stopButton = new QPushButton(tr("Stop ECG capture"));
    stopButton->setDisabled(true);
    takeScreenshot = new QPushButton("Take screenshot");
}

void PlotAndCaptureWidget::setupActions()
{
    //Signals-slots
    connect(takeScreenshot, SIGNAL(clicked()), this, SLOT(takeScreen()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startCapture()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopCapture()));
     connect(logger, SIGNAL(updateStatus(QString)), this, SLOT(updateStatus(QString)));

}

void PlotAndCaptureWidget::setupLayout()
{
    QLabel *statusLabel = new QLabel("Status: ");
    QLabel *xAxisLabel = new QLabel("Time [s]");
    xAxisLabel->setAlignment(Qt::AlignCenter);

    //Channel control layout
    QHBoxLayout *channelControlLayout = new QHBoxLayout;
    channelControlLayout->addWidget(leadIButton);
    channelControlLayout->addWidget(leadIIButton);
    channelControlLayout->addWidget(leadIIIButton);
    channelControlLayout->addWidget(respButton);

    channelControlGroup->setLayout(channelControlLayout);

    //Status bar layout
    QHBoxLayout *statusBarLayout = new QHBoxLayout;
    statusBarLayout->addWidget(statusLabel);
    statusBarLayout->addWidget(currentStatusLabel);
    statusBarLayout->addStretch();

    //Buttons on the top of the widget
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(takeScreenshot);

    //Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(statusBarLayout);

    for (int ii = 0; ii<4; ii++) {
        mainLayout->addWidget(d_plots[ii]);
    }
    mainLayout->addWidget(xAxisLabel);
    mainLayout->addWidget(channelControlGroup);

    setLayout(mainLayout);
}
