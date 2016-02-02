#include "ecgcapturemenu.h"
#include "settingsmenu.h"
#include "../settingssingleton.h"
#include <chrono>
#include <thread>
#include "pifacecad.h"

EcgCaptureMenu::EcgCaptureMenu()
{
    options={"Settings", "Start"};
    numberOfOptions=1;
    device=new DeviceManager();
    stream=new DataStream();
    SettingsSingleton::instance().setSourceId(0);
    device->init(0, *stream);

    QThread *sampleT = new QThread;
    device->moveToThread(sampleT);

}
AbstractMenu *EcgCaptureMenu::newMenu(){
    AbstractMenu *newMenu=0;
    switch (currentOption){
    case 0:
        setUpperText();
        newMenu=new SettingsMenu;
        break;

    case 1:
        setUpperText("Stop");
        device->start();
        while(true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));  // IMPORTANT if not using this time-out the read_switch fucntion would read a push more then once.
            if(!pifacecad_read_switch(5)) {
                device->stop();
                logger->save(*stream);
                break;
            }
        }

    }
    return newMenu;


}



