#!/bin/bash

#For use with Linux based operating systems such as Raspbian, ubuntu, Linux Mint etc. 
#Script used to install software needed for software development of the Biosignal PI using apt-get

sudo apt-get update
sudo apt-get upgrade -y 
sudo apt-get install -y build-essential mesa-common-dev cmake libfontconfig1-dev libdbus-1-dev libfreetype6-dev libudev-dev libasound2-dev libavcodec-dev libavformat-dev libswscale-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev gstreamer-tools gstreamer0.10-plugins-good gstreamer0.10-plugins-bad libicu-dev libsqlite3-dev libxslt1-dev libssl-dev perl gperf bison flex libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync0-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev doxygen

