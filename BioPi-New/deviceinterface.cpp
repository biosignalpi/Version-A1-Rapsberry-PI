#include "deviceinterface.h"
#include <iostream>
     
    DeviceInterface::DeviceInterface(DataStream& inputStream) : stream(inputStream) {
        //stream=inputStream;
    }
    
    DeviceInterface::~DeviceInterface() {

    }
    void DeviceInterface::init(DataStream& inputStream){
        stream=inputStream;
    }
    void DeviceInterface::sendSampleVectorFunction(QVector<QVector<QPointF> > input){

    	emit sendSampleVector(input);
    }
    	void DeviceInterface::updateStatusFunction(QString input){
    		std::cerr << "updateStatusFunction" << std::endl;
     		emit updateStatus(input);
    	}
