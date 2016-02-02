#include "abstractmenu.h"
#include "pifacecad.h"

AbstractMenu::AbstractMenu()
{
 currentOption=0;
}

void AbstractMenu::setUpperText(){
    pifacecad_lcd_clear();
    pifacecad_lcd_set_cursor(0,0);
    const char * tmp = options.at(currentOption).c_str();
    pifacecad_lcd_write(tmp);
}
void AbstractMenu::setUpperText(const char * input){
    pifacecad_lcd_clear();
    pifacecad_lcd_set_cursor(0,0);
    pifacecad_lcd_write(input);
}

void AbstractMenu::setLowerText(){
    pifacecad_lcd_set_cursor(0,1);
    const char * tmp = options.at(currentOption).c_str();
    pifacecad_lcd_write(tmp);
}

void AbstractMenu::next(){
    if(currentOption==numberOfOptions)
        currentOption=0;
    else
        currentOption=currentOption+1;
    pifacecad_lcd_set_cursor(0,1);
    pifacecad_lcd_write("                   ");
    pifacecad_lcd_set_cursor(0,1);
    const char * tmp = options.at(currentOption).c_str();
    pifacecad_lcd_write(tmp);


}
