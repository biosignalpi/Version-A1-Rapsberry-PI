#include "datastream.h"

    DataStream::DataStream() {


    }

    DataStream::~DataStream() {


    }

    QString DataStream::toText(int index){
        return this->at(index).toText();
    }
