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
        appcfgparam.cpp \
        cliarghandler.cpp \
        communication.cpp \
        communicationworker.cpp \
    communicworkerfactory.cpp \
        dataconverter.cpp \
    form_termio.cpp \
        uilog.cpp \
        main.cpp \
        mainwindow.cpp \
        dialog_connect.cpp \
        networkprotocol.cpp \
        networkscan.cpp \
        networkworker.cpp \
        networkwparam.cpp \
        outputfile.cpp \
        protocol_udp.cpp \
        runscript.cpp \
        runscriptparam.cpp \
        saveconfiguration.cpp \
        serialworker.cpp \
        serialwparam.cpp \
        protocol_tcp_client.cpp \
        protocol_tcp_server.cpp \


HEADERS += \
        appcfgparam.h \
        cliarghandler.h \
        communication.h \
        communicationworker.h \
    communicworkerfactory.h \
        dataconverter.h \
    form_termio.h \
        uilog.h \
        mainwindow.h \
        dialog_connect.h \
        networkprotocol.h \
        networkscan.h \
        networkworker.h \
        networkwparam.h \
        outputfile.h \
        protocol_udp.h \
        runscript.h \
        runscriptparam.h \
        saveconfiguration.h \
        serialworker.h \
        serialwparam.h \
        shortcuts.h \
        utils_tabWidget.h \
        protocol_tcp_client.h \
        protocol_tcp_server.h \



FORMS += \
        form_termio.ui \
        mainwindow.ui \
        dialog_connect.ui

RESOURCES += \
    resources.qrc

