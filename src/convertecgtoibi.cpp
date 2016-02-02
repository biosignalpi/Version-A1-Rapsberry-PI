/*
 * convertecgtoibi.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: martin
 */

#include "libFiles/QRSDET.H"
#include "libFiles/QRSFILT.CPP"

#include "convertecgtoibi.h"
#include <QThread>
#include <QString>
#include <QVector>
#include <QPointF>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>
#include <iostream>


ConvertEcgToIbi::ConvertEcgToIbi(QString fileName, QObject *parent):
QThread( parent )
{
    fname = fileName;


}

/*
 * Load the file with chosen filename and emit the signal sendFileData() when the file is read.
 */
void ConvertEcgToIbi::run()
{
	QFile myFile(fname);
	if (myFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		time.start();
		QTextStream ecgInfo(&myFile);
		QVector<int > ecgVals;
        QVector<double> timeData;
		int iterations;
		if (!ecgInfo.atEnd()) {
			QString strVals = ecgInfo.readLine();
			ecgInfo.readLine();
			ecgInfo.readLine();
			double tmp;
			int i=0;
			while (!ecgInfo.atEnd()) {

				strVals = ecgInfo.readLine();
				QStringList strPieces = strVals.split(QRegularExpression("\\s+"));


				if (strPieces.length()==4) {
                    tmp=strPieces[2].toDouble();
                    ecgVals.append((tmp*500)); ///< @todo normalize input to work with more files

				}
				else if (strPieces.length()==3) {
                                    tmp=strPieces[2].toDouble();
                                    ecgVals.append((tmp*500));
                                                    }
				else if (strPieces.length()==5){

					tmp=strPieces[2].toDouble();
                    ecgVals.append((tmp*500));
                    }
				else {
					std::cerr << "Wrong File" << std::endl;
					return;
				}
				i++;
                }
            QVector<double> qrsPeaks;
			extractRtoR(&ecgVals, &qrsPeaks);
            qrsPeaks.takeFirst();// Remove the influense of the QRS-detectors learning period
            qrsPeaks.takeFirst();// Remove the influense of the QRS-detectors learning period
            qrsPeaks.takeFirst();// Remove the influense of the QRS-detectors learning period
            tmp=0;
            for (int i; i<qrsPeaks.length(); i++){
                tmp=tmp+(qrsPeaks.at(i));
                timeData.append(tmp);
            }
            if (qrsPeaks.length()>10){   ///@todo FIX this check neater
                emit sendFileData(qrsPeaks,timeData);
                saveAsIbiFile(&qrsPeaks);
            }
            else
                std::cerr << "Not enough R peaks detected" << std::endl;
            qDebug("Time elapsed: %d ms", time.elapsed());

		}
		ecgInfo.flush();
		myFile.close();



	}

}

void ConvertEcgToIbi::extractRtoR(QVector<int>* input, QVector<double>* output) {

	output->append(QRSDet(input->takeFirst(),1));
	double tmpQrs=0;
	double count=0;
	while (!input->empty()) {
		tmpQrs=QRSDet(input->takeFirst(),0);
		if (tmpQrs==0){
            count=count+1000/sampRate;
		}
		else {
            output->append((count+1000/sampRate)/1000);
			count=0;
		}



	}
}
void ConvertEcgToIbi::saveAsIbiFile(QVector<double>* input){
	std::cerr << input->length() <<std::endl;
	QFile outFile(fname + "_RR.txt");

		    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {

		        std::cerr << "Failed to open data file for write" << std::endl;
		    } else {
		        QTextStream out(&outFile);
		        double time=0,tmp=0;
		        qDebug() << "Writing " << input->length() << " samples to " << fname << "..." << endl;

		        out <<"Length:" << "\t" << QString::number(input->length()) << "\n";
                out <<"[s]" << "\t" << "[s]" << "\n";
		        while (!input->empty()){
                    tmp=input->takeFirst();
                  //  tmp=tmp/1000;
                out << QString::number(time, 'f', 3) << "\t"
		            		<< QString::number(tmp, 'f', 3) << "\n";
		            time+=tmp;
		        }

		        std::cerr << "Samples saved in text format" << std::endl;
		        outFile.close();
		    }
}



