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
        dataconverter.cpp \
        logfile.cpp \
        main.cpp \
        mainwindow.cpp \
        dialog_connect.cpp \
        networkworker.cpp \
        runscript.cpp \
        saveconfiguration.cpp \
        serialworker.cpp

HEADERS += \
        dataconverter.h \
        handlearguments.h \
        logfile.h \
        mainwindow.h \
        dialog_connect.h \
        networkworker.h \
        runscript.h \
        saveconfiguration.h \
        serialworker.h

FORMS += \
        mainwindow.ui \
        dialog_connect.ui

RESOURCES += \
    resources.qrc

