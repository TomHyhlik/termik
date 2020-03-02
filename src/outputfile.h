#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include <QObject>
#include <QFile>

#define  LOGFILE_EXTENSION         ".txt"




class OutputFile : public QObject
{
    Q_OBJECT

    QString dir;
    QString fileName;
    bool initialized;
    bool writeDataToFile(QString fileName, QString data);

public:
    OutputFile(QString val);


public slots:
    bool writeData_ascii(QString data);
    bool writeData_hex(QString data);

};

#endif // OUTPUTFILE_H
