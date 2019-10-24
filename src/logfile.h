#ifndef LOGFILE_H
#define LOGFILE_H

#include <QObject>

#include <QFile>



#define  FILE_EXTENSION         ".txt"



class LogFile : public QObject
{
    Q_OBJECT

    QString fileName;
    QString fileDirectory;
    bool initialized;

public:
    explicit LogFile(QObject *parent = nullptr);

signals:

public slots:

    void writeData_ascii(QString data);
    void writeData_hex(QString data);

    void init(QString directory);



};

#endif // LOGFILE_H
