#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T21:49:36
#
#-------------------------------------------------

QT       += core gui
QT       += network

QMAKE_CXXFLAGS_DEBUG +=-Wall -pedantic

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
