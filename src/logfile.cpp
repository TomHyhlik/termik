#include "logfile.h"
#include "mainwindow.h"

#include <QTextStream>
#include <QDateTime>

/////////////////////////////////////////////////////////////////
LogFile::LogFile(QObject *parent) : QObject(parent)
{
    initialized = false;
}

/////////////////////////////////////////////////////////////////
void LogFile::writeData_ascii(QString data)
{
    QString fileName_ascii = QString("%1_ascii").arg(fileName);
    QFile file(QString("%1/%2%3").arg(fileDirectory)
               .arg(fileName_ascii).arg(FILE_EXTENSION));

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        return;
    }

    QTextStream fileData(&file);

    fileData << data;

    file.flush();
    file.close();
}

/////////////////////////////////////////////////////////////////
void LogFile::writeData_hex(QString data)
{
    QString fileName_hex = QString("%1_hex").arg(fileName);
    QFile file(QString("%1/%2%3").arg(fileDirectory)
               .arg(fileName_hex).arg(FILE_EXTENSION));

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        return;
    }

    QTextStream fileData(&file);

    fileData << data;

    file.flush();
    file.close();
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
