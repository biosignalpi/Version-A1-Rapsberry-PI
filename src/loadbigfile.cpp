#include "loadbigfile.h"
#include <QThread>
#include <QString>
#include <QVector>
#include <QPointF>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

/*
 * Class used to load a big .txt file in a new thread
 */
LoadBigFile::LoadBigFile(QString fileName, QObject *parent):
QThread( parent )
{
	fname = fileName;
	decimateFlag = true;
}

/**
 * Load the file with chosen filename and emit the signal sendFileData() when the file is read.
 */
void LoadBigFile::run()
{
	QFile myFile(fname);
	if (myFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream ecgInfo(&myFile);
		QVector<QVector<QPointF> > ecgVals;
		int iterations;
		if (!ecgInfo.atEnd()) {
			QString strVals = ecgInfo.readLine();
			while (!ecgInfo.atEnd()) {
				strVals = ecgInfo.readLine();
				QStringList strPieces = strVals.split(QRegularExpression("\\s+"));

				if (strPieces.length()==5) {
					//                double x = 0.0, y = 0.0;
					//                x = strPieces[0].toDouble();
					//                y = strPieces[1].toDouble();

					double elapsed = strPieces[0].toDouble();
					//    elapsed = elapsed/5;

					QVector<QPointF> tmp;
					tmp << QPointF(elapsed, strPieces[1].toDouble())
                    				<< QPointF(elapsed, strPieces[2].toDouble())
									<< QPointF(elapsed, strPieces[3].toDouble())
									<< QPointF(elapsed, strPieces[4].toDouble());

					//                ecgVals.append(QPointF(x/1000,y));
					ecgVals.append(tmp);
					tmp.clear();
				}
				else if (strPieces.length()==4){
					QVector<QPointF> tmp;
					tmp << QPointF(iterations/1000, strPieces[0].toDouble())
            	                    				<< QPointF(iterations/1000, strPieces[1].toDouble())
													<< QPointF(iterations/1000, strPieces[2].toDouble())
													<< QPointF(iterations/1000, strPieces[3].toDouble());

					//                ecgVals.append(QPointF(x/1000,y));
					iterations++;
					ecgVals.append(tmp);
					tmp.clear();
				}

				//    for (int ii=0; ii<=8; ii++) {
				//        ecgInfo.readLine();
				//    }
			}
		}
		ecgInfo.flush();
		myFile.close();

		if (decimateFlag) {
			decimate();
		}

		emit sendFileData(ecgVals);
	}
}

void LoadBigFile::decimate()
{
	//TODO
}
