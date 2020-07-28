#ifndef FASTCMDSHANDLER_H
#define FASTCMDSHANDLER_H

#include <QObject>
#include <QListWidget>

#include "form_fastcmd.h"


#define OBJNAME "ObjName"

class FastCmdsHandler : public QObject
{
    Q_OBJECT

    QListWidget *listWidget;

    void addPlusButtonAtTheEnd();
    void addForm(Form_fastCmd*);

public:
    explicit FastCmdsHandler(QListWidget* val);

    Form_fastCmd* cmdAt(int i);
    int count() { return listWidget->count()-1; }

public slots:
    void fastCmds_addCmdBlank();
    void fastCmds_addCmd(FastCmdData cmdData);



signals:
    void Tx(QByteArray);


};

#endif // FASTCMDSHANDLER_H
