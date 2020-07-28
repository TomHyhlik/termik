#include "form_fastcmd.h"
#include "ui_form_fastcmd.h"

#include "mainwindow.h"
#include "dataconverter.h"

#include <QPushButton>

/////////////////////////////////////////////////////////////////
Form_fastCmd::Form_fastCmd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_fastCmd)
{
    ui->setupUi(this);

    pushButton_send.setFixedSize(QSize(50, 25));
    comboBox_dataFormat.setFixedSize(QSize(75, 25));

    pushButton_send.setText(">");
    pushButton_showSettings.setText(":");

    comboBox_dataFormat.addItem(TITLE_DATA_ASCII);
    comboBox_dataFormat.addItem(TITLE_DATA_HEX);

    //    pushButton_showSettings.setFixedSize(QSize(20, 25));

    /* pushbuttons */
    pushButton_send.setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                  .arg(COLOR_WHITE).arg(COLOR_GRAY0));
    pushButton_showSettings.setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                          .arg(COLOR_WHITE).arg(COLOR_GRAY0));
    comboBox_dataFormat.setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                      .arg(COLOR_WHITE).arg(COLOR_BLACK));
    lineEdit_cmd.setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                               .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->horizontalLayout->addWidget(&lineEdit_name);
    ui->horizontalLayout->addWidget(&lineEdit_cmd);
    ui->horizontalLayout->addWidget(&comboBox_dataFormat);
    ui->horizontalLayout->addWidget(&pushButton_send);

    connect(&pushButton_send, &QPushButton::clicked,
            this, &Form_fastCmd::sendPressed);
    connect(&lineEdit_cmd, &QLineEdit::returnPressed,
            this, &Form_fastCmd::sendPressed);

}

/////////////////////////////////////////////////////////////////
FastCmdData Form_fastCmd::getData()
{
    FastCmdData data;
    data.cmd = lineEdit_cmd.text();
    data.name = lineEdit_name.text();
    data.format = comboBox_dataFormat.currentIndex();
    return data;
}

/////////////////////////////////////////////////////////////////
void Form_fastCmd::sendPressed()
{
    dataConverter conv;
    conv.setStrOfIndex(
                title_dataFormat.indexOf(comboBox_dataFormat.currentText()),
                lineEdit_cmd.text());

    emit Tx(conv.getByteArray());
}

/////////////////////////////////////////////////////////////////
Form_fastCmd::~Form_fastCmd()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////
