#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include <QObject>
#include <QFile>

#define  LOGFILE_EXTENSION         ".txt"




class OutputFile : public QObject
{
    Q_OBJECT


    QString fileName;
    bool initialized;
    bool writeDataToFile(QString fileName, QString data);

public:
    OutputFile();


signals:

public slots:

    void writeData_ascii(QString data);
    void writeData_hex(QString data);

    void init(QString directory);



};

#endif // OUTPUTFILE_H
