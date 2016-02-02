#include "ecgstreamobject.h"

EcgStreamObject::EcgStreamObject()
{

}

EcgStreamObject::EcgStreamObject(double _frame1, double _frame2, double _frame3, double _resp, double _time)
    : frame1(_frame1),frame2(_frame2),frame3(_frame3),time(_time),resp(_resp){

}

QString EcgStreamObject::toText() const{
    QString tmp=QString::number(time) + "\t" + QString::number(frame1) + "\t"
                      +QString::number(frame2) + "\t"
                       + QString::number(frame3) + "\t"
                        + QString::number(resp);
    return tmp;
}
EcgStreamObject::~EcgStreamObject(){

}
