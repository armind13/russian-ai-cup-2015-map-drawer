#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T12:33:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AiCupMapDrawer
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h \
    Constants.h

FORMS    += MainWindow.ui

RESOURCES += \
    Tiles.qrc
