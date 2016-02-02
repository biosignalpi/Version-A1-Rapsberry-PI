#ifndef SAMPLINGTHREAD_H
#define SAMPLINGTHREAD_H

#include <QPointF>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include "deviceinterface.h"
#include <QElapsedTimer>



class EcgCapture;

/**
 * @addtogroup Device-Facade
 * @{ */

/** \class SamplingThread
 * \brief DeviceInterface Class responsible for sampling ECG
 *
 *
 * \author Martin
 * @author Jonatan
 *
 */
class SamplingThread: public DeviceInterface
{
Q_OBJECT

public:
  //  SamplingThread(QObject *parent = NULL);
    SamplingThread(DataStream& inputStream);
    virtual ~SamplingThread();
    void clearSamples();
    void setSource(int);
    void setFileName(QString);
    void setFileType(QString);
    void startThread();
    virtual void stop();
    virtual void run();

    virtual void getData(DataStream&); ///< Populates DataStream vector with values \todo
    virtual bool connected(); ///<Boolean for check whether the device is connected<\todo Implement function
    virtual void close(); ///< Closes the connection to bcm2835 \todo Implement function

public slots:
    void setChannel(int);

private:

    QVector<QVector<QPointF> > *privateSamples;
    QVector<QVector<double> > *sampleData;

    EcgCapture *ecg;


    int sampleRate;
    int Fs;
    int sourceId;
    int channelId;
    int counter,counterII;
    bool stopThread;
    double prevTime;
    double prevVal;
    double sleepInterval;

    QString fileName;
    QString fileType;
    QElapsedTimer clock;

    /**
     * @brief Samples one frame from EcgCapture
     *
     */
    void sample(double,DataStream&);
    void saveAsText();
    void saveAsBDF();

};

/** @} */

#endif // SAMPLINGTHREAD_H
