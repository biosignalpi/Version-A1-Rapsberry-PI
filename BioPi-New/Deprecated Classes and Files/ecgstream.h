#ifndef ECGSTREAM_H_
#define ECGSTREAM_H_

#include "datastream.h"
#include <vector>

/** \@file ecgstream.h
 * @brief Struct for storage of ECG-data
 * @deprecated Leftover Class
 *
 *
 * \author Martin
 * \bugs No known Bugs
 *
 */
struct EcgStream: public DataStream {
public:
    EcgStream();
    virtual ~EcgStream();
    virtual int getSize();///< \brief returns size of the streamVector \return size
    virtual bool full(){return false;};///< Returns state of streamVector \return full?
    virtual double getData(); ///< Returns first element in streamVector, also deletes the element from streamVector \return [double] first element
    void transferValues(EcgStream &);
    virtual bool empty(); ///< Return empty if streamVector is empty \return empty?
    virtual void add(double); ///< adds the element to the end of streamVector \param[in] value
    virtual void add(double,double,double,double,double){};
    virtual void hej();  ///< DUMMY
private:

    std::vector<double> streamVector; ///< dynamic vector that stores doubles
    void init();

};

#endif /* ECGSTREAM_H_ */
