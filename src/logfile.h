#ifndef LOGFILE_H
#define LOGFILE_H

#include <QObject>
#include <QFile>



#define  LOGFILE_EXTENSION         ".txt"




class LogFile : public QObject
{
    Q_OBJECT

    QString fileDirectory;

    QString fileName;
    bool initialized;
    bool writeDataToFile(QString fileName, QString data);

public:
    explicit LogFile(QObject *parent = nullptr);

    void setFileDirectory(QString val) {
        fileDirectory = val;
    }

    QString getFileDirectory() {
        return fileDirectory;
    }



signals:

public slots:

    void writeData_ascii(QString data);
    void writeData_hex(QString data);

    void init(QString directory);



};

#endif // LOGFILE_H
