#include "datalogger.h"
#include "settingssingleton.h"
#include <QDebug>
#include <iostream>
#include "ecgstreamobject.h"
#include <QFile>


DataLogger::DataLogger(QObject *parent) : QObject(parent)
{

}

DataLogger::~DataLogger(){

}
/** Saves the information from an EcgStreamObject stored in a DataStream vector
 *
 * lements.
 */
void DataLogger::save(DataStream &input){
    saveAsText(input);

    if  (SettingsSingleton::instance().getSaveAsEdf()){
        saveAsEdf(input);
    }
}
/** Saves the information from a EcgStream object into two textfiles
 * filename.txt and filename_header.txt
 *
 * \todo Modify EcgStream and saveAsText soo that EcgStream specifies what to
 * print and how to print it. saveAsText should take DataStream as input instead making it more reusable.
 *
 *\todo loop through the stream without deleting the elements.
 */
void DataLogger::saveAsText(DataStream &input){


            QFile outFileHeader(SettingsSingleton::instance().getFileName()+"_header.txt");

                if (!outFileHeader.open(QIODevice::WriteOnly | QIODevice::Text)) {
                emit updateStatus("Failed to open data file for write!");
                    std::cerr << "Failed to open header-data file for write!!" << endl;
                } else {
                    QTextStream outHeader(&outFileHeader);

                    outHeader   << "[ECG CAPTURE SETTINGS]\n"
                                << "Filename: " <<      SettingsSingleton::instance().getFileName() << ".txt \n"
                                << "Samples: " <<       QString::number(input.size()) << "\n"
                                << "Duration: " <<      QString::number(input.back().time) << "ms \n"
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
                emit updateStatus("Failed to open data file for write!");
                    std::cerr << "Failed to open data file for write" << std::endl;
                } else {
                    QTextStream out(&outFile);

                emit updateStatus(QString("Writing " + QString::number(input.size()) + " samples to " + SettingsSingleton::instance().getFileName() + "..."));
                    qDebug() << "Writing " << input.size() << " samples to " << SettingsSingleton::instance().getFileName() << "..." << endl;

                    for (int i ; i<input.size();i++){
                           const EcgStreamObject tmp=input.at(i);
                                            out << tmp.toText() << endl; //"\n";


                    }

                emit updateStatus(QString("Samples saved in text format"));
                    std::cerr << "Samples saved in text format" << std::endl;

                    outFile.close();
                }



}
/** Saves the information from a EcgStream object into a EDF-file
 *
 * \bug unimplemented function
 * \todo Implement it
 *
 */
void DataLogger::saveAsEdf(DataStream &input){
    qDebug() << "Save as EDF not implemented yet" << endl;
    updateStatus("Save as EDF not implemented yet");


}
