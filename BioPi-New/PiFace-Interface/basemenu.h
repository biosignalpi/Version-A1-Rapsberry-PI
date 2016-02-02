#ifndef BASEMENU_H
#define BASEMENU_H

#include "abstractmenu.h"
/**
 * @brief Homepage of the Menu-system for the PiFace GUI
 * @author Martin
 */
class BaseMenu : public AbstractMenu
{
public:
    BaseMenu();
    virtual ~BaseMenu(){};
    virtual AbstractMenu *newMenu();

};

#endif // BASEMENU_H

