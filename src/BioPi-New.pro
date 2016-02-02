#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T12:48:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BioPi-New
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model.cpp \
    devicemanager.cpp

HEADERS  += mainwindow.h \
    model.h \
    devicemanager.h

FORMS    += mainwindow.ui
