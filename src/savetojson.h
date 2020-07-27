#ifndef SAVETOJSON_H
#define SAVETOJSON_H

#include <QObject>

class SaveToJson : public QObject
{
    Q_OBJECT

protected:
    QString fileName;

    virtual bool jsonData_parse(QByteArray) = 0;
    virtual QByteArray jsonData_make() = 0;

public:

    bool read();
    bool write();


signals:

};

#endif // SAVETOJSON_H
