/*
 * plottingwidget.h
 *
 *  Created on: Nov 2, 2015
 *      Author: martin
 */

#ifndef PLOTTINGWIDGET_H_
#define PLOTTINGWIDGET_H_

#include <QWidget>
#include <QListWidget>



class Plot;
class QLabel;
class QProgressBar;
class SliderWidget;
class QComboBox;
class QPushButton;
class QTextEdit;
/**
 * @brief Widget that can read ECG information from file and plots the data.
 * @author Jonatan
 * @author Martin
 * @todo Use the DataLogger instead of loadBigFile for reading data from txt and edf file. This needs to be implemented both in this class and also in the DataLogger Class.
 *
 */
class PlottingWidget : public QWidget
{
    Q_OBJECT

public:
    PlottingWidget(QWidget * = NULL);

protected:
    /**
     * @brief Handles the events triggered by moving the scroll button
     * Catches the event when the mouse is in the widget are and the scroll button is moved.
    * If scrolled away from the user the next methos is triggered and a step forward is made,
    * if scrolled towards the user the prev method is triggered to browse backwards.
     * @param event
     */
    void wheelEvent( QWheelEvent * event );

private:
    /**
     * @brief Setup of the necessary components that is used in the widget
     */
    void setupComponents();
    /**
     * @brief setup actions and signals slots used in the widget
     */
    void setupActions();
    /**
     * @brief setup the Layout of the PlottingWidget
     */
    void setupLayout();

    QListWidget *ecgFilesWidget;
    //Plot *d_plot;
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

    QAction *playAction;
    QAction *pauseAction;
    QAction *nextAction;
    QAction *prevAction;

    QPushButton *getFilesButton;
    QPushButton *resetPlotButton;
    QTextEdit *headerTextArea;

private slots:
    /**
     * @brief Shows the previous frame of the signal
     */
    void prev();
    /**
     * @brief Start the ECG playback
     */
    void play();
    /**
     * @brief Pause the ECG playback
     */
    void pause();
    /**
     * @brief Shows the next frame of the signal
     */
    void next();
    /**
     * @brief Load the supported ECG-formats from the application directory
     * Supported formats:: .txt, .edf, .bdf
     */
    void getEcgFileList();
    /**
     * @brief If a file is double-clicked, load it in another thread to prevent locking the GUI
     */
    void fileSelected(QListWidgetItem*);
    /**
     * @brief Plot the QVector obtained from the initEcg(QVector<QVector<QPointF> > fileData);
     */
    void plotVector();
    /**
     * @brief Init the ECG vector and display the ECG.
     * @param fileData the information from the file processed by loadBigFile()
     */
    void initEcg(QVector<QVector<QPointF> > fileData);
    /**
     * @brief Clear the plot
     */
    void clearPlot();
    /**
     * @brief If the slider for browsing the ecg is moved, update the plot to show the new interval of the ECG.
     */
    void updatePlot(int);
    /**
     * @brief If the window size of the plot is changed, go back to the start and update the plotted interval
     */
    void windowSizeChanged(int);
};



#endif /* PLOTTINGWIDGET_H_ */
