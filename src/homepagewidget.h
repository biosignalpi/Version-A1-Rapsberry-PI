#ifndef HOMEPAGEWIDGET_H
#define HOMEPAGEWIDGET_H

#include <QWidget>
/**
 * @brief Startpage for the Biosignal PI software.
 * Displays information about the project/software and shows a picture on how to attach the electrodes.
 * @author Jonatan
 * @author Martin
 *
 * */
class HomePageWidget : public QWidget
{
    Q_OBJECT

public:
    HomePageWidget(QWidget * = NULL);
};

#endif // HOMEPAGEWIDGET_H
