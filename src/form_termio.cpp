#include "form_termio.h"
#include "ui_form_termio.h"
#include "mainwindow.h"

Form_termIO::Form_termIO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_termIO)
{
    ui->setupUi(this);



//    ui->verticalLayout->addWidget(&textEdit_out);
//    ui->verticalLayout->addWidget(&lineEdit_in);



//    ui->textEdit_out->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
//                                        .arg(COLOR_WHITE).arg(COLOR_BLACK));
//    ui->lineEdit_in->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
//                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));

//    textEdit_out->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
//                                        .arg(COLOR_WHITE).arg(COLOR_BLACK));
//    lineEdit_in->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
//                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));



}

Form_termIO::~Form_termIO()
{
    delete ui;
}
