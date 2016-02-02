
#include <samplingthread.h>
#include "devicemanager.h"
#include "settingssingleton.h"

#include <QDebug>



DeviceManager::DeviceManager(): device(NULL){



}

DeviceManager::~DeviceManager(){
    delete device;
}
void DeviceManager::close(){
    delete device;
    device=NULL;

}

	void DeviceManager::receiveSampleVector(QVector<QVector<QPointF> > input){

		emit sendSampleVector(input);
	}
    void DeviceManager::receiveStatus(QString input){
    	emit updateStatus(input);
    }

void DeviceManager::collectData(DataStream& stream){
//    while(device->connected()) {
		device->init(stream);
    	device->getData(stream);

//    }
    return;
}

void DeviceManager::startCapture(){


		device->start();
		emit updateStatus("Device Started");
}

void DeviceManager::stop(){
	device->stop();
}

void DeviceManager::init(int deviceNumber, DataStream& inputStream){
    deviceNumber=SettingsSingleton::instance().getSourceId();
    if (device!=NULL)
        close();
    if (deviceNumber==4) {
        device=new EcgMock(inputStream);

    }else  {
        device=new SamplingThread(inputStream);

    }
    QThread *sampleT = new QThread;
    device->moveToThread(sampleT);
    //device->init(inputStream);
    connect(device, SIGNAL(updateStatus(QString)), this, SLOT(receiveStatus(QString)),Qt::QueuedConnection);
    connect(device, SIGNAL(sendSampleVector(QVector<QVector<QPointF> >)), this, SLOT(receiveSampleVector(QVector<QVector<QPointF> >)),Qt::QueuedConnection);


}

bool DeviceManager::connected(){
    bool state;
    return state;
}
