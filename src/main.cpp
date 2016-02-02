#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include <QStyleFactory>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    qApp->setStyle(QStyleFactory::create("Fusion"));
	qRegisterMetaType< QVector<QPointF> >("QVector<QPointF>");
	qRegisterMetaType< QPointF >("QPointF");
    qRegisterMetaType< QVector< double> >("QVector<double>");
	qRegisterMetaType< QVector<QVector<QPointF> > >("QVector<QVector<QPointF> >");
    MainWindow w;
    w.setFixedSize(800,700);  //Needed for using the Biosignal PI with Linux Mint and Ubuntu the Window will resize unexpectedly otherwise
    w.show();
    return a.exec();
}
