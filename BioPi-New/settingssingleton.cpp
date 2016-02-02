#include <settingssingleton.h>

SettingsSingleton::SettingsSingleton() {

    fileName="default";
    name="";
    gender="";
    birthDate="";
    patientCode="";
    recordingName="";
    notes="";
    sampleRate=500;
    source="";
    sourceId=4;
    saveAsEdf=false;

}

SettingsSingleton::~SettingsSingleton() {

}

SettingsSingleton& SettingsSingleton::instance(){
    static SettingsSingleton _instance;
    return _instance;
}

void SettingsSingleton::setFileName(QString input){
	fileName=input;
}
    void SettingsSingleton::setName(QString input){
    	name=input;
    }
    void SettingsSingleton::setGender(QString input){
    	gender=input;
    }
    void SettingsSingleton::setBirthDate(QString input){
    	birthDate=input;
    }
    void SettingsSingleton::setPatientCode(QString input){
    	patientCode=input;
    }
    void SettingsSingleton::setRecordingName(QString input){
    	recordingName=input;
    }
    void SettingsSingleton::setNotes(QString input){
    	notes=input;
    }
    void SettingsSingleton::setSampleRate(int input){
    	sampleRate=input;
    }
    void SettingsSingleton::setSource(QString input){
    	source=input;
    }
    void SettingsSingleton::setSourceId(int input){
        sourceId=input;
    }
    void SettingsSingleton::setSaveAsEdf(bool input){
    	saveAsEdf=input;
    }

    QString SettingsSingleton::getFileName(){
    	return fileName;
    }
    QString SettingsSingleton::getName(){
    	return name;
    }
    QString SettingsSingleton::getGender(){
    	return gender;
    }
    QString SettingsSingleton::getBirthDate(){
    	return birthDate;
    }
    QString SettingsSingleton::getPatientCode(){
    	return patientCode;
    }
    QString SettingsSingleton::getRecordingName(){
    	return recordingName;
    }
    QString SettingsSingleton::getNotes(){
    	return notes;
    }
    int SettingsSingleton::getSampleRate(){
    	return sampleRate;
    }
    QString SettingsSingleton::getSource(){
    	return source;
    }
    int SettingsSingleton::getSourceId(){
        return sourceId;
    }
    bool SettingsSingleton::getSaveAsEdf(){
    	return saveAsEdf;
    }
