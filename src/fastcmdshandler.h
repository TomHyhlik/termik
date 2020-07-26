#ifndef FASTCMDSHANDLER_H
#define FASTCMDSHANDLER_H

#include <QObject>
#include <QListWidget>


#define OBJNAME "ObjName"

class FastCmdsHandler : public QObject
{
    Q_OBJECT


    QListWidget *listWidget;

    void addPlusButtonAtTheEnd();

public:
    explicit FastCmdsHandler(QListWidget* val);

    QString cmdAt(int i);

public slots:
    void fastCmds_addCmd();



signals:
    void Tx(QByteArray);


};

#endif // FASTCMDSHANDLER_H
