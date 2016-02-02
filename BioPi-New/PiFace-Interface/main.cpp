#include <iostream>
#include <QCoreApplication>
#include <QVector>
#include <QPointF>
#include <QTimer>
#include <QDebug>
#include <stdio.h>
#include "pifacecontrolandview.h"
#include "pifacecad.h"



bool piFaceConnected(int i){
    if (i<2)
        return false;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qRegisterMetaType< QVector<QPointF> >("QVector<QPointF>");
    qRegisterMetaType< QPointF >("QPointF");
    qRegisterMetaType< QVector<QVector<QPointF> > >("QVector<QVector<QPointF> >");

    if (pifacecad_open()>=0){    // if no PiFace is connected the pifacecad_open will return -1
        PiFaceControlAndView *piFaceViewAndControl=new PiFaceControlAndView(&a);

        QObject::connect(piFaceViewAndControl, SIGNAL(finished()), &a, SLOT(quit()));
        QTimer::singleShot(0,piFaceViewAndControl, SLOT(run()));

    }
    else{
       qDebug() << "No PiFaceConnected, (provide input argument) " << endl;
       return 1;
    }

    return a.exec();

}



