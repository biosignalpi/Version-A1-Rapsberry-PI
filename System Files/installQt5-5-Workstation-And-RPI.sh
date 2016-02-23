#!/bin/bash

#For use with Linux based operating systems such as ubuntu, Linux Mint etc. 
#Script used to install QT5.5 from git source onto workstation
#Installs all neccessary modules for BioSignal PI
#Check ErrorList.txt for possible errors occured during compilation

git clone git://code.qt.io/qt/qt5.git
cd qt5
git checkout 5.5
perl init-repository
cd qtbase
./configure -release -device linux-rasp-pi2-g++ -device-option CROSS_COMPILE=$HOME/raspberry/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf- -opengl es2 -optimized-qmake  -make libs -opensource -confirm-license -reduce-relocations -reduce-exports -sysroot /mnt/rasp-rootfs -prefix /usr/local/qt5 -hostprefix /usr/local/qt5
pwd
echo "make" 
make > outputMake.txt 2> ../ErrorList.txt
for module in qtimageformats qtsvg qtxmlpatterns qtdeclarative qtgraphicaleffects qtmultimedia qtquick1 qtscript qtwebkit qtsensors qt3d qtlocation qtconnectivity; do
cd ../$module
(echo "----------------"  "-------------------" && \
	echo "-------------" $module "----------------" \
	 && echo "---------------" "----------------") >> ../ErrorList.txt
echo "#############Errors qmake #########" >> ../ErrorList.txt
echo $module " qmake"
../qtbase/bin/qmake > outputQmake.txt 2>> ../ErrorList.txt
echo "#############Errors make #########" >> ../ErrorList.txt
echo $module "make"
make -j4 > outputMake.txt 2>> ../ErrorList.txt
#echo "#############Errors sudo make install #########" >> ../ErrorList.txt
#sudo make install > outputMakeInstall.txt 2>> ../ErrorList.txt
echo $module
done
