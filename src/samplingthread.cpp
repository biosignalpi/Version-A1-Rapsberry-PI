#include "samplingthread.h"
#include "ecgcapture.h"
#include "settingssingleton.h"
#include <QVector>
#include <QPointF>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QCoreApplication>
//#include <qwt_system_clock.h>
#include <QtMath>
#include "ecgstreamobject.h"
//#include "edflib.h"
//#include "settings.h"

SamplingThread::SamplingThread(DataStream& inputStream):channelId(1), DeviceInterface(inputStream)
{
	privateSamples = new QVector<QVector<QPointF> >;
   //sampleData = new QVector<QVector<double> >;
	ecg = new EcgCapture();
	fileName = "ECG";
	fileType = "text";
}


SamplingThread::~SamplingThread(){
    delete sampleData;
    delete ecg;
    delete privateSamples;
}



void SamplingThread::run()
{
	clock.start();
		prevTime = clock.elapsed();
		startThread();
		emit updateStatus(QString("Collecting samples..."));
		while(!stopThread) {

			double elapsed = clock.elapsed();
            sample(elapsed, stream);

			//If sampling is too fast the sampling thread will need to wait
			//The wait interval is depending on the sampling frequency
			const double usec = (sleepInterval-(clock.elapsed()-elapsed))*1000;

			if (usec>1) {
				usleep(usec);
			}

		}






}

void SamplingThread::stop()
{
	stopThread = true;
}

void SamplingThread::startThread()
{

	QString iniPath = qApp->applicationDirPath() + "/settings.ini";
	QSettings settings(iniPath, QSettings::IniFormat);

	fileName =SettingsSingleton::instance().getFileName();
    sourceId = SettingsSingleton::instance().getSourceId(); //settings.value("/ECGCapture/Source", 0).toInt();
    sampleRate =SettingsSingleton::instance().getSampleRate(); //settings.value("/ECGCapture/SampleRate", 0).toInt();
	counter = 0;
    counterII=0;
	sleepInterval = 0.0;

	qDebug() << "SourceID:" << sourceId  << endl;

	EcgCapture::OperatingMode source;
	EcgCapture::Frequency freq;

	switch (sourceId) {
	case 0:
		source = EcgCapture::ecgCapture;
		break;
	case 1:
		source = EcgCapture::testToneLowFreqSin;
		break;
	case 2:
		source = EcgCapture::testToneHighFreqSin;
		break;
	case 3:
		source = EcgCapture::testToneSquare;
		break;
	default:
		source = EcgCapture::ecgCapture;
		break;
	}

	switch (sampleRate) {
	case 0:
		freq = EcgCapture::lowFreq;
		sleepInterval = 1.70;
		Fs = 500;
		break;
	case 1:
		freq = EcgCapture::midFreq;
		sleepInterval = 0.70;
		Fs = 1000;
		break;
	case 2:
		freq = EcgCapture::highFreq;
		sleepInterval = 0.0;
		Fs = 2000;
		break;
	default:
		freq = EcgCapture::midFreq;
		sleepInterval = 0.70;
		Fs = 1000;
		break;
	}

    ecg->init(source, freq);
    ecg->start();
    stopThread=false;


}


void SamplingThread::clearSamples()
{
	privateSamples->clear();
}

void SamplingThread::setChannel(int channel)
{

	channelId = channel;
}

void SamplingThread::setSource(int source)
{
	sourceId = source;
}

void SamplingThread::setFileName(QString fname)
{
	if (fname != "") {
		fileName = fname;
	}
}

void SamplingThread::setFileType(QString ftype)
{
	if (ftype == "text") {
		fileType = "text";
	} else if (ftype == "bdf") {
		fileType = "bdf";
	}
}

/**
 * Saves the collected data as a text file.
 * @deprecated not used
 */
void SamplingThread::saveAsText()
{
	/*    QFile outFileHeader(fileName+"_header.txt");

    if (!outFileHeader.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit updateStatus("Failed to open data file for write!");
    } else {
        QTextStream outHeader(&outFileHeader);

        outHeader   << "[ECG CAPTURE SETTINGS]\n"
                    << "Filename: " <<      Settings::instance().getFilename() << ".txt \n"
                    << "Samples: " <<       QString::number(sampleData->length()) << "\n"
                    << "Duration: " <<      QString::number(sampleData->last().at(0)) << "ms \n"
                    << "Sample rate: " <<   QString::number(Settings::instance().getSampleRate()) << " Hz\n"
                    << "Source: "  <<       Settings::instance().getSource() << "\n"
                    << "\n[RECORDING INFORMATION]\n"
                    << "Recording name: " <<    Settings::instance().getRecordingName() << "\n"
                    << "Patient code: " <<      Settings::instance().getPatientCode() << "\n"
                    << "Name: " <<              Settings::instance().getName() << "\n"
                    << "Gender: " <<            Settings::instance().getGender() << "\n"
                    << "Birthdate: " <<         Settings::instance().getBirthDate() << "\n"
                    << "Notes: " <<             Settings::instance().getNotes() << "\n";

        outFileHeader.close();

    }

    QFile outFile(fileName+".txt");

    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit updateStatus("Failed to open data file for write!");
    } else {
        QTextStream out(&outFile);

        emit updateStatus(QString("Writing " + QString::number(sampleData->length()) + " samples to " + fileName + "..."));

        for (int ii =0; ii < sampleData->length(); ii++) {
            out << QString::number(sampleData->at(ii).at(0)) << "\t"
                << QString::number(sampleData->at(ii).at(1)) << "\t"
                << QString::number(sampleData->at(ii).at(2)) << "\t"
                << QString::number(sampleData->at(ii).at(3)) << "\t"
                << QString::number(sampleData->at(ii).at(4)) << "\n";
        }

        emit updateStatus(QString("Samples saved in text format"));

        outFile.close();
    }
	 */
}

/*!
 * Saves the collected data as a BDF file.
 * @deprecated not used
 */
void SamplingThread::saveAsBDF()
{ /*
    emit updateStatus(QString("Saving as BDF file..."));

    int nseconds = static_cast<int>(sampleData->last().at(0)/1000);
    int smpfreq = Fs;

    if (sampleData->length() < nseconds*smpfreq)
    {
        emit updateStatus("Error: too many samples missing!");
    } else {
        int i, j, k,
                hdl,
                chns;

        double buf[smpfreq];

        //QString tmp = fileName+".bdf";
        QString tmp = fileName+".edf";

        //Convert the filename to the correct format
        const char* fname = tmp.toLocal8Bit().data();

        chns = 4;

        //Open the file for write
        //hdl = edfopen_file_writeonly(fname, EDFLIB_FILETYPE_BDFPLUS, chns);
        hdl = edfopen_file_writeonly(fname, EDFLIB_FILETYPE_EDFPLUS, chns);

        //All channels have the same sampling frequency
        for (i=0; i<chns; i++) {
            edf_set_samplefrequency(hdl, i, smpfreq);
        }

//        for (i=0; i<chns; i++) {
//            edf_set_physical_maximum(hdl, i, 3.0);
//        }

//        for (i=0; i<chns; i++) {
//            edf_set_digital_maximum(hdl, i, 8388607);
//        }

//        for (i=0; i<chns; i++) {
//            edf_set_digital_minimum(hdl, i, -8388607);
//        }

//        for (i=0; i<chns; i++) {
//            edf_set_physical_minimum(hdl, i, -3.0);
//        }

        for (i=0; i<chns; i++) {
            edf_set_physical_maximum(hdl, i, 1);
        }

        for (i=0; i<chns; i++) {
            edf_set_digital_maximum(hdl, i, 32767);
        }

        for (i=0; i<chns; i++) {
            edf_set_digital_minimum(hdl, i, -32768);
        }

        for (i=0; i<chns; i++) {
            edf_set_physical_minimum(hdl, i, -1);
        }

        edf_set_label(hdl, 0, "Lead I");
        edf_set_label(hdl, 1, "Lead II");
        edf_set_label(hdl, 2, "Lead III");
        edf_set_label(hdl, 3, "Respiration");

        for (i=0; i<chns; i++) {
            edf_set_physical_dimension(hdl, i, "V");
        }

        //Data is written in blocks of 1s each
        for (j=0; j<nseconds; j++) {
            for (k=1; k<=chns; k++) {
                for (i=0; i<smpfreq; i++) {
                    buf[i] = sampleData->at(i+(j*smpfreq)).at(k);
                }
                edfwrite_physical_samples(hdl, buf);
            }
        }

        edfclose_file(hdl);

        emit updateStatus(QString("Samples saved in BDF format..."));
    }
 */
}


/**
 * Collects a single sample and emits samples to the plot if enough samples is
 * collected.
 *
 *
 * FRAME FORMAT:
    ELAPSED (ms) | LEAD 1 | LEAD 2 | LEAD 3 | RESPIRATION | LEAD OFF DETECTION
    Lead off: 1 = leads disconnected, 0 = leads connected

 */
void SamplingThread::sample(double elapsed,DataStream& inputStream){

	// FRAME FORMAT:
	//ELAPSED (ms) | LEAD 1 | LEAD 2 | LEAD 3 | RESPIRATION | LEAD OFF DETECTION
	//Lead off: 1 = leads disconnected, 0 = leads connected

	QVector<double> frame;
	frame.append(elapsed);
    frame << ecg->readFrame();
    //double y = frame.at(channelId);
	static double lead1, lead2, lead3, respiration;
	static bool userNotified = false;

	if (sourceId == 0) {
		//If lead is disconnected, notify
		if (frame[5] == 1) {
			if (!userNotified) {
				userNotified = true;
				emit updateStatus("Leads disconnected");
			}
		}
	}

    lead1 += frame.at(1);
	lead2 += frame.at(2);
	lead3 += frame.at(3);
	respiration += frame.at(4);

    inputStream.append(EcgStreamObject(frame.at(1), frame.at(2),frame.at(3), frame.at(4),elapsed/1000));

	counter++;


	if (counter >= 10) {
		QVector<QPointF> tmp;
		tmp << QPointF(elapsed/1000,lead1/10) << QPointF(elapsed/1000,lead2/10) << QPointF(elapsed/1000,lead3/10) << QPointF(elapsed/1000, respiration/10);

		privateSamples->append(tmp);
		tmp.clear();

		counter = 0;
		lead1 = 0.0;
		lead2 = 0.0;
		lead3 = 0.0;
		respiration = 0.0;
	}

	if (privateSamples->size() >= 20) {
		QVector<QVector<QPointF> > sampleVector = *privateSamples;

        privateSamples->clear();
        emit sendSampleVector(sampleVector);

	}

}


/**
 *
 * @deprecated Not used
 */
void SamplingThread::getData(DataStream& inputStream){
	clock.start();
	prevTime = clock.elapsed();
	startThread();
    for (int ii=0; ii<30000 ;ii++) {

		double elapsed = clock.elapsed();
		sample(elapsed, inputStream);

		//If sampling is too fast the sampling thread will need to wait
		//The wait interval is depending on the sampling frequency
		const double usec = (sleepInterval-(clock.elapsed()-elapsed))*1000;

		if (usec>1) {
			usleep(usec);
			qDebug() << "sleep" << usec  << endl;

		}

	}

}

/**
 * @brief SamplingThread::connected
 * @todo Implement
 * @return
 */
bool SamplingThread::connected() {
    return true;
}
/**
 * @brief SamplingThread::close
 * @todo Implement
 */
void SamplingThread::close() {

}
