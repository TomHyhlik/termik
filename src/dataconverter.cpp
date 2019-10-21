#include "dataconverter.h"

dataConverter::dataConverter()
{

}

/////////////////////////////////////////////////////////////////
void dataConverter::setStrAscii(QString arg)
{
    pureData = arg.toUtf8();
}

/////////////////////////////////////////////////////////////////
void dataConverter::setStrHex(QString arg)
{
    pureData = QByteArray::fromHex(arg.toUtf8());
}

/////////////////////////////////////////////////////////////////
void dataConverter::setStrDec(QString arg)
{
    bool ok;
    QString element;
    for (int i = 0; i <= arg.size(); i += DIGIT_NUM_DEC) {
        element = arg.mid(i, DIGIT_NUM_DEC);
        if (element.size() != 0) {
            while (element.size() < DIGIT_NUM_DEC) {
                element.append("0");
            }
            quint32 num = element.toUInt(&ok, 10);
            pureData.append(qint8(num));
        }
    }
}
/////////////////////////////////////////////////////////////////
QByteArray dataConverter::getByteArray()
{
    return pureData;
}
/////////////////////////////////////////////////////////////////
void dataConverter::setByteArray(QByteArray arg)
{
    pureData = arg;
}

/////////////////////////////////////////////////////////////////
QString dataConverter::getStrAscii()
{
    QString out;
    for (int i = 0; i < pureData.size(); i++) {
        out.append(pureData.at(i));
    }
    return out;
}
/////////////////////////////////////////////////////////////////
QString dataConverter::getStrHex()
{
    QString out;
    for (int i = 0; i < pureData.size(); i++) {
        QString numStr = QString::number(quint8(pureData.at(i)), 16);
        while(numStr.size() < DIGIT_NUM_HEX){
            numStr.prepend("0");
        }
        out.append(QString("%1 ").arg(numStr));
    }
    return out;
}
/////////////////////////////////////////////////////////////////
QString dataConverter::getStrDec()
{
    QString out;
    for (int i = 0; i < pureData.size(); i++) {
        QString numStr = QString::number(quint8(pureData.at(i)), 10);
        while(numStr.size() < DIGIT_NUM_DEC){
            numStr.prepend("0");
        }
        out.append(QString("%1 ").arg(numStr));
    }
    return out;
}

/////////////////////////////////////////////////////////////////

























