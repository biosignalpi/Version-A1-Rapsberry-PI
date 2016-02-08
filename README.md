BioSignal-Pi
============

[Link to Software Documentation](http://biosignalpi.github.io/Version-A1-Rapsberry-PI)

============
Biosignal PI aim is to provide a flexible and affordable open-source platform and tools for physiological and biological measurements such as blood pressure, blood glucose, weight, body composition, activity monitoring, and brain and cardiac activity.In first step, electrocardiogram (ECG) with wide usage in diagnosing and monitoring of heart disease and even in monitoring the autonomic nervous system through heart-rate variability (HRV) is developed.

This version provides 5-12 leads ECG and respiration measurement system based on Raspberry PI, a credit-card-size single-board computer, and ADAS1000. ADAS1000 is introduced by Analog Devices includes all the components necessary to perform a five-lead ECG digital conversion with respiration and pacemaker-artefact detection in a single chip.



#System Requirements
In order to be able to cross-compile the Raspberry Pi(RPI) from an workstation it is neccessary to utilize a cross-compiler this project has used the arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian toolchain. 
Cloned from https://github.com/raspberrypi/tools

To build the Biosignal PI software the system needs to have the following software and libraries installed:
* QT5 (Biosignal PI has been tested with  5.5 and 5.6 both older versions of QT5 might work.) 
* qwt 6.1.2
* cmake 3.0.3
* bcm2835 1.46 c-library used for controlling to GPIO-pins
* libpifacecad c-library used for PiFaceCad
* libmcp23s17 c-library used for PiFaceCad

#Building the Biosignal PI software
The software is built through the use of CMake.
 $ mkdir [buildFolder]  
The buildFolder is just an example name this can be set to anything. 
 $ cd [buildFolder]
 $ cmake -C ../[local-settings-file].cmake ../src/
local-settings-file is a file that should be set to tell CMake about the path to the needed dependecies see the different .cmake files in the main folder for example.
 $ make 

 

#To build the Documentation
 $ make docs 
This will create the documentation in the folder Documentation

# Build tests
 $ make tests


# For information on how to setup the workstation for cross-compilation and installing Qt se








