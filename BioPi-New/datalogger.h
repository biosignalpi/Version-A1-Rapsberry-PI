#ifndef DATALOGGER_H
#define DATALOGGER_H
/**
 * @addtogroup DataLogger
 * @brief Classes and Functions used to log data, for example saving to txt file or edf file.
 * @author Martin
 * @{ */

#include <QObject>
#include "datastream.h"

/**
 * @brief The DataLogger class
 * @author Martin
 */
class DataLogger : public QObject
{
    Q_OBJECT
public:
    explicit DataLogger(QObject *parent = 0);
    ~DataLogger();

    void save(DataStream& input); ///< Saves the input to a txt-file, header-file and edf-file(if bool saveAsEdf in SettingsSingleton)
private:
    void saveAsText(DataStream& input); ///< Saves input as a txt-file and header-file @param[in] input the DataStream containing the data to save.
    void saveAsEdf(DataStream& input); ///< Saves input as a edf-file @param[in] input the DataStream containing the data to save.


signals:
    void updateStatus(QString status); ///< Signal emitting status messages during the process
public slots:
};

/**
  * @} */


#endif // DATALOGGER_H
