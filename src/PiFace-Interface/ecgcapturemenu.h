#ifndef ECGCAPTUREMENU_H
#define ECGCAPTUREMENU_H

#include "basemenu.h"
#include "../datalogger.h"
#include "../devicemanager.h"

/**
 * @brief  Menu were the user can chosse between SettingsMenu or starting ECG-capture
 * The start menu starts the ECG-capture and will capture until pressed again.
 *
 * @author Martin
 */
class EcgCaptureMenu : public BaseMenu
{
public:
    EcgCaptureMenu();
    virtual ~EcgCaptureMenu(){};
    /**
     * @brief Enter SettingsMenu for case 0 and starts DeviceManager and EcgCapture for case 1
     * @return the next menu
     * @bug The program will freeze after the capturing is stopped since the stop function isn't implemented with a return statement
     */
    virtual AbstractMenu *newMenu();
private:
       DeviceManager* device;
       DataStream* stream;
       DataLogger* logger;
};

#endif // ECGCAPTUREMENU_H




