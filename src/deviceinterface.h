/* deviceInterface.h
 *
 *  Created on: Sep 14, 2015
 *      Author: Martin Rostin
 */

#ifndef DEVICEINTERFACE_H_
#define DEVICEINTERFACE_H_

#include <QObject>
#include <QThread>
#include <QPointF>
#include <QString>
#include <QVector>
#include "datastream.h"


/**
 * @addtogroup Device-Facade
 * @{ */

/** \class DeviceInterface
 * \brief Abstract interface for all devices
 *
 * Specifies pure virtual functions that specifies the functionality all devices should have
 *
 *@author Martin
 */
class DeviceInterface:public QThread {
	Q_OBJECT
public:
    DeviceInterface(DataStream& inputStream);
	virtual ~DeviceInterface();

	virtual void getData(DataStream&)=0;
	virtual bool connected()=0;
	virtual void init(DataStream&);
	virtual void close()=0;
	virtual void run()=0;
	virtual void stop()=0;
/*protected slots:
	void sendSampleVectorSlot(QVector<QVector<QPointF> >);
	void updateStatusSlot(QString); */
signals:
	void sendSampleVector(QVector<QVector<QPointF> >);
	void updateStatus(QString);
protected:
    DataStream& stream;
	void updateStatusFunction(QString);
	void sendSampleVectorFunction(QVector<QVector<QPointF> >);


};

/** @} */

#endif /* DEVICEINTERFACE_H_ */
