/**
 * @class  AbstractMenu
 * @brief Abstract menu object for PiFace CAD
 *
 *AbstractMenu is the base class for menu objects to be used to create a
 *small logical menu that can be called from the PiFace CAD
 *
 *@author Martin
 *
 */
#ifndef ABSTRACTMENU_H
#define ABSTRACTMENU_H

#include <string>
#include <vector>

class AbstractMenu
{
public:
    AbstractMenu();
    virtual ~AbstractMenu(){};

    /**
     * @brief Pure virtual function, creates the next Menu object
     * Pure virtual function, that is meant to create a the AbstractMenu object that
     * comes after the MenuObject that called it. What AbstractMenu object that are
     * created depends on in which object the function was called.
     *
     * @param currentOption inherited from AbstractMenu to realize what Object to create.
     *
     */
    virtual AbstractMenu *newMenu()=0;

    /**
     * @brief Sets the first row of the PiFace CAD to the current option choosen
     *Uses the C library pifacecad.h to control the display
     *
     */
    virtual void setUpperText();

    /**
         * @brief Sets the first row of the PiFace CAD to the current option choosen
         *Uses the C library pifacecad.h to control the display
         *@param text to display on upper row of PiFace CAD
         *
         */
    virtual void setUpperText(const char *);



    /**
        * @brief Toggles the second row of the PiFace CAD to the next option
        *Uses the C library pifacecad.h to control the display
        *
        */
    virtual void next();

    /**
        * @brief Sets the second row of the PiFace CAD to the current option choosen
        *Uses the C library pifacecad.h to control the display
        *
        */
    virtual void setLowerText();
protected:

    /** @param options
     * @brief std::vector containing the different options to display on the PiFace CAD
     *To be set by the derived AbstractMenu object
     */
    std::vector<std::string> options;

    /** @param numberOfOptions
     * @brief number of elements stored in the options vector.
     * To be set by the derived AbstractMenu object
     */
    int numberOfOptions;

    /**
     * @param currentOption
     * @brief Counter that keeps track of the option visible on the PiFace CAD
     */
    int currentOption;
};

#endif // ABSTRACTMENU_H


