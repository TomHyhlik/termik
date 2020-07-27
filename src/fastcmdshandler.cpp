#include "fastcmdshandler.h"
#include "mainwindow.h"
#include "form_fastcmd.h"

#include <QPushButton>
#include <QHBoxLayout>

/////////////////////////////////////////////////////////////////
FastCmdsHandler::FastCmdsHandler(QListWidget* val)
    : listWidget(val)
{
    addPlusButtonAtTheEnd();

    /* add cmd */
    for (int i = 0; i < 2; i++)
        fastCmds_addCmd();

    /* add cmds ti json */
//    for (int i = 0; i < count(); i++) {
//        Form_fastCmd* cmdForm = cmdAt(i);
//        if (cmdForm != nullptr) {
//            qDebug() << "CMD" << i << ": " << cmdForm->lineEdit_cmd.text();
//        }
//    }
}

/////////////////////////////////////////////////////////////////
Form_fastCmd* FastCmdsHandler::cmdAt(int i)
{
    QWidget *w = qobject_cast <QWidget*> (listWidget->itemWidget(listWidget->item(i)));
    Form_fastCmd* fastCmd = w->findChild <Form_fastCmd*> (OBJNAME);

    if (fastCmd != nullptr) {
//            qDebug() << "data: " << fastCmd->lineEdit_cmd.text();
        return fastCmd;
    }
//        qDebug() << "fastCmd: " << i << "is NULL";
    return nullptr;
}

/////////////////////////////////////////////////////////////////
void FastCmdsHandler::fastCmds_addCmd()
{
    Form_fastCmd* cmdUi = new Form_fastCmd();
    cmdUi->lineEdit_name.setText(tr("Cmd %1").arg(count()));
    connect(cmdUi, &Form_fastCmd::Tx,
            this, &FastCmdsHandler::Tx);

    cmdUi->setObjectName(OBJNAME);

    QListWidgetItem *item = new QListWidgetItem();
    item->setText("lol");

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);

    layout->addWidget(cmdUi);

    QWidget *widget = new QWidget();

    widget->setLayout(layout);
    item->setSizeHint(QSize(0, 40));

    if (listWidget->count() > 0) {
        listWidget->insertItem(listWidget->count() - 1, item);
        listWidget->setItemWidget(item, widget);
    } else {
        listWidget->addItem(item);
        listWidget->setItemWidget(item,widget);
    }

    cmdUi->lineEdit_cmd.setFocus();
    listWidget->show();
}
/////////////////////////////////////////////////////////////////
void FastCmdsHandler::addPlusButtonAtTheEnd()
{
    QPushButton* addNewFastCmd = new QPushButton();
    addNewFastCmd->setText("+");
    QListWidgetItem *item = new QListWidgetItem();
    connect(addNewFastCmd, &QPushButton::clicked,
            this, &FastCmdsHandler::fastCmds_addCmd);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);

    layout->addWidget(addNewFastCmd);

    QWidget *widget = new QWidget();

    widget->setLayout(layout);
    item->setSizeHint(QSize(0, 40));

    listWidget->addItem(item);
    listWidget->setItemWidget(item, widget);
}

/////////////////////////////////////////////////////////////////
