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
        interfacedialog.cpp \
    deauthattackwindow.cpp \
    beaconsniffer.cpp

HEADERS  += interfacedialog.h \
    deauthattackwindow.h \
    beaconsniffer.h \
    linux.h

FORMS    += interfacedialog.ui \
    deauthattackwindow.ui

LIBS = -L /usr/local/lib/ -l tins -lpthread
