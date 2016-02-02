#ifndef SETTINGSSINGLETON_H_
#define SETTINGSSINGLETON_H_

#include <QString>
/**
 * @class SettingsSingleton
 * @brief Singleton containing all settings used by the Biosignal PI Framework
 *
 * @author Martin
 * @todo Add verification functions controlling the input.
 */
class SettingsSingleton {
public:
    /**
     * @brief Retrives a reference to the ONE and ONLY SettingsSingleton created for the application.
     * @return[SettingsSingleton&] instance handle to access the member functions for get and set of private variables
     */
    static SettingsSingleton& instance();
    virtual ~SettingsSingleton();
    /**
     * @brief Used to set private variable fileName.
    */
    void setFileName(QString fileName);
    /**
     * @brief Used to set private variable name.
     * @param  name the name to change the private variable to.
     */
    void setName(QString name);

    /**
     * @brief Used to set private variable gender.
     * @param gender the gender to change the private variable to.
     */
    void setGender(QString gender);

    /**
     * @brief Used to set private variable birthDate.
     * @param birthDate the birthDate to change the private variable to.
     */
    void setBirthDate(QString birthDate);

    /**
     * @brief Used to set private variable patientCode.
     * @param patientCode the patientCode to change the private variable to.
     */
    void setPatientCode(QString patientCode);

    /**
     * @brief Used to set private variable recordingName.
     * @param recordingName the recordingName to change the private variable to.
     */
    void setRecordingName(QString recordingName);

    /**
     * @brief Used to set private variable notes.
     * @param notes the notes to change the private variable to.
     */
    void setNotes(QString notes);

    /**
     * @brief Used to set private variable sampleRate.
     * @param sampleRate the sampleRate to change the private variable to.
     */
    void setSampleRate(int sampleRate);

    /**
     * @brief Used to set private QString source.
     * @param source the source to change the private variable to.
     */
    void setSource(QString source);

    /**
     * @brief Used to set private int name.
     * @param sourceId the sourceId to change the private variable to.
     */
    void setSourceId(int sourceId);
    /**
     * @brief Set the private bool saveAsEdf
     * @param  saveAsEdf
     */
    void setSaveAsEdf(bool saveAsEdf);

    /**
     * @brief Returns a QString containing the value from private QString fileName
     * @return fileName
     */
    QString getFileName();
    /**
     * @brief Returns a QString containing the value from private QString name
     * @return name
     */
    QString getName();
    /**
     * @brief Returns a QString containing the value from private QString gender
     * @return gender
     */
    QString getGender();
    /**
     * @brief Returns a QString containing the value from private QString birthDate
     * @return birthDate
     */
    QString getBirthDate();
    /**
     * @brief Returns a QString containing the value from private QString patientCode
     * @return patientCode
     */
    QString getPatientCode();
    /**
     * @brief Returns a QString containing the value from private QString recordingName
     * @return recordingName
     */
    QString getRecordingName();
    /**
     * @brief Returns a QString containing the value from private QString notes
     * @return notes
     */
    QString getNotes();
    /**
     * @brief Returns a int containing the value from private int sampleRate
     * @return sampleRate
     */
    int getSampleRate();
    /**
     * @brief Returns a QString containing the value from private QString source
     * @return source
     */
    QString getSource();
    /**
     * @brief Returns a int containing the value from private int sourceId
     * @return sourceId
     */
    int getSourceId();
    /**
     * @brief Returns the private bool saveAsEdf
     * @return saveAsEdf
     */
    bool getSaveAsEdf();

protected:
    /**
     * @brief Protected constructur called by instance() to create ONE and ONLY ONE SettingsSingleton
     */
    SettingsSingleton();
private:
 //   static SettingsSingleton *_instance;
    SettingsSingleton(SettingsSingleton const&)=delete;
    void operator=(SettingsSingleton const&)=delete;
    QString fileName;
    QString name;
    QString gender;
    QString birthDate;
    QString patientCode;
    QString recordingName;
    QString notes;
    int sampleRate;
    QString source;
    int sourceId;
    bool saveAsEdf;
};
#endif /* SETTINGSSINGLETON_H_ */
