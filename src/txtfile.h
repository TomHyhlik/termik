#ifndef TXTFILE_H
#define TXTFILE_H

#include <QObject>
#include <QFile>
#include <QTextStream>





class txtFile : public QObject
{
    Q_OBJECT
public:
    explicit txtFile(QObject *parent = nullptr);
    void write(QString data);

signals:

public slots:


private:

};

#endif // TXTFILE_H
