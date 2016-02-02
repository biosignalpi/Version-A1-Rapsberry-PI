#include "homepagewidget.h"
#include <QtWidgets>

HomePageWidget::HomePageWidget(QWidget *parent):
    QWidget( parent )
{
    QLabel *headerLabel = new QLabel("<span style=\"font-size:24px; font-weight:bold;\">Biosignal PI</span>");
    headerLabel->setTextFormat(Qt::RichText);

    QLabel *textLabel = new QLabel();
    textLabel->setText("This is a 5 lead ECG system for the raspberry PI <br /><br />"
                       "How to record an ECG:"
                       "<ol>"
                       "<li>Click on the settings button, choose source and sampling rate. 1 kHz sampling rate is recommended in order to prevent frame drops.</li>"
                       "<li>Fill in the ECG capture settings (optional).</li>"
                       "<li>Connect the leads as show in the image.</li>"
                       "<li>Click on the ECG capture button and then on Start ECG capture.</li>"
                       "<li>To stop the capture, press the Stop ECG capture button, this will save the captured data to a file.</li>"
                       "</ol> <br />"
                       "How to view an ECG:"
                       "<ol>"
                       "<li>Click on the View ECG button.</li>"
                       "<li>Click on the Get ECG files button.</li>"
                       "<li>Double-click on the file with the ECG values.</li>"
                       "<li>The ECG will now be loaded and viewed at the right side of the screen.</li>"
                       "</ol>");
    textLabel->setWordWrap(true);


    QLabel *placementHeaderLabel = new QLabel("<b>Electrode placement</b>");
    placementHeaderLabel->setAlignment(Qt::AlignHCenter);

    QLabel *placementLabel = new QLabel();
    placementLabel->setPixmap(QPixmap(":/images/images/5-electrode-ECG.jpg"));

    QVBoxLayout *leftSideLayout = new QVBoxLayout;
    leftSideLayout->addStretch();
    leftSideLayout->addWidget(headerLabel);
    leftSideLayout->addWidget(textLabel);
    leftSideLayout->addStretch();

    QVBoxLayout *rightSideLayout = new QVBoxLayout;
    rightSideLayout->addStretch();
    rightSideLayout->addWidget(placementHeaderLabel);
    rightSideLayout->addWidget(placementLabel);
    rightSideLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addStretch();
    mainLayout->addLayout(leftSideLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(rightSideLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
}
