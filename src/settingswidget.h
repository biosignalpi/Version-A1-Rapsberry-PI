#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

class QLineEdit;
class QTextEdit;
class QPushButton;
class QButtonGroup;
class QRadioButton;
class QCheckBox;
/**
 * @brief Widget used to change the different settings in SettingsWidget
 *
 * @author Martin
 * @todo Add some sort of input-control for validating that the entered data is "correct"
 */
class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    SettingsWidget(QWidget * = NULL);

private slots:
    void sourceChanged(int);
    void sampleRateChanged(int);
    void applyCaptureSettings();

private:
    void setupComponents();
    void setupActions();
    void setupLayout();
    int idToSampleRate(int);
    QString idToSource(int);

    QString iniPath;
    QLineEdit *fileNameTextBox;
    QLineEdit *nameTextBox;
    QLineEdit *recordingNameTextBox;
    QLineEdit *genderTextBox;
    QLineEdit *birthdateTextBox;
    QLineEdit *patientCodeTextBox;
    QTextEdit *notesTextBox;
    QPushButton *applyCaptureSettingsButton;
    QButtonGroup *sourceControlButtonGroup;
    QButtonGroup *sampleRateControlButtonGroup;
    QCheckBox *saveAsEDFCheckbox;
    QRadioButton *ecgSource;
    QRadioButton *sin10Source;
    QRadioButton *sin150Source;
    QRadioButton *squareSource;
    QRadioButton *ecgMockSource;
    QRadioButton *lowSampleRate;
    QRadioButton *midSampleRate;
    QRadioButton *highSampleRate;
};

#endif // SETTINGSWIDGET_H
