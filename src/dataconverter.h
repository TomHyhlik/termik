#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include "mainwindow.h"

#include <QByteArray>
#include <QString>

class dataConverter
{
    QByteArray pureData;


public:
    dataConverter();

    void setStrAscii(QString arg);
    void setStrHex(QString);
    void setStrDec(QString);


    void setByteArray(QByteArray);
    QByteArray getByteArray();


    QString getStrAscii();
    QString getStrHex();
    QString getStrDec();





};

#endif // DATACONVERTER_H
