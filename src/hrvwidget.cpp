#include "hrvwidget.h"
#include "sliderwidget.h"
#include "convertecgtoibi.h"
#include <plot.h>
#include <QtWidgets>
#include "hrvanalysis.h"

#include <QDebug>

#include <cmath>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "HRV/timeDomainHRV_emxAPI.h"
#include "HRV/timeDomainHRV_terminate.h"
#include "HRV/timeDomainHRV_initialize.h"
#include "HRV/freqDomainHRV_types.h"



HrvWidget::HrvWidget(QWidget *parent):
QWidget( parent )
{


	setupComponents();
	setupActions();
	setupLayout();
}

/*
 * Load the supported ECG formats from the application directory.
 *
 * Supported formats: .txt, .edf, .bdf
 */
void HrvWidget::getEcgFileList()
{
	ecgFilesWidget->clear();

	QStringList nameFilter;
	nameFilter << "*.txt";
	nameFilter << "*.edf";
	nameFilter << "*.bdf";
	QDir directory(qApp->applicationDirPath());
	QStringList ecgFiles = directory.entryList(nameFilter);

	ecgFilesWidget->addItems(ecgFiles);
}

/*
 * If a file is double-clicked, load it in a different thread to prevent locking the GUI
 */
void HrvWidget::fileSelected(QListWidgetItem *item)
{
	tlbl->setText("Loading "+item->text());
	progBar->setVisible(true);
	progBar->setRange(0,0);
	progBar->setValue(0);

	ConvertEcgToIbi *loadFile = new ConvertEcgToIbi(item->text());

    connect(loadFile, SIGNAL(sendFileData(QVector<double>, QVector<double>)), this, SLOT(performHRV(QVector<double>, QVector<double>)));
    connect(loadFile,SIGNAL(finished()),SLOT(fileFinished()));
	loadFile->start();
	headerTextArea->setText("Performing HRV-Calculations");
	//Read header file and display information about the recording
    QFileInfo fInfo(item->text());
	QFile headerFile(fInfo.baseName()+"_header.txt");
	if (headerFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream headerTextStream(&headerFile);
		QString headerText;

		while (!headerTextStream.atEnd()) {
			headerText += headerTextStream.readLine() + "\n";
		}

		headerTextArea->setText(headerText);
		headerTextStream.flush();
		headerFile.close();
	}
    performHRV(fInfo.baseName());



}

void HrvWidget::saveFreqHrv(const structFreq_T *tobeSaved){
	QFile outFile("outputFreqHRV.txt");
	if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Failed to open data file for write" << endl;
	} else {
		QTextStream out(&outFile);
		for (int i=0; i<512; i++){
			out << QString::number(tobeSaved->lomb.f[i], 'f', 3) << "\t"
					<< QString::number(tobeSaved->lomb.psd[i], 'f', 3) << "\n";
		}
		outFile.close();
	}
}

void HrvWidget::performHRV(QString fileInfo) {
    QFile ibiFile(fileInfo+".txt_RR.txt");
    if (ibiFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ibiTextStream(&ibiFile);

        int i=0;
        QString strVals = ibiTextStream.readLine();
        QStringList strPieces = strVals.split(QRegularExpression("\\s+"));
        QVector <double> ibiData;
        QVector <double> timeData;
        while (!ibiTextStream.atEnd()) {
            strVals = ibiTextStream.readLine();
            strPieces = strVals.split(QRegularExpression("\\s+"));

            if (strPieces.length()==3) {
                ibiData.append(strPieces[2].toDouble());
                timeData.append(strPieces[1].toDouble());
            }
            else if (strPieces.length()==2) {
                ibiData.append(strPieces[1].toDouble());
                timeData.append(strPieces[0].toDouble());
            }
        }
         struct0_T outputTime;
         performTimeDomainHrv(&ibiData, &outputTime);
         structFreq_T outputFreq;
         performFreqDomainHrv(&ibiData, &timeData, &outputFreq);
         psdPlot(&outputFreq);
         printHRV(&outputTime);
         printHRV(&outputFreq);
         saveFreqHrv(&outputFreq);


        ibiTextStream.flush();
        ibiFile.close();
    }


}

void HrvWidget::performHRV(QVector<double> ibiData, QVector<double> timeData){
    struct0_T outputTime;
    performTimeDomainHrv(&ibiData, &outputTime);
    structFreq_T outputFreq;
    performFreqDomainHrv(&ibiData, &timeData, &outputFreq);
    psdPlot(&outputFreq);
    printHRV(&outputTime);
    printHRV(&outputFreq);
    saveFreqHrv(&outputFreq);

}

void HrvWidget::printHRV(const struct0_T *outputHrv){
	qDebug() << "Max: " << outputHrv->max << endl
			<< "Mean HR: " << outputHrv->meanHR << endl
			<< "SDNN: " << outputHrv->SDNN << endl
			<< "SDANN: " << outputHrv->SDANN << endl
			<< "Mean: " << outputHrv->mean << endl
			<< "Min: " << outputHrv->min << endl
            << "Median: " << outputHrv->median << endl;
    QString headerText;
    headerTextArea->setText("<b>Time Domain Statistics: </b>");
    headerText=+ "Max: " + QString::number(outputHrv->max, 'f', 3);
    headerTextArea->append(headerText);headerText=+ "Mean HR: " + QString::number(outputHrv->meanHR, 'f', 3);
    headerTextArea->append(headerText);headerText=+ "SDNN: " + QString::number(outputHrv->SDNN, 'f', 3);
    headerTextArea->append(headerText);headerText=+ "SDANN: " + QString::number(outputHrv->SDANN, 'f', 3);
    headerTextArea->append(headerText);headerText=+ "Mean: " + QString::number(outputHrv->mean, 'f', 3);
    headerTextArea->append(headerText);headerText=+ "Min: " + QString::number(outputHrv->min, 'f', 3);
    headerTextArea->append(headerText);headerText=+ "Median: " + QString::number(outputHrv->median, 'f', 3);
    headerTextArea->append(headerText);

}

void HrvWidget::printHRV(const structFreq_T *outputHrv){
	qDebug() << outputHrv->lomb.hrv.aHF << endl
			<< outputHrv->lomb.hrv.aHF << endl
			<< outputHrv->lomb.hrv.nLF << endl
			<< outputHrv->lomb.hrv.nHF << endl
			<< outputHrv->lomb.hrv.aTotal << endl
			<< outputHrv->lomb.hrv.aLF << endl
			<< outputHrv->lomb.hrv.LFHF << endl
			<< outputHrv->lomb.hrv.pVLF << endl;
  mainTextArea->append("<b> Frequency Domain Statistics </b>");
    mainTextArea->append("LF / HF: " + QString::number(outputHrv->lomb.hrv.LFHF, 'f', 3));
            mainTextArea->append("Power HF: " + QString::number(outputHrv->lomb.hrv.pHF, 'f', 3) + "%");
            mainTextArea->append("Power LF: " + QString::number(outputHrv->lomb.hrv.pLF, 'f', 3)+ "%");
        mainTextArea->append("Power VLF: " + QString::number(outputHrv->lomb.hrv.pVLF, 'f', 3) + "%");
	//   myCurve->setRenderHint( QwtPlotItem::RenderAntialiased );
	   myCurve->setPen( Qt::blue );
	 //  myCurve->setLegendAttribute( QwtPlotCurve::LegendShowLine );
	 //  myCurve->setYAxis( QwtPlot::yLeft );

	   myCurve->setSamples(outputHrv->lomb.f,outputHrv->lomb.psd,100);
	   //myCurve->setSamples(freq,psd,100);
	   myCurve->attach(lombPlot);
	   lombPlot->replot();
}


/**
 *
 * @param tobePloted
 */
void HrvWidget::psdPlot(const structFreq_T *tobePloted) {
	double mean_Freq=0,mean_psd=0;
	int index=5;
	for (int i=0; i<102; i++) {
	for (int j=0; j<10;j++) {
		mean_Freq+=tobePloted->lomb.f[index+j-5];
		mean_psd+=tobePloted->lomb.psd[index+j-5];

	}
	index++;
	freq[i]=mean_Freq/10;
	psd[i]=mean_psd/10;
	mean_Freq=0;
	mean_psd=0;
	}

}
/**
 * Clear the plot
 */
void HrvWidget::clearPlot()
{

		lombPlot->repaint();

}




void HrvWidget::fileFinished(){
    tlbl->setText("Done!");
    progBar->setMaximum(10);
    progBar->setValue(10);
}





/**
 * Setup the necessary components that is used in the widget
 */
void HrvWidget::setupComponents()
{


	//Buttons
	getFilesButton = new QPushButton("Get ECG files");
	resetPlotButton = new QPushButton("Reset plot");

	//Header text area
    headerTextArea = new QTextBrowser();
    headerTextArea->setMinimumWidth(250);

    //Main text Area
    mainTextArea = new QTextBrowser();

	//Progressbar label
    tlbl = new QLabel("No file selected");

	//List of ecg files
	ecgFilesWidget = new QListWidget;
	ecgFilesWidget->setFixedSize(QSize(QWIDGETSIZE_MAX,100));

    //Lomb Plot
	lombPlot=new QwtPlot(this);
	lombPlot->setTitle("Lomb");
    lombPlot->setFixedSize(QSize(QWIDGETSIZE_MAX,300));
	myCurve = new QwtPlotCurve( "Lomb" );


	//Progress bar
	progBar = new QProgressBar();
	progBar->setRange(0,0);
	progBar->setVisible(false);
	progBar->setTextVisible(false);



}

/**
 * Setup actions and the signal-slots used in the widget
 */
void HrvWidget::setupActions()
{

	//Signals-slots
	connect(resetPlotButton, SIGNAL(clicked()), this, SLOT(clearPlot()));
    connect(ecgFilesWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(fileSelected(QListWidgetItem*)));
	connect(getFilesButton, SIGNAL(clicked()), this, SLOT(getEcgFileList()));

}

/**
 * Setup the layout of the widget
 */
void HrvWidget::setupLayout()
{




	//Progressbar area
	QHBoxLayout *progressBarLayout = new QHBoxLayout;
	progressBarLayout->addWidget(tlbl, 2);
	progressBarLayout->addWidget(progBar, 8);



	//Area with navigation control components
	QHBoxLayout *playbackLayout = new QHBoxLayout;



	//Sidebar layout
    QVBoxLayout *sidebarLayout = new QVBoxLayout;
	sidebarLayout->addWidget(getFilesButton);
	sidebarLayout->addWidget(ecgFilesWidget);
	sidebarLayout->addLayout(progressBarLayout);
    sidebarLayout->addWidget(headerTextArea);
	sidebarLayout->addStretch();
	sidebarLayout->addWidget(resetPlotButton);

	//Plot layout
	QVBoxLayout *plotLayout = new QVBoxLayout;
	plotLayout->addWidget(lombPlot);
    plotLayout->addWidget(mainTextArea);



	//Main layout
	QHBoxLayout *mainLayout = new QHBoxLayout;

	mainLayout->addLayout(sidebarLayout, 1);
	mainLayout->addLayout(plotLayout, 9);

	setLayout(mainLayout);


}
