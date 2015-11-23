QT += core network
QT -= gui

TARGET = tcp
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    packetgenerator.cpp \
    tcpsocket.cpp

HEADERS += \
    packetgenerator.h \
    tcpsocket.h

