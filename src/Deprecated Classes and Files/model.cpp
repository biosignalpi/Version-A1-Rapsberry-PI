#include "model.h"
#include <stdio.h>
#include <iostream>
#include <QDebug>

#include <chrono>
#include <thread>
//#include "saveastext.h"


using namespace std;

Model::Model()
{
    init(1);
}

void Model::init(int i){
	device=new DeviceManager();
	stream=new EcgStream_four();
	stream2=new EcgStream_four();
    logger=new DataLogger();
}
Model::~Model(){

	delete device;
	delete stream;
	delete stream2;
    delete logger;
}
void Model::sampleData() {
	device->init(1, *stream);
	QThread *sampleT = new QThread;
	device->moveToThread(sampleT);
    device->start();
//   stream->transferValues(*stream2);
	//  int _sizeArray=stream->sizeValues;
	//       for (int i=0;i<_sizeArray;i++){
	//           stream->values[i]=18;
	//       }
 //   device->close();

}

void Model::stopSampling() {
	device->stop();
	stream->getSize();
	stream->transferValues(*stream2);
}
void Model::test(){
	bool condition=true;
	int cnt=0;
//	while (condition) {
        device->init(1, *stream);
		device->collectData(*stream);
		stream->transferValues(*stream2);


	//	this->print();
	//	if (++cnt>5) {
	//		condition=false;
	//	}  }
//	}
        logger->save(*stream2);
    //    device->close();

}
void Model::print(){
	int _sizeArray=stream2->getSize();

	while (!stream2->empty()){
		EcgStruct4 tmp=stream2->getDataD();
		cerr << tmp.time
				<< "  " << tmp.frame1
				<< "  " << tmp.frame2
				<< "  " << tmp.frame3
				<< "  " << tmp.frame4 <<endl;
	}
}
/** Saves the information from a EcgStream object into two textfiles
 * filename.txt and filename_header.txt
 *
 * \todo Modify EcgStream and saveAsText soo that EcgStream specifies what to
 * print and how to print it. saveAsText should take DataStream as input instead making it more reusable.
 *
 *
 */
void Model::saveAsText(EcgStream_four & input)
{
//	EcgStream_four& input=*inputStream;
	QFile outFileHeader(SettingsSingleton::instance().getFileName()+"_header.txt");

	    if (!outFileHeader.open(QIODevice::WriteOnly | QIODevice::Text)) {
//	        emit updateStatus("Failed to open data file for write!");
	    	std::cerr << "Failed to open header-data file for write!!" << endl;
	    } else {
	        QTextStream outHeader(&outFileHeader);

	        outHeader   << "[ECG CAPTURE SETTINGS]\n"
	                    << "Filename: " <<      SettingsSingleton::instance().getFileName() << ".txt \n"
	        //            << "Samples: " <<       QString::number(sampleData->length()) << "\n"
	        //            << "Duration: " <<      QString::number(sampleData->last().at(0)) << "ms \n"
	                    << "Sample rate: " <<   QString::number(SettingsSingleton::instance().getSampleRate()) << " Hz\n"
	                    << "Source: "  <<       SettingsSingleton::instance().getSource() << "\n"
	                    << "\n[RECORDING INFORMATION]\n"
	                    << "Recording name: " <<    SettingsSingleton::instance().getRecordingName() << "\n"
	                    << "Patient code: " <<      SettingsSingleton::instance().getPatientCode() << "\n"
	                    << "Name: " <<              SettingsSingleton::instance().getName() << "\n"
	                    << "Gender: " <<            SettingsSingleton::instance().getGender() << "\n"
	                    << "Birthdate: " <<         SettingsSingleton::instance().getBirthDate() << "\n"
	                    << "Notes: " <<             SettingsSingleton::instance().getNotes() << "\n";

	        outFileHeader.close();

	    }

	    QFile outFile(SettingsSingleton::instance().getFileName() + ".txt");

	    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
//	        emit updateStatus("Failed to open data file for write!");
	        std::cerr << "Failed to open data file for write" << std::endl;
	    } else {
	        QTextStream out(&outFile);

//	        emit updateStatus(QString("Writing " + QString::number(sampleData->length()) + " samples to " + fileName + "..."));
	        qDebug() << "Writing " << input.getSize() << " samples to " << SettingsSingleton::instance().getFileName() << "..." << endl;
	        while (!input.empty()){
	        	EcgStruct4 tmp=input.getDataD();
	        			out << QString::number(tmp.time) << "\t"
	        				<< QString::number(tmp.frame1) << "\t"
	        			<< QString::number(tmp.frame2) << "\t"
	        			<< QString::number(tmp.frame3) << "\t"
	        			<< QString::number(tmp.frame4) << "\n";

//	            out << QString::number(sampleData->at(ii).at(0)) << "\t"
//	                << QString::number(sampleData->at(ii).at(1)) << "\t"
//	                << QString::number(sampleData->at(ii).at(2)) << "\t"
//	                << QString::number(sampleData->at(ii).at(3)) << "\t"
	        //    out << QString::number(inputStream.getData()) << "\n";
	        }

//	        emit updateStatus(QString("Samples saved in text format"));
	        std::cerr << "Samples saved in text format" << std::endl;

	        outFile.close();
	    }
}
