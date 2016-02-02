#include "settingswidget.h"
#include <QtWidgets>
#include <QSettings>
#include <QDebug>
#include "settingssingleton.h"



SettingsWidget::SettingsWidget(QWidget *parent):
    QWidget( parent )
{
    setupComponents();
    setupActions();
    setupLayout();
}

/**
 * Source changed, update ini-file accordingly
 */
void SettingsWidget::sourceChanged(int id)
{
    if ((id >= 0) && (id < 5)) {
        QSettings settings(iniPath, QSettings::IniFormat);
        settings.setValue("ECGCapture/Source", id);
    }

    SettingsSingleton::instance().setSource(idToSource(id));
    SettingsSingleton::instance().setSourceId(id);

}

/**
 * Sample rate was changed, update the ini-file accordingly.
 */
void SettingsWidget::sampleRateChanged(int id)
{
    if ((id >= 0) && (id < 3)) {
        QSettings settings(iniPath, QSettings::IniFormat);
        settings.setValue("ECGCapture/SampleRate", id);

        SettingsSingleton::instance().setSampleRate(idToSampleRate(id));
    }
}

int SettingsWidget::idToSampleRate(int id)
{
    int fs;

    if ((id >= 0) && (id < 3)) {
        switch (id) {
        case 0:
            fs = 500;
            break;
        case 1:
            fs = 1000;
            break;
        case 2:
            fs = 2000;
            break;
        default:
            fs = -1;
            break;
        }
    }

    return fs;
}

QString SettingsWidget::idToSource(int id)
{
    QString source = "";

 //   if ((id >= 0) && (id < 4)) {
        switch (id) {
        case 0:
            source = "ECG";
            break;
        case 1:
            source = "10 Hz sin test tone";
            break;
        case 2:
            source = "150 Hz sin test tone";
            break;
        case 3:
            source = "1 Hz Square wave test tone";
            break;
        case 4:
            source="EcgMock";
            break;
        default:
            break;
        }
 //   }

    return source;
}

/**
 * Apply the ECG capture settings when the apply-button is pressed
 *
 * \todo Some more validation on the settings data so it matches the EDF
 * requirements
 */
void SettingsWidget::applyCaptureSettings()
{
    QString fileName = fileNameTextBox->text();
    QString name = nameTextBox->text();
    QString recordingName = recordingNameTextBox->text();
    QString gender = genderTextBox->text();
    QString birthDate = birthdateTextBox->text();
    QString patientCode = patientCodeTextBox->text();
    QString notes = notesTextBox->toPlainText();

    if (fileName != "") {
        SettingsSingleton::instance().setFileName(fileName);
    }

    if (name != "") {
        SettingsSingleton::instance().setName(name);
    }

    if (recordingName != "") {
        SettingsSingleton::instance().setRecordingName(recordingName);
    }

    if (gender != "") {
        SettingsSingleton::instance().setGender(gender);
    }

    if (birthDate != "") {
        SettingsSingleton::instance().setBirthDate(birthDate);
    }

    if (patientCode != "") {
        SettingsSingleton::instance().setPatientCode(patientCode);
    }

    if (notes != "") {
        SettingsSingleton::instance().setNotes(notes);
    }

    if (saveAsEDFCheckbox->isChecked()) {
        SettingsSingleton::instance().setSaveAsEdf(true);
    }


}


/**
 * Setup the necessary components that is used in the widget
 */
void SettingsWidget::setupComponents()
{
    //Get settings from previous captures from the .ini-file
    iniPath = qApp->applicationDirPath() + "/settings.ini";
    QSettings settings(iniPath, QSettings::IniFormat);

    //=====START SOURCE CONTROL=====
    QVector<QAbstractButton *> sourceButtonArray;
    sourceControlButtonGroup = new QButtonGroup;

    ecgSource = new QRadioButton("ECG");
    sin10Source = new QRadioButton("10 Hz sin test tone");
    sin150Source = new QRadioButton("150 Hz sin test tone");
    squareSource = new QRadioButton("1 Hz square wave test tone");
    ecgMockSource = new QRadioButton("EcgMock");

    sourceButtonArray.append(ecgSource);
    sourceButtonArray.append(sin10Source);
    sourceButtonArray.append(sin150Source);
    sourceButtonArray.append(squareSource);
    sourceButtonArray.append(ecgMockSource);

    for (int ii=0; ii<sourceButtonArray.size(); ii++) {
        sourceControlButtonGroup->addButton(sourceButtonArray.at(ii), ii);
    }

    int sourceId = settings.value("/ECGCapture/Source", 0).toInt();
    sourceButtonArray.at(sourceId)->setChecked(true);
    settings.setValue("ECGCapture/Source", sourceId);
    SettingsSingleton::instance().setSource(idToSource(sourceId));
    //=====END SOURCE CONTROL=====

    //=====START SAMPLE RATE CONTROL=====
    QVector<QAbstractButton *> sampleRateButtonArray;
    sampleRateControlButtonGroup = new QButtonGroup;

    lowSampleRate = new QRadioButton("500 Hz");
    midSampleRate = new QRadioButton("1000 Hz");
    highSampleRate = new QRadioButton("2000 Hz");

    sampleRateButtonArray.append(lowSampleRate);
    sampleRateButtonArray.append(midSampleRate);
    sampleRateButtonArray.append(highSampleRate);

    for (int ii=0; ii<sampleRateButtonArray.size(); ii++) {
        sampleRateControlButtonGroup->addButton(sampleRateButtonArray.at(ii), ii);
    }

    int sampleRateId = settings.value("/ECGCapture/SampleRate", 0).toInt();
    sampleRateButtonArray.at(sampleRateId)->setChecked(true);
    settings.setValue("ECGCapture/SampleRate", sampleRateId);
    SettingsSingleton::instance().setSampleRate(idToSampleRate(sampleRateId));
    //=====END SAMPLE RATE CONTROL=====

    //Set up objects to be used
    fileNameTextBox = new QLineEdit;
    nameTextBox = new QLineEdit;
    recordingNameTextBox = new QLineEdit;
    genderTextBox = new QLineEdit;
    birthdateTextBox = new QLineEdit;
    patientCodeTextBox = new QLineEdit;
    notesTextBox = new QTextEdit;
    applyCaptureSettingsButton = new QPushButton("Apply settings");
    saveAsEDFCheckbox = new QCheckBox;
}

/**
 * Setup actions and the signal-slots used in the widget
 */
void SettingsWidget::setupActions()
{
    //Signals-slots
    connect(sourceControlButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(sourceChanged(int)));
    connect(sampleRateControlButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(sampleRateChanged(int)));
    connect(applyCaptureSettingsButton, SIGNAL(clicked()), this, SLOT(applyCaptureSettings()));
}

/**
 * Setup the layout of the widget
 */
void SettingsWidget::setupLayout()
{
    QGroupBox *sampleRateControlGroup = new QGroupBox("Sample rate");
    QGroupBox *sourceControlGroup = new QGroupBox("Source");
    QGroupBox *captureSettingsGroup = new QGroupBox("ECG capture settings");

    QLabel *sampleFreqNote = new QLabel("NOTE: some frames are dropped at 2000 Hz.");
    QLabel *fileNameLabel = new QLabel("Filename: ");
    QLabel *nameLabel = new QLabel("Name: ");
    QLabel *recordingNameLabel = new QLabel("Recording name: ");
    QLabel *genderLabel = new QLabel("Gender: ");
    QLabel *birthdateLabel = new QLabel("Birth date: ");
    QLabel *patientCodeLabel = new QLabel("Patient code: ");
    QLabel *notesLabel = new QLabel("Notes: ");
    QLabel *saveAsEDFLabel = new QLabel("Save as EDF: ");

    //The ECG capture settings options layout
    QFormLayout *captureSettingsLayout = new QFormLayout;
    captureSettingsLayout->addRow(fileNameLabel, fileNameTextBox);
    captureSettingsLayout->addRow(nameLabel, nameTextBox);
    captureSettingsLayout->addRow(recordingNameLabel, recordingNameTextBox);
    captureSettingsLayout->addRow(genderLabel, genderTextBox);
    captureSettingsLayout->addRow(birthdateLabel, birthdateTextBox);
    captureSettingsLayout->addRow(patientCodeLabel, patientCodeTextBox);
    captureSettingsLayout->addRow(notesLabel, notesTextBox);
    captureSettingsLayout->addRow(saveAsEDFLabel, saveAsEDFCheckbox);
    captureSettingsLayout->addWidget(applyCaptureSettingsButton);

    captureSettingsGroup->setLayout(captureSettingsLayout);

    //Source control layout
    QVBoxLayout *sourceControlLayout = new QVBoxLayout;

    sourceControlLayout->addWidget(ecgSource);
    sourceControlLayout->addWidget(sin10Source);
    sourceControlLayout->addWidget(sin150Source);
    sourceControlLayout->addWidget(squareSource);
    sourceControlLayout->addWidget(ecgMockSource);

    sourceControlGroup->setLayout(sourceControlLayout);

    //Sample rate layout
    QVBoxLayout *sampleRateControlLayout = new QVBoxLayout;
    sampleRateControlLayout->addWidget(lowSampleRate);
    sampleRateControlLayout->addWidget(midSampleRate);
    sampleRateControlLayout->addWidget(highSampleRate);
    sampleRateControlLayout->addWidget(sampleFreqNote);

    sampleRateControlGroup->setLayout(sampleRateControlLayout);

    //Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(sourceControlGroup);
    mainLayout->addStretch();
    mainLayout->addWidget(sampleRateControlGroup);
    mainLayout->addStretch();
    mainLayout->addWidget(captureSettingsGroup);
    mainLayout->addStretch();

    setLayout(mainLayout);
}
