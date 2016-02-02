#include "bluetoothmenu.h"
#include "settingsmenu.h"

BluetoothMenu::BluetoothMenu()
{
    numberOfOptions=1;
    options={"Default", "Default"};

}

/**
  *@todo Implement to get Bluyetooth functionallity
 */
AbstractMenu *BluetoothMenu::newMenu(){
    AbstractMenu *newMenu=0;
    switch (currentOption){
    case 0:
        newMenu=new SettingsMenu;
        break;
    case 1:
        newMenu=new BaseMenu;
    }
    return newMenu;


}


