#ifndef FORM_FASTCMD_H
#define FORM_FASTCMD_H

#include <QWidget>

#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>


namespace Ui {
class Form_fastCmd;
}

class Form_fastCmd : public QWidget
{
    Q_OBJECT

public:
    explicit Form_fastCmd(QWidget *parent = nullptr);
    ~Form_fastCmd();

    QLineEdit lineEdit_cmd;

    QComboBox comboBox_dataFormat;
    QPushButton pushButton_send;
    QPushButton pushButton_showSettings;


    Ui::Form_fastCmd *ui;

private slots:
    void sendPressed();


signals:
    void send(QByteArray);





};

#endif // FORM_FASTCMD_H
