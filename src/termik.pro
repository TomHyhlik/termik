#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T22:22:45
#
#-------------------------------------------------


QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = termik
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        txtfile.cpp \
        dialog_connect.cpp \
        networkworker.cpp \
        serialworker.cpp

HEADERS += \
        handlearguments.h \
        mainwindow.h \
        txtfile.h \
        dialog_connect.h \
        networkworker.h \
        serialworker.h

FORMS += \
        mainwindow.ui \
        dialog_connect.ui

