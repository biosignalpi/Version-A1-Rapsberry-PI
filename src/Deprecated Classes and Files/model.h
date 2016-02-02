#ifndef MODEL_H
#define MODEL_H


#include "devicemanager.h"
#include "ecgstream_fourchannels.h"
#include "settingssingleton.h"
#include "datalogger.h"

/**
 * \class Model
 * \brief The main model responsible for the logic of the MVC-part
 *
 * used by main
 * combines device with DataStream object
 * \author Martin
 *
*/
class Model
{
public:
    Model();
    ~Model();
    void sampleData(); ///< Sample data into variable stream from the connected device
    void print(); ///< Prints sampled data
    void stopSampling();
    void test();
protected:
    void init(int);
 //   SettingsSingleton *settings=SettingsSingleton::instance();
    DeviceManager* device; ///< Connection to DeviceManager
    EcgStream_four* stream; ///< Vector type of class EcgStream used to store the measured values
    EcgStream_four* stream2; ///< Vector type of class EcgStream used to store the measured values
    DataLogger* logger;

private:
    const static int numberOfChannels=4;
    void saveAsText(EcgStream_four & input);


};

#endif // MODEL_H
