#ifndef ECGCAPTURE_H
#define ECGCAPTURE_H

#include <QObject>
#include <QVector>
#include <QPointF>

/**
 * @addtogroup Device-Facade
 * @{ */

/** \class EcgCapture
 * \brief Responsible for communication with ADAS
 *
 * EcgCapture is the main class responsible for communication with the ADAS1000.
 * It uses the BCM2835.h library for access to the GPIO pins of RPI
 *
 *
 * \todo Move all function descriptions from the .cpp file to the headerfile (.h file)
 * \author Jonathan
 * \author Martin
 * \bug Crashes with a QVector index out of range. Problem caused by the readFrame function when it dosent provide a array with at least 5 elements
*/
class EcgCapture: QObject
{
    Q_OBJECT

public:

    enum OperatingMode {
        ecgCapture,
        testToneSquare,
        testToneLowFreqSin,
        testToneHighFreqSin
    };

    enum Frequency {
        lowFreq,
        midFreq,
        highFreq
    };

    enum leadFormat {
        digital,
        electrode
    };

    EcgCapture();
    /**
     * @brief  Initiate the device by configuring the registers depending on operating mode and
 * sampling frequency.
 *
 * @param[in] OperatingMode enum stating which operating mode to use
 * @param[in] Frequency enum stating the which frequency to sample in
 *
 */
    void init(OperatingMode, Frequency);
    /**
     * @brief Start capturing frames from the ADAS1000
     */
    void start();
    /**
     * @brief stop capture
     * \todo Implement
     *
     */
    void stop();
    void testDevice();

    const QVector<double> readFrame();

private:
    void spiInit();
    void csEnable();
    void csDisable();
    void enableRegisterWrite();
    bool setReg(QByteArray);
    double ecgVoltageConversion(int ADCDecimal, leadFormat format);
    double respVoltageConversion(int);

    int test;
    OperatingMode mode;
    leadFormat leadMode;
    QVector<QPointF> privateSamples;
};
/** @ } */

#endif // ECGCAPTURE_H
