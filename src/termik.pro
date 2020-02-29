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
        cliarghandler.cpp \
        communication.cpp \
        communicationworker.cpp \
        dataconverter.cpp \
        log.cpp \
        logfile.cpp \
        main.cpp \
        mainwindow.cpp \
        dialog_connect.cpp \
        networkscan.cpp \
        networkworker.cpp \
        networkwparam.cpp \
        runscript.cpp \
        runscriptparam.cpp \
        saveconfiguration.cpp \
        serialworker.cpp \
        serialwparam.cpp \
        tcpworker.cpp \
        utils.cpp

HEADERS += \
        cliarghandler.h \
        communication.h \
        communicationworker.h \
        dataconverter.h \
        log.h \
        logfile.h \
        mainwindow.h \
        dialog_connect.h \
        networkscan.h \
        networkworker.h \
        networkwparam.h \
        runscript.h \
        runscriptparam.h \
        saveconfiguration.h \
        serialworker.h \
        serialwparam.h \
        tcpworker.h

FORMS += \
        mainwindow.ui \
        dialog_connect.ui

RESOURCES += \
    resources.qrc

