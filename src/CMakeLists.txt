cmake_minimum_required(VERSION 3.0.2)   ##Needed to generate Auto UIC
PROJECT(BioPI)


#add_subdirectory(Tests)
add_subdirectory(PiFace-Interface)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##CHECK if compiler supports c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)



FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Bluetooth REQUIRED)
FIND_PACKAGE(Qt5DBus REQUIRED)
FIND_PACKAGE(Qwt REQUIRED)


find_library(bcm2835_lib bcm2835 REQUIRED)
include_directories("/mnt/rasp-rootfs/usr/local/include/")

include_directories(
"/usr/local/qwt-6.1.2/include"
"/usr/local/qwt-6.1.2/lib") 





##Comment out /mnt/rasp-rootfs/ to build for ubuntu
include_directories(SYSTEM
"/mnt/rasp-rootfs/usr/include/arm-linux-gnueabihf"
"/mnt/rasp-rootfs/usr/include"
"/mnt/rasp-rootfs/usr/local/include"
"/mnt/rasp-rootfs/usr/lib/arm-linux-gnueabihf"
${QWT_INCLUDE_DIR}
)


##Comment out /mnt/rasp-rootfs/ to build for ubuntu
link_directories( 
#"/mnt/rasp-rootfs/opt/vc/lib" "/mnt/rasp-rootfs/lib/arm-linux-gnueabihf" "/mnt/rasp-rootfs/rootfs/lib" "/mnt/rasp-rootfs/usr/lib/arm-linux-gnueabihf" "/mnt/rasp-rootfs/usr/lib" "/mnt/rasp-rootfs/usr/local/lib" "/mnt/rasp-rootfs/usr/local/qwt-6.1.2/lib"
"/usr/local/qwt-6.1.2/lib"
)  

add_library(model settingssingleton.cpp datastream.cpp datalogger.cpp ecgstreamobject.cpp )
add_library(mainwindow mainwindow.cpp plotandcapturewidget.cpp plot.cpp 
plottingwidget.cpp loadbigfile.cpp sliderwidget.cpp  settingswidget.cpp homepagewidget.cpp)



###Resurces needed for loading images in the QT-GUI
file(GLOB Resources "*.qrc")
QT5_ADD_RESOURCES (ResourceSources ${Resources})


### HRV functionality from MATLAB Coder
file(GLOB hrv_SRC "HRV/*.cpp" "HRV/*.c")

add_library(timeDomainHRV ${hrv_SRC} hrvwidget.cpp hrvanalysis.cpp  convertecgtoibi.cpp libFiles/QRSFILT.CPP libFiles/QRSDET2.CPP)



file(GLOB btfiletransfer "Qt-btfiletransfer/*.cpp")

add_library(bluetoothwidget ${btfiletransfer})


add_library(devicemanager devicemanager.cpp deviceinterface.cpp 
ecgmock.cpp meanFilter.cpp ecgcapture.cpp samplingthread.cpp ecgstreamobject.cpp)


add_definitions(${QT5Widgets_DEFINITIONS})
ADD_EXECUTABLE(BioPI WIN32 main.cpp ${ResourceSources})
target_link_libraries(devicemanager bcm2835)
target_link_libraries(mainwindow qwt model)


Target_Link_Libraries(BioPI mainwindow devicemanager bcm2835 timeDomainHRV bluetoothwidget) # wfdb)
qt5_use_modules(mainwindow Core Widgets Bluetooth DBus)
qt5_use_modules(devicemanager Core Widgets)
qt5_use_modules(model Core Widgets)
qt5_use_modules(bluetoothwidget Core Widgets Bluetooth DBus)
qt5_use_modules(timeDomainHRV Core Widgets Bluetooth DBus)
