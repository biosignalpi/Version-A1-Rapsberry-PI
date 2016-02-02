#ifndef ECGMOCK_H_
#define ECGMOCK_H_

#include "datastream.h"
#include "deviceinterface.h"

//#include "ecgstream_fourchannels.h"


/**
 * @addtogroup Device-Facade
 * @{ */

/*! \class EcgMock
 * \brief Mock version of an device
 *  The EcgMock device will return sine and cosine functions as data. Call the EcgMock should render
 * (sine(x),cosine(x),tan(x),sin(2x))
 * \author Martin
 * \bug No known Bugs
 */
class EcgMock   : public DeviceInterface {
	Q_OBJECT
public:
    EcgMock(DataStream& inputStream);
    virtual ~EcgMock();
    virtual void getData(DataStream&); ///< \see DeviceInterface::getData();
    virtual bool connected(); ///< true as long as close() isn't called.
    virtual void reconnect(); ///< sets state=true
    virtual void close(); ///< sets state=false

    virtual void stop();



protected:
    virtual void run();
private:
    virtual void init();
    bool state,condition;
    double cnt=0;
    QVector<QVector<QPointF> > *privateSamples;
    QVector<QVector<double> > *sampleData;
};

/** @} */

#endif /* ECGMOCK_H_ */

#ifndef PI
#define PI 3.14159265
#endif

