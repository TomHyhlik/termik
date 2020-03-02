#include <QTextStream>
#include <QDateTime>


#include "outputfile.h"
#include "mainwindow.h"


/////////////////////////////////////////////////////////////////
OutputFile::OutputFile(QString val) : dir(val)
{
    QDateTime dt = QDateTime::currentDateTime();
    QString timeStr = dt.toString(TIME_FORMAT);

    fileName = QString("termik_log_%1").arg(timeStr);
}

/////////////////////////////////////////////////////////////////
bool OutputFile::writeData_ascii(QString data)
{
    return writeDataToFile(QString("%1/%2_ascii%3")
                           .arg(dir)
                           .arg(fileName)
                           .arg(LOGFILE_EXTENSION),
                           data);
}

/////////////////////////////////////////////////////////////////
bool OutputFile::writeData_hex(QString data)
{
    return writeDataToFile(QString("%1/%2_hex%3")
                           .arg(dir)
                           .arg(fileName)
                           .arg(LOGFILE_EXTENSION),
                           data);
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
