#ifndef FASTCMDSHANDLER_H
#define FASTCMDSHANDLER_H

#include <QObject>
#include <QListWidget>



class FastCmdsHandler : public QObject
{
    Q_OBJECT


    QListWidget *listWidget;

    void addPlusButtonAtTheEnd();

public:
    explicit FastCmdsHandler(QListWidget* val);

    int hasFocus();

public slots:
    void fastCmds_addCmd();



signals:
    void Tx(QByteArray);


};

#endif // FASTCMDSHANDLER_H
