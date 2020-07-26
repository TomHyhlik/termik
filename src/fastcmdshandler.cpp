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

    for (int i = 0; i < 2; i++)
        fastCmds_addCmd();


    for (int i = 0; i < listWidget->count()-1; i++) {
        qDebug() << "CMD" << i << ": " << cmdAt(i);
    }


}

/////////////////////////////////////////////////////////////////
QString FastCmdsHandler::cmdAt(int i)
{
        QListWidgetItem* item = listWidget->item(i);

        if (item != nullptr)
        {
//            Form_fastCmd* fastCmd = dynamic_cast <Form_fastCmd*> (listWidget->itemWidget(item));
//            Form_fastCmd *fastCmd = nullptr;//(Form_fastCmd*)listWidget->itemWidget(item);
            QWidget *w = qobject_cast<QWidget *>(listWidget->itemWidget(item));

            Form_fastCmd* fastCmd = w->findChild<Form_fastCmd*>(OBJNAME);

            if (fastCmd != nullptr) {
                if (fastCmd->lineEdit_cmd.hasFocus())
                    qDebug() << "data: " << fastCmd->lineEdit_cmd.text();
                    return fastCmd->lineEdit_cmd.text();
            } else {
                qDebug() << "fastCmd: " << i << "is NULL";
            }
        } else {
            qDebug() << "Item: " << i << "is NULL";
        }

    return "";
}

/////////////////////////////////////////////////////////////////
void FastCmdsHandler::fastCmds_addCmd()
{
    Form_fastCmd* cmdUi = new Form_fastCmd();
    cmdUi->lineEdit_cmd.setText(tr("Some cmd"));
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
