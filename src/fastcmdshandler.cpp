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
}

/////////////////////////////////////////////////////////////////
Form_fastCmd* FastCmdsHandler::cmdAt(int i)
{
    QWidget *w = qobject_cast <QWidget*> (listWidget->itemWidget(listWidget->item(i)));
    Form_fastCmd* fastCmd = w->findChild <Form_fastCmd*> (OBJNAME);
    return fastCmd;
}

/////////////////////////////////////////////////////////////////
void FastCmdsHandler::fastCmds_addCmd(FastCmdData cmdData)
{
    Form_fastCmd* cmdUi = new Form_fastCmd();

    cmdUi->lineEdit_cmd.setText(cmdData.cmd);
    cmdUi->lineEdit_name.setText(cmdData.name);

//    cmdUi->comboBox_dataFormat.setCurrentText(cmdData.format); todo

    addForm(cmdUi);
}

/////////////////////////////////////////////////////////////////
void FastCmdsHandler::fastCmds_addCmdBlank()
{
    Form_fastCmd* cmdUi = new Form_fastCmd();
    cmdUi->lineEdit_name.setText(tr("Cmd_%1").arg(count()));
    addForm(cmdUi);
}

/////////////////////////////////////////////////////////////////
void FastCmdsHandler::addForm(Form_fastCmd* cmdUi)
{
    connect(cmdUi, &Form_fastCmd::Tx,
            this, &FastCmdsHandler::Tx);
    cmdUi->setObjectName(OBJNAME);
    QListWidgetItem *item = new QListWidgetItem();
//    item->setText("lol");
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
    QPushButton* pushButton_addNewCmd = new QPushButton();
    pushButton_addNewCmd->setText("+");
    QListWidgetItem *item = new QListWidgetItem();
    connect(pushButton_addNewCmd, &QPushButton::clicked,
            this, &FastCmdsHandler::fastCmds_addCmdBlank);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->addWidget(pushButton_addNewCmd);
    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    item->setSizeHint(QSize(0, 40));
    listWidget->addItem(item);
    listWidget->setItemWidget(item, widget);
}

/////////////////////////////////////////////////////////////////
