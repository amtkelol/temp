QT += core gui network widgets

TARGET = tcp
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    packetgenerator.cpp \
    tcpsocket.cpp \
    mainwindow.cpp

HEADERS += \
    packetgenerator.h \
    tcpsocket.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

