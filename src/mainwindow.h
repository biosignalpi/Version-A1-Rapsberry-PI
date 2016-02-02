#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QPushButton;
class QListWidget;
class QStackedWidget;

/**
 * @brief MainWindow holds all the different parts of the GUI
 * Implements the different widgets used in the GUI and let the user decide wich widget to use by clicking
 * the approbiate icon representing the different widgets the Biosignal PI software contains of.
 *  @author Martin
 * @author Jonatan
 * @todo add new Icons for the HRV-Widget and the BluetoothTransfer-Widget
 *
 */
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget * = NULL);

private slots:
    /**
     * @brief Terminates the application
     */
    void quit();
    /**
     * @brief Saves a screenshot of the application as a png file
     */
    void takeScreenshot();

private:
    /**
     * @brief declares and creates the different components of the Mainwindow
     */
    void setupComponents();
    /**
     * @brief Used to create the different actions(CONNECT) needed for the Mainwindow
     */
    void setupActions();
    /**
     * @brief Controlls the Graphical part of the MainWindow
     */
    void setupLayout();


    QPushButton *quitButton;
    QPushButton *screenShotButton;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;

};

#endif // MAINWINDOW_H
