#include "settingsmenu.h"

SettingsMenu::SettingsMenu()
{
        numberOfOptions=0;
        options={"Setting1", "Setting2"};

}

AbstractMenu *SettingsMenu::newMenu(){
    AbstractMenu *newMenu=0;
    switch (currentOption){
    case 0:
        setUpperText();
        newMenu=new EcgCaptureMenu;
        break;

    case 1:
        newMenu=new EcgCaptureMenu;
        break;
    }
    return newMenu;

}
