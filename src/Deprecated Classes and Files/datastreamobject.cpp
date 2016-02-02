#include "datastreamobject.h"

DataStreamObject::DataStreamObject()
{

}

QString DataStreamObject::toText() const{
    return QString::number(time);
}
DataStreamObject::~DataStreamObject(){

}
