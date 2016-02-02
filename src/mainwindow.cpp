#include "mainwindow.h"
/*#include "ecgplotwidget.h"
#include "ecgviewwidget.h"
#include "emptywidget.h" */
#include "homepagewidget.h"
#include "plottingwidget.h"
#include "settingswidget.h"
#include <QtWidgets>
#include "plotandcapturewidget.h"
#include "hrvwidget.h"
#include "Qt-btfiletransfer/remoteselector.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget( parent )
{
    setupComponents();
    setupActions();
    setupLayout();
}

void MainWindow::quit()
{
    qApp->quit();
}

void MainWindow::takeScreenshot()
{
    QPixmap screen = this->grab();

    QDir directory(qApp->applicationDirPath());
    QStringList filesInDir = directory.entryList();
    QString baseName = QDate::currentDate().toString().remove(" ");

    if (filesInDir.contains(baseName+".png")) {
        int ii=1;
        while (filesInDir.contains(QString(baseName+"%1.png").arg(ii))) {
            ii++;
        }
        baseName += QString::number(ii);
    }
    baseName += ".png";
    screen.save(baseName);

}
/**
 *
 *
 */
void MainWindow::setupComponents()
{
    HomePageWidget *homePageWidget = new HomePageWidget;
    PlotAndCaptureWidget *ecgPlotWidget = new PlotAndCaptureWidget;
    PlottingWidget *plottingWidget = new PlottingWidget;
    SettingsWidget *settingsWidget = new SettingsWidget;
    HrvWidget *hrvWidget= new HrvWidget;
    RemoteSelector *bluetoothWidget=new RemoteSelector;

    quitButton = new QPushButton(tr("Quit"));
    quitButton->show();
    quitButton->setMinimumHeight(64);
    quitButton->setMaximumHeight(64);


    screenShotButton = new QPushButton(tr("Take snapshot"));
    screenShotButton->show();
    screenShotButton->setMinimumHeight(64);
    screenShotButton->setMaximumHeight(64);


    stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(homePageWidget);
    stackedWidget->addWidget(ecgPlotWidget);
    stackedWidget->addWidget(plottingWidget);
    stackedWidget->addWidget(settingsWidget);
    stackedWidget->addWidget(hrvWidget);
    stackedWidget->addWidget(bluetoothWidget);


    QListWidgetItem *homeListWidgetItem = new QListWidgetItem;
    homeListWidgetItem->setText("Start");
    homeListWidgetItem->setIcon(QIcon(":/images/images/go-home.png"));

    QListWidgetItem *plotCaptureListWidgetItem = new QListWidgetItem;
    plotCaptureListWidgetItem->setText("ECG capture");
    plotCaptureListWidgetItem->setIcon(QIcon(":/images/images/emblem-favorite.png"));

    QListWidgetItem *ecgViewListWidgetItem = new QListWidgetItem;
    ecgViewListWidgetItem->setText("View ECG");
    ecgViewListWidgetItem->setIcon(QIcon(":/images/images/media-playback-start-4.png"));

    QListWidgetItem *settingsListWidgetItem = new QListWidgetItem;
    settingsListWidgetItem->setText("Settings");
    settingsListWidgetItem->setIcon(QIcon(":/images/images/emblem-system-2.png"));

    QListWidgetItem *hrvListWidgetItem = new QListWidgetItem;
    hrvListWidgetItem->setText("HRV");
    hrvListWidgetItem->setIcon(QIcon(":/images/images/emblem-system-2.png"));

    QListWidgetItem *bluetoothWidgetItem = new QListWidgetItem;
    bluetoothWidgetItem->setText("Bluetooth Transfer");
    bluetoothWidgetItem->setIcon(QIcon(":/images/images/emblem-favorite.png"));


    listWidget = new QListWidget();
    listWidget->addItem(homeListWidgetItem);
    listWidget->addItem(plotCaptureListWidgetItem);
    listWidget->addItem(ecgViewListWidgetItem);
    listWidget->addItem(settingsListWidgetItem);
    listWidget->addItem(hrvListWidgetItem);
    listWidget->addItem(bluetoothWidgetItem);
    listWidget->setIconSize(QSize(48,48));
    listWidget->setFlow(QListWidget::LeftToRight);
    listWidget->setMaximumHeight(64);
    listWidget->setUniformItemSizes(false);
}

void MainWindow::setupActions()
{

    connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
    connect(screenShotButton, SIGNAL(clicked()), this, SLOT(takeScreenshot()));
}

void MainWindow::setupLayout()
{
    QHBoxLayout *sidebarLayout = new QHBoxLayout;
    sidebarLayout->addWidget(listWidget);
    sidebarLayout->addWidget(screenShotButton);
    sidebarLayout->addWidget(quitButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(stackedWidget);
    mainLayout->addLayout(sidebarLayout);

    setLayout(mainLayout);
}
