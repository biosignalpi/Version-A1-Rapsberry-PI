#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "ecgcapturemenu.h"
/**
 * @brief The SettingsMenu class for the PiFace GUI
 *
 * @author Martin
 */
class SettingsMenu : public EcgCaptureMenu
{
public:
    SettingsMenu();
    virtual ~SettingsMenu(){};
    /**
      * Unimplemented
     * @todo Implement
     */
    virtual AbstractMenu *newMenu();

};

#endif // SETTINGSMENU_H
