SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_C_COMPILER $ENV{HOME}/ExJobb/RaspberryPi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER $ENV{HOME}/ExJobb/RaspberryPi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++)

#SET(CMAKE_CXX_AR $ENV{HOME}/ExJobb/RaspberryPi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-ar)
SET(CMAKE_LINKER       $ENV{HOME}/ExJobb/RaspberryPi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-ld)
#SET(CMAKE_NM           $ENV{HOME}/ExJobb/RaspberryPi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-nm)
#SET(CMAKE_OBJCOPY      $ENV{HOME}/ExJobb/RaspberryPi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-objcopy)
#SET(CMAKE_OBJDUMP      $ENV{HOME}/ExJobb/RaspberryPi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-objdump)
#SET(CMAKE_STRIP        $ENV{HOME}/ExJobb/RaspberryPi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-strip)
#SET(CMAKE_RANLIB       $ENV{HOME}/ExJobb/RaspberryPi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-tanlib)



SET(CMAKE_FIND_ROOT_PATH /mnt/rasp-rootfs/)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#set(CMAKE_SKIP_RPATH true)

set (CMAKE_PREFIX_PATH "/mnt/rasp-rootfs/usr/local/qt-5.5-RPI/lib/cmake/" : "/mnt/rasp-rootfs")
set(CMAKE_LIBRARY_PATH "mnt/rasp-rootfs/lib" : "/mnt/rasp-rootfs/usr/lib" : "/mnt/rasp-rootfs/usr/local/lib")
#set(CMAKE_MODULE_PATH $ENV{HOME}/raspberrypi/rootfs/usr/share/cmake-2.8/Modules)
SET(QWT_INCLUDE_DIR "/mnt/rasp-rootfs/usr/local/qwt-6.1.2/" CACHE PATH "")
SET(QWT_LIBRARY "/mnt/rasp-rootfs/usr/local/qwt-6.1.2/lib/" CACHE PATH "")
#set (CMAKE_PREFIX_PATH "/mnt/rasp-rootfs/usr/local/qt5-pi/lib/cmake/Qt5DBus/")

 set(Qt5Gui_OPENGL_INCLUDE_DIR 
    ${CMAKE_FIND_ROOT_PATH}/opt/vc/include
   ${CMAKE_FIND_ROOT_PATH}/opt/vc/include/interface/vcos/pthreads
   ${CMAKE_FIND_ROOT_PATH}/opt/vc/include/interface/vmcs_host/linux
 )

set (CMAKE_CXX_FLAGS "-W -O3 -g -Wall -std=c++0x -rdynamic  -D_TRACE ${CMAKE_CXX_FLAGS}"  CACHE STRING "" FORCE)
#rdynamic is for stack unwinding on crash

set(SYSROOT /mnt/rasp-rootfs/)
set (PKG_CONFIG_SYSROOT_DIR ${SYSROOT})
set(PKG_CONFIG_PATH ${SYSROOT}/usr/lib/pkgconfig:${SYSROOT}/usr/local/lib/pkgconfig:${SYSROOT}/usr/lib/arm-linux-gnueabihf/pkgconfig:${SYSROOT}/usr/share/pkgconfig)

set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS})


#set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

#set(CMAKE_EXTRA_SHARED_LIBRARY_SUFFIXES ".so.5.5.1")  ##TEST

#SET(CMAKE_CXX_FLAGS "-fPIC")



