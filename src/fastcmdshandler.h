#ifndef FASTCMDSHANDLER_H
#define FASTCMDSHANDLER_H

#include <QObject>
#include <QListWidget>



class fastCmdsHandler : public QObject
{
    Q_OBJECT


    QListWidget *listWidget;


public:
    explicit fastCmdsHandler(QListWidget* val);




signals:



};

#endif // FASTCMDSHANDLER_H
