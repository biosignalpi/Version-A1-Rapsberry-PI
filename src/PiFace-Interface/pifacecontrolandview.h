#ifndef PIFACECONTROLANDVIEW_H
#define PIFACECONTROLANDVIEW_H

#include <QObject>
/**
 * @brief Handles the eventloop of the PiFace GUI
 *
 * @author Martin
 */
class PiFaceControlAndView : public QObject
{
    Q_OBJECT

public:
    PiFaceControlAndView(QObject *parent=0);
    ~PiFaceControlAndView();
public slots:
    /**
     * @brief Main eventloop
     */
    void run();
signals:
    /**
     * @brief Emits when it wants to be terminated
     */
    void finished();

};

#endif // PIFACECONTROLANDVIEW_H
