#include <QTextStream>
#include <QDateTime>


#include "logfile.h"
#include "mainwindow.h"


/////////////////////////////////////////////////////////////////
LogFile::LogFile(QObject *parent) : QObject(parent)
{
    initialized = false;
}

/////////////////////////////////////////////////////////////////
void LogFile::writeData_ascii(QString data)
{
    QString fileName_ascii;
    fileName_ascii = QString("%1/%2_ascii%3")
            .arg(fileDirectory)
            .arg(fileName)
            .arg(LOGFILE_EXTENSION);

    writeDataToFile(fileName_ascii, data);
}

/////////////////////////////////////////////////////////////////
void LogFile::writeData_hex(QString data)
{
    QString fileName_hex;
    fileName_hex = QString("%1/%2_hex%3")
            .arg(fileDirectory)
            .arg(fileName)
            .arg(LOGFILE_EXTENSION);

    writeDataToFile(fileName_hex, data);
}
/////////////////////////////////////////////////////////////////
bool LogFile::writeDataToFile(QString thisFileName, QString data)
{
    QFile file(thisFileName);

    if (file.open(QIODevice::ReadWrite |
                   QIODevice::Text |
                   QIODevice::Append)) {
        QTextStream fileData(&file);
        fileData << data;
        file.flush();
        file.close();
        return true;

    } else {
        return false;
    }
}

/////////////////////////////////////////////////////////////////
void LogFile::init(QString directory)
{
    fileDirectory = directory;

    QDateTime dt = QDateTime::currentDateTime();
    QString timeStr = dt.toString(TIME_FORMAT);

    fileName = QString("termik_log_%1").arg(timeStr);
}

/////////////////////////////////////////////////////////////////
