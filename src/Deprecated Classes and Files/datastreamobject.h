#ifndef DATASTREAMOBJECT_H
#define DATASTREAMOBJECT_H

#include <QString>

struct DataStreamObject
{
public:
    DataStreamObject();
    virtual ~DataStreamObject();
    double time;
    virtual QString toText() const;

};

#endif // DATASTREAMOBJECT_H
