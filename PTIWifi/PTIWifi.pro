#-------------------------------------------------
#
# Project created by QtCreator 2017-07-15T10:54:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PTIWifi
TEMPLATE = app


SOURCES += main.cpp\
        interfacedialog.cpp

HEADERS  += interfacedialog.h

FORMS    += interfacedialog.ui

LIBS = -L /usr/local/lib/ -l tins -lpthread
