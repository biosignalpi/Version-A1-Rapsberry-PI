/*
 * saveastext.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: martin
 */

#include "saveastext.h"
#include "settingssingleton.h"
#include "ecgstruct4.h"
#include <QFile>
#include <iostream>
#include <QString>
#include <QtCore>
#include <QtDebug>








void saveAsText(EcgStream & inputStream){
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
	        qDebug() << "Writing " << inputStream.getSize() << " samples to " << SettingsSingleton::instance().getFileName() << "..." << endl;
	        while (!inputStream.empty()){
//	            out << QString::number(sampleData->at(ii).at(0)) << "\t"
//	                << QString::number(sampleData->at(ii).at(1)) << "\t"
//	                << QString::number(sampleData->at(ii).at(2)) << "\t"
//	                << QString::number(sampleData->at(ii).at(3)) << "\t"
	            out << QString::number(inputStream.getData()) << "\n";
	        }

//	        emit updateStatus(QString("Samples saved in text format"));
	        std::cerr << "Samples saved in text format" << std::endl;

	        outFile.close();
	    }
}





void saveAsText(EcgStream_four & input)
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
	        			out << QString::number(tmp.time)
	        				<< QString::number(tmp.frame1)
	        			<< QString::number(tmp.frame2)
	        			<< QString::number(tmp.frame3)
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



