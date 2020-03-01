#include <QTextStream>
#include <QDateTime>


#include "outputfile.h"
#include "mainwindow.h"


/////////////////////////////////////////////////////////////////
OutputFile::OutputFile()
{
}

/////////////////////////////////////////////////////////////////
void OutputFile::writeData_ascii(QString data)
{
    QString fileName_ascii;
    fileName_ascii = QString("%1/%2_ascii%3")
            .arg(fileDirectory)
            .arg(fileName)
            .arg(LOGFILE_EXTENSION);

    writeDataToFile(fileName_ascii, data);
}

/////////////////////////////////////////////////////////////////
void OutputFile::writeData_hex(QString data)
{
    QString fileName_hex;
    fileName_hex = QString("%1/%2_hex%3")
            .arg(fileDirectory)
            .arg(fileName)
            .arg(LOGFILE_EXTENSION);

    writeDataToFile(fileName_hex, data);
}
/////////////////////////////////////////////////////////////////
bool OutputFile::writeDataToFile(QString thisFileName, QString data)
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
void OutputFile::init(QString directory)
{
    fileDirectory = directory;

    QDateTime dt = QDateTime::currentDateTime();
    QString timeStr = dt.toString(TIME_FORMAT);

    fileName = QString("termik_log_%1").arg(timeStr);
}

/////////////////////////////////////////////////////////////////
