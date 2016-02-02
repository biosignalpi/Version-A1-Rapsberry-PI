#ifndef ECGSTREAMOBJECT_H
#define ECGSTREAMOBJECT_H

//#include "datastreamobject.h"
#include <QString>
/**
 * @brief Struct to store Biosignal data from a specific time, combined with DataStream it will store a sequence of sampled data.
 * @param frame1,frame2,frame3 Captured ECG-data
 * @param resp Respiration data
 * @param time Timestamp information
 * @author Martin
 *
 */
struct EcgStreamObject
{
public:
    EcgStreamObject();
    /**
     * @brief Constructor for a EcgStreamObject to be used in a DataStream vector.
     * @param [in] frame1,frame2,frame3 Captured ECG-data
     * @param [in] resp Respiration data
    * @param [in] time Timestamp information
     */
    EcgStreamObject(double frame1,double frame2,double frame3, double resp, double time);
    virtual ~EcgStreamObject();
    /**
     * @brief Converts the data from the struct into a QString representation
     * @return String representation of the Data with tab between values.
     */
    virtual QString toText() const;
    double frame1,frame2,frame3,resp,time;

};

#endif // ECGSTREAMOBJECT_H
