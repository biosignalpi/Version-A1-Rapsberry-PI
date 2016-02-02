#include "pifacecontrolandview.h"
#include "pifacecad.h"
#include <chrono>
#include <thread>
#include "abstractmenu.h"
#include "basemenu.h"





 PiFaceControlAndView::PiFaceControlAndView(QObject *parent):
    QObject(parent)
{

}

PiFaceControlAndView::~PiFaceControlAndView(){

}

void PiFaceControlAndView::run()
{
    pifacecad_open();
    pifacecad_lcd_backlight_on();
    pifacecad_lcd_write("Chose option");
    AbstractMenu* currentMenu=new BaseMenu();
    currentMenu->next();

    while(true){
        if(!pifacecad_read_switch(7)){
            currentMenu->next();
        }else if(!pifacecad_read_switch(5)){
            AbstractMenu* tempMenu;
            tempMenu=currentMenu->newMenu();
            if (tempMenu){
                delete currentMenu;
                currentMenu=tempMenu;
            }
            else
                delete tempMenu;
            currentMenu->setLowerText();

        }else if(!pifacecad_read_switch(4))
            break;


        std::this_thread::sleep_for(std::chrono::milliseconds(300));  // IMPORTANT if not using this time-out the read_switch fucntion would read a push more then once.
    }
    pifacecad_lcd_clear();
    pifacecad_lcd_home();
    delete currentMenu;
    pifacecad_lcd_write("QUIT");
    pifacecad_close();

    emit finished();
}
