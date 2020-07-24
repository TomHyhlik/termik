#include "form_fastcmd.h"
#include "ui_form_fastcmd.h"

#include "mainwindow.h"

#include <QPushButton>

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

    ui->horizontalLayout->addWidget(&lineEdit_cmd);
    ui->horizontalLayout->addWidget(&comboBox_dataFormat);
    ui->horizontalLayout->addWidget(&pushButton_send);

    connect(&pushButton_send, &QPushButton::clicked,
            this, &Form_fastCmd::sendPressed);


}
void Form_fastCmd::sendPressed()
{
    emit send(QByteArray(lineEdit_cmd.text().toUtf8()));
}

Form_fastCmd::~Form_fastCmd()
{
    delete ui;
}
