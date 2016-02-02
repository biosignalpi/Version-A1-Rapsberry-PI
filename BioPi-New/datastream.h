

#ifndef DATASTREAM_H_
#define DATASTREAM_H_


#include <QVector>
#include <QString>
#include "ecgstreamobject.h"

/**
  * @brief Abstract Interface that should be used for storing data in the memory
  * @author Martin
  *
  */
class DataStream : public QVector<EcgStreamObject> {

public:
    DataStream();

    virtual ~DataStream();
    /**
     * @brief Text representation of the Object at index
     * @param index Index of wanted EcgStreamObject
     * @return QString contationg the data of the EcgStreamObject
     */
    QString toText(int index);
    int samplingRate;




};

#endif /* DATASTREAM_H_ */
