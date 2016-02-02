#include "plottingwidget.h"
#include "sliderwidget.h"
#include "loadbigfile.h"
#include <plot.h>
#include <QtWidgets>

PlottingWidget::PlottingWidget(QWidget *parent):
    QWidget( parent )
{
    recordingTime = 0;
    nFrames = 0;
    currentFrame = 0;

    setupComponents();
    setupActions();
    setupLayout();
}

/*
 * Load the supported ECG formats from the application directory.
 *
 * Supported formats: .txt, .edf, .bdf
 */
void PlottingWidget::getEcgFileList()
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
void PlottingWidget::fileSelected(QListWidgetItem *item)
{
    tlbl->setText("Loading "+item->text());
    progBar->setVisible(true);
    progBar->setRange(0,0);
    progBar->setValue(0);

    LoadBigFile *loadFile = new LoadBigFile(item->text());

    connect(loadFile, SIGNAL(sendFileData(QVector<QVector<QPointF> >)), this, SLOT(initEcg(QVector<QVector<QPointF> >)));

    loadFile->start();

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
}

/*
 * Clear the plot
 */
void PlottingWidget::clearPlot()
{
    for (int ii = 0; ii<4; ii++) {
        d_plots[ii]->ClearPlot();
    }


}

/*
 * If the slider for browsing the ecg is moved, update the plot to show the new interval of
 * the ECG.
 */
void PlottingWidget::updatePlot(int index)
{
    int windowSize = timeframeComboBox->itemData(timeframeComboBox->currentIndex()).toInt();
    int startingPosition = index*windowSize;
    currentFrame = index;

    for (int ii = 0; ii<4; ii++) {
        d_plots[ii]->setInterval(startingPosition, startingPosition+windowSize);
    }
    // d_plot->setInterval(startingPosition, startingPosition+windowSize);
}

/*
 * If the window size of the plot is changed, go back to the start and update the plotted interval
 */
void PlottingWidget::windowSizeChanged(int index)
{
    if (index > 1) {
        currentFrame = 0;
        int windowSize = timeframeComboBox->itemData(index).toInt();
        nFrames = static_cast<int>(recordingTime/timeframeComboBox->itemData(index).toInt());

        for (int ii = 0; ii<4; ii++) {
            d_plots[ii]->setInterval(0, windowSize);
        }

        //d_plot->setInterval(0, windowSize);
    } else if (index == 0) {
        for (int ii = 0; ii<4; ii++) {
            d_plots[ii]->setInterval(0, recordingTime);
        }

        // d_plot->setInterval(0, recordingTime);
        nFrames = 0;
    }

    startingPointSlider->setInterval(0, nFrames);
    startingPointSlider->setValue(0);
}

/*
 * Init the ECG vector and display the ECG.
 */
void PlottingWidget::initEcg(QVector<QVector<QPointF> > fileData)
{
    ecgVals = fileData;

    tlbl->setText("Done!");
    progBar->setMaximum(10);
    progBar->setValue(10);

    recordingTime = static_cast<int>(ecgVals.last().at(0).x());
    nFrames = static_cast<int>(recordingTime/timeframeComboBox->itemData(timeframeComboBox->currentIndex()).toInt());

    startingPointSlider->setInterval(0,nFrames);

    plotVector();

    for (int ii = 0; ii<4; ii++) {
        d_plots[ii]->setInterval(0, timeframeComboBox->itemData(timeframeComboBox->currentIndex()).toInt());
    }

    if (recordingTime>5) {
        QVector<double> maxVector;
        QVector<double> minVector;

        for (int ii = 0; ii<4; ii++) {
            maxVector.append(ecgVals[500].at(ii).y());
            minVector.append(ecgVals[500].at(ii).y());
        }

        for (int ii = 500; ii<ecgVals.length(); ii++) {
            for (int jj = 0; jj<4; jj++) {
                if(ecgVals[ii].at(jj).y()<maxVector[jj]) {
                    if (ecgVals[ii].at(jj).y()<minVector[jj])
                    {
                        minVector[jj] = ecgVals[ii].at(jj).y();
                    }
                } else {
                    maxVector[jj] = ecgVals[ii].at(jj).y();
                }
            }
        }

        for (int ii = 0; ii<4; ii++) {
            d_plots[ii]->setYAxis(minVector[ii], maxVector[ii]);
        }

    }

    // d_plot->setInterval(0, timeframeComboBox->itemData(timeframeComboBox->currentIndex()).toInt());
}

/*
 * Plot the vector obtained from the initEcg method
 */
void PlottingWidget::plotVector()
{
    const int sampleSize = ecgVals.length();
    d_plots[0]->setInterval(0, ecgVals.last().at(0).x());

    for (int ii = 0; ii<4; ii++) {
        d_plots[ii]->ClearPlot();
    }
    // d_plot->ClearPlot();

    for (int ii = 0; ii < sampleSize; ii++) {
        for (int jj = 0; jj<4; jj++) {
            d_plots[jj]->AppendPoint(ecgVals.at(ii).at(jj));
        }
        // d_plot[ii]->AppendPoint(ecgVals.at(ii).at(0));
    }

    for (int ii = 0; ii<4; ii++) {
        d_plots[ii]->DrawCurveSegment(sampleSize);
    }
    // d_plot->DrawCurveSegment(sampleSize);

}

/*
 * Show the previous frame of the signal
 */
void PlottingWidget::prev()
{
    if (currentFrame > 0) {
        int windowSize = timeframeComboBox->itemData(timeframeComboBox->currentIndex()).toInt();
        currentFrame = startingPointSlider->value() - 1;
        startingPointSlider->setValue(currentFrame);

        for (int ii = 0; ii<4; ii++) {
            d_plots[ii]->setInterval(currentFrame*windowSize, (currentFrame+1)*windowSize);
        }
        // d_plot->setInterval(currentFrame*windowSize, (currentFrame+1)*windowSize);
    }
}

/*
 * Start ECG playback
 */
void PlottingWidget::play()
{
    int windowSize = timeframeComboBox->itemData(timeframeComboBox->currentIndex()).toInt();
    playTimer->start(windowSize*1000);
}

/*
 * Pause ECG playback
 */
void PlottingWidget::pause()
{
    playTimer->stop();
}

/*
 * Show the next fram of the signal
 */
void PlottingWidget::next()
{
    if (currentFrame<nFrames) {
        int windowSize = timeframeComboBox->itemData(timeframeComboBox->currentIndex()).toInt();
        currentFrame = startingPointSlider->value() + 1;
        startingPointSlider->setValue(currentFrame);

        for (int ii = 0; ii<4; ii++) {
            d_plots[ii]->setInterval(currentFrame*windowSize, (currentFrame+1)*windowSize);
        }
        // d_plot->setInterval(currentFrame*windowSize, (currentFrame+1)*windowSize);
    }
}

/*
 * Catches the event when the mouse is in the widget are and the scroll button is moved.
 * If scrolled away from the user the next methos is triggered and a step forward is made,
 * if scrolled towards the user the prev method is triggered to browse backwards.
 */
void PlottingWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if (delta > 0) {
        next();
    } else if (delta < 0) {
        prev();
    }
}

/*
 * Setup the necessary components that is used in the widget
 */
void PlottingWidget::setupComponents()
{
    //Timer used to play a recorded ECG
    playTimer = new QTimer();

    //Buttons
    getFilesButton = new QPushButton("Get ECG files");
    resetPlotButton = new QPushButton("Reset plot");

    //Header text area
    headerTextArea = new QTextEdit("");

    //Progressbar label
    tlbl = new QLabel("no file selected");

    //List of ecg files
    ecgFilesWidget = new QListWidget;
    ecgFilesWidget->setFixedSize(QSize(QWIDGETSIZE_MAX,100));

    //Plot widget
    //d_plot = new Plot("",this);
    d_plots.append(new Plot("Lead I", this));
    d_plots.append(new Plot("Lead II", this));
    d_plots.append(new Plot("Lead III", this));
    d_plots.append(new Plot("Respiration", this));

    d_plots[0]->setCurveColor(Qt::red);
    d_plots[1]->setCurveColor(Qt::blue);
    d_plots[2]->setCurveColor(Qt::green);
    d_plots[3]->setCurveColor(Qt::black);

    d_plots[3]->setCurveMargin(0.0001);

    //Progress bar
    progBar = new QProgressBar();
    progBar->setRange(0,0);
    progBar->setVisible(false);
    progBar->setTextVisible(false);

    //Window size component
    timeframeComboBox = new QComboBox();
    timeframeComboBox->addItem("Whole recording", 0);
    timeframeComboBox->insertSeparator(1);
    timeframeComboBox->addItem("5 s", 5);
    timeframeComboBox->addItem("10 s", 10);
    timeframeComboBox->addItem("1 min", 60);
    timeframeComboBox->setCurrentIndex(2);

    //Slider to navigate the recorded signal
    startingPointSlider = new SliderWidget();
}

/*
 * Setup actions and the signal-slots used in the widget
 */
void PlottingWidget::setupActions()
{
    //ECG navigation control buttons
    prevAction = new QAction(QIcon(":/images/images/media-skip-backward-6.png"), "Prev.", this);
    playAction = new QAction(QIcon(":/images/images/media-playback-start-6.png"), "Play", this);
    pauseAction = new QAction(QIcon(":/images/images/media-playback-pause-6.png"), "Pause", this);
    nextAction = new QAction(QIcon(":/images/images/media-skip-forward-6.png"), "Next", this);

    //Signals-slots
    connect(prevAction, SIGNAL(triggered()), this, SLOT(prev()));
    connect(nextAction, SIGNAL(triggered()), this, SLOT(next()));
    connect(playAction, SIGNAL(triggered()), this, SLOT(play()));
    connect(pauseAction, SIGNAL(triggered()), this, SLOT(pause()));
    connect(timeframeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(windowSizeChanged(int)));
    connect(getFilesButton, SIGNAL(clicked()), this, SLOT(getEcgFileList()));
    connect(resetPlotButton, SIGNAL(clicked()), this, SLOT(clearPlot()));
    connect(startingPointSlider, SIGNAL(valueChanged(int)), this, SLOT(updatePlot(int)));
    connect(ecgFilesWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(fileSelected(QListWidgetItem*)));
    connect(playTimer, SIGNAL(timeout()), this, SLOT(next()));
}

/*
 * Setup the layout of the widget
 */
void PlottingWidget::setupLayout()
{

    QLabel *wsLabel = new QLabel("Window size");

    //Setup the navigation control
    QToolBar *playbackButtons = new QToolBar;
    playbackButtons->addAction(prevAction);
    playbackButtons->addAction(playAction);
    playbackButtons->addAction(pauseAction);
    playbackButtons->addAction(nextAction);

    //Progressbar area
    QHBoxLayout *progressBarLayout = new QHBoxLayout;
    progressBarLayout->addWidget(tlbl, 2);
    progressBarLayout->addWidget(progBar, 8);

    //Window size control area
    QHBoxLayout *wsLayout = new QHBoxLayout;
    wsLayout->addStretch();
    wsLayout->addWidget(wsLabel);
    wsLayout->addWidget(timeframeComboBox);
    wsLayout->addStretch();

    //Area with navigation control components
    QHBoxLayout *playbackLayout = new QHBoxLayout;
    playbackLayout->addWidget(playbackButtons);
    playbackLayout->addWidget(startingPointSlider);

    //Sidebar layout
    QVBoxLayout *sidebarLayout = new QVBoxLayout;
    sidebarLayout->addWidget(getFilesButton);
    sidebarLayout->addWidget(ecgFilesWidget);
    sidebarLayout->addLayout(progressBarLayout);
    sidebarLayout->addLayout(wsLayout);
    sidebarLayout->addWidget(headerTextArea);
    sidebarLayout->addStretch();
    sidebarLayout->addWidget(resetPlotButton);

    //Plot layout
    QVBoxLayout *plotLayout = new QVBoxLayout;
    //plotLayout->addWidget(d_plot);

    for (int ii = 0; ii < 4; ii++) {
        plotLayout->addWidget(d_plots[ii]);
    }

    plotLayout->addLayout(playbackLayout);

    //Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(sidebarLayout, 1);
    mainLayout->addLayout(plotLayout, 9);

    setLayout(mainLayout);
}
