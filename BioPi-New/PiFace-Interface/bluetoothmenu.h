#ifndef BLUETOOTHMENU_H
#define BLUETOOTHMENU_H

#include "basemenu.h"
/**
 * @brief The BluetoothMenu class
 *
 * @author Martin
 */
class BluetoothMenu : public BaseMenu
{
public:
    BluetoothMenu();
    virtual ~BluetoothMenu(){};
    /**
     * @brief Does nothing
     * @todo implement when Bluetooth functionallity is working for the RPI
     */
    virtual AbstractMenu *newMenu();

};

#endif // BLUETOOTHMENU_H


