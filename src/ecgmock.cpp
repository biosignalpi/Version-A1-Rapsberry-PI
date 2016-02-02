/*
     * ECGmock.cpp
     *
     *  Created on: Sep 14, 2015
     *      Author: Martin Rostin
     */

#include "ecgmock.h"
#include <iostream>
#include <math.h>
#include <QDebug>
#include "ecgstreamobject.h"


EcgMock::EcgMock(DataStream& inputStream): DeviceInterface(inputStream) {
    init();
}

EcgMock::~EcgMock() {
    close();
}
/**
 *
 * @deprecated old function, not used
 * @param DataStream &
 *
 */
void EcgMock::getData(DataStream& inputStream){
    int _sizeArray=2000;
    updateStatus(QString("EcgMock::GetData"));
    int _angle=0;

    for (int i=0;i<_sizeArray;i++){
        // 	EcgStruct4 tmp=EcgStruct4(cnt++,cnt++,cnt++,cnt++,cnt++);
        stream.push_back(EcgStreamObject(sin(_angle*PI/180),cos(_angle*PI/180),tan(_angle*PI/180),sin(_angle*2*PI/180),_angle*PI/180));
        if(_angle>360){
            _angle-=360;
        }
        _angle+=6;
        /*      std::cerr << tmp.time << "  " << tmp.frame1 << "  " << tmp.frame1
                << "  " << tmp.frame2
                << "  " << tmp.frame3
                <<std::endl; */
    }
    return;
}
void EcgMock::run(){
    double counter,counter2=0;
    double cosinus,angle,sinus,sinus2x,tangens=0.0;
    double _angle=0;
    condition=true;
    emit updateStatus(QString("EcgMock Started"));
    while(condition) {
        stream.append(EcgStreamObject(sin(_angle*PI/180),cos(_angle*PI/180),tan(_angle*PI/180),sin(_angle*2*PI/180),_angle*PI/180));
        if(counter2>100){
            counter2=0;
            msleep(200);
        }
        angle+=_angle;
        cosinus+=cos(_angle*PI/180);
        sinus2x+=sin(_angle*2*PI/180);
        sinus+=sin(_angle*PI/180);
        tangens+=tan(_angle*PI/180);
        _angle+=0.2;
        counter++;
        counter2++;


        if (counter >= 10) {
            QVector<QPointF> tmp;
            double time=(_angle)*PI/1800;
            tmp << QPointF(time,sinus/10) << QPointF(time,cosinus/10) << QPointF(time,tangens/10) << QPointF(time,sinus2x/10);
            //privateSamples->append(QPointF(elapsed/1000,lead1/10));
            privateSamples->append(tmp);
            tmp.clear();

            angle = 0;
            sinus = 0.0;
            cosinus = 0.0;
            tangens = 0.0;
            sinus2x = 0.0;
            counter=0.0;
        }

        if (privateSamples->size() >= 20) {
            QVector<QVector<QPointF> > sampleVector = *privateSamples;
            emit sendSampleVector(sampleVector);
            privateSamples->clear();


        }
    }
}
void EcgMock::stop(){
    condition=false;
}


bool EcgMock::connected(){

    return state;
}
void  EcgMock::reconnect(){
    if (!state)
        init();
}
void  EcgMock::close(){
    state=false;
    delete privateSamples;
    delete sampleData;
}

void EcgMock::init(){
    state=true;
    privateSamples = new QVector<QVector<QPointF> >;
    sampleData = new QVector<QVector<double> >;
}
