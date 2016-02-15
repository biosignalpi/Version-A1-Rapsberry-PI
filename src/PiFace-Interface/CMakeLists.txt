project(PiFaceCAD)
cmake_minimum_required(VERSION 3.0.2)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
set(CMAKE_INCLUDE_CURRENT_DIR ON)

##Local directories needs to be set for the used system
include_directories("~/ExJobb/Software/libpifacecad/src"
"~/ExJobb/Software/libpifacecad"
"~/ExJobb/Software/libmcp23s17")
##Local directories needs to be set for the used system
link_directories("/mnt/rasp-rootfs/usr/local/lib" "/mnt/rasp-rootfs/opt/vc/lib" "/mnt/rasp-rootfs/lib/arm-linux-gnueabihf" "/mnt/rasp-rootfs/rootfs/lib" "/mnt/rasp-rootfs/usr/lib/arm-linux-gnueabihf" "/mnt/rasp-rootfs/usr/lib")

##Local directories needs to be set for the used system
find_library(pifacecad REQUIRED NAMES pifacecad libpifacecad HINTS "~/ExJobb/Software/libpifacecad" "/mnt/rasp-rootfs/home/pi/ExJobb/Software/libpifacecad")
##Local directories needs to be set for the used system
find_library(mcp23s17 REQUIRED NAMES libmcp23s17 mcp23s17 HINTS "~/ExJobb/Software/libmcp23s17" "/mnt/rasp-rootfs/home/pi/ExJobb/Software/libmcp23s17")

FIND_PACKAGE(Qt5Core REQUIRED)

find_library(bcm2835_lib bcm2835 REQUIRED)
include_directories("/mnt/rasp-rootfs/usr/local/include/")


add_library(menues  pifacecontrolandview.cpp abstractmenu.cpp  basemenu.cpp bluetoothmenu.cpp settingsmenu.cpp ecgcapturemenu.cpp)


add_executable(PiFaceBioPI main.cpp)
target_link_libraries(PiFaceBioPI menues model devicemanager bcm2835 ${pifacecad} ${mcp23s17})
qt5_use_modules(menues Core)
