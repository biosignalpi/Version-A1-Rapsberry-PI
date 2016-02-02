#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "datastream.h"

#include "deviceinterface.h"
#include "ecgmock.h"
#include "samplingthread.h"
#include <QThread>

/**
 * @addtogroup Device-Facade
 * @brief Module responsible for all connection to the BioMedical Devices used
 * @author Martin
 * @{ */

/** \class DeviceManager
 * \brief Handles which device to connect through the DeviceInterface
 *  @author Martin
 *
 *
*/
class DeviceManager : public QThread
{
	Q_OBJECT
public:
    DeviceManager();
    ~DeviceManager();
    void collectData(DataStream&); ///< Collects data from the connected device @deprecated
    void startCapture(); ///< Starts the initiated device through a call to start()
    void stop(); ///< Stops the running device  @todo use connected() before execution
    void init(int, DataStream&); ///< Prepares a new data-collection, @param deviceNumber Which device to connect @param outputStream DataStream to store the collected values in.
    DeviceInterface* device; ///< The connected device

public slots:
    void receiveSampleVector(QVector<QVector<QPointF> >);  ///< Slot used to transfer sendSampleVector from initiated device to the local signal
    void receiveStatus(QString);  ///< Slot used to transfer updateStatus from initiated device to the local signal
signals:
    void sendSampleVector(QVector<QVector<QPointF> >); ///< Sends a QVector that can be used for a GUI to plot in "Real-time"
    void updateStatus(QString);  ///< Information signal for updating status about progress
private:
     bool connected(); ///< Checks whether the device is connected
         void close(); ///< Closes the connection to the device, frees device soo that it can be connected to a new DeviceInterface \todo Implement it

};
/** @} */

#endif // DEVICEMANAGER_H


