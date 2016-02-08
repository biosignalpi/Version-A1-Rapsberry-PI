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
./configure -confirm-license -developer-build -opensource -no-gtkstyle -nomake examples -nomake tests --optimized-qmake  > outputConfigure.txt 2> errorsConfigure.txt
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
