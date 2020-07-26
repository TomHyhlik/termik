#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include "mainwindow.h"

#include <QByteArray>
#include <QString>



enum dataFormat {
    data_ascii = 0, data_hex, data_dec, //data_bin
};


class dataConverter
{
    QByteArray pureData;

public:
    dataConverter() {};
    dataConverter(QByteArray val)
        : pureData(val) {}

    void setStrAscii(QString arg);
    void setStrHex(QString);
    void setStrDec(QString);
    void setStrOfIndex(int index, QString data);


    void setByteArray(QByteArray);
    QByteArray getByteArray();


    QString getStrAscii();
    QString getStrHex();
    QString getStrDec();

    QString getStrOfIndex(int);



};

#endif // DATACONVERTER_H
