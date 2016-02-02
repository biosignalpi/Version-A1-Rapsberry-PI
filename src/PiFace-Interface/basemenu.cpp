#include "basemenu.h"
#include "ecgcapturemenu.h"
#include "bluetoothmenu.h"

BaseMenu::BaseMenu()
{
    numberOfOptions=1;
    options={"Ecg Capture", "Bluetooth"};
}

AbstractMenu *BaseMenu::newMenu(){
    AbstractMenu *newMenu=0;
    switch (currentOption){
    case 0:
        setUpperText();
        newMenu=new EcgCaptureMenu;
        break;

    case 1:
        setUpperText();
        newMenu=new BluetoothMenu;
        break;
    }
    return newMenu;


}


