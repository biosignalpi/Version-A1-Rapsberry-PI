#ifndef LOADBIGFILE_H
#define LOADBIGFILE_H

#include <QThread>
#include <QVector>
#include <QPointF>
/**
 * @brief Class used to load a big .txt file in a new thread
 *
 * @author Jonatan
 *
 * @todo Could be integrated into DataLogger instead
 */
class LoadBigFile : public QThread
{
    Q_OBJECT

public:
    LoadBigFile(QString fileName, QObject *parent = NULL);
    virtual void run();

signals:
    /**
     * @brief signal used to send the loaded txt file as a QVector<QVector <QPointF> > that can be used for plotting the file
     */
    void sendFileData(QVector<QVector<QPointF> >);

private:
    void decimate(); //TODO
    bool decimateFlag;
    QString fname;
};

#endif // LOADBIGFILE_H
