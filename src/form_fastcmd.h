#ifndef FORM_FASTCMD_H
#define FORM_FASTCMD_H

#include <QWidget>

#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>


namespace Ui {
class Form_fastCmd;
}


struct FastCmdData
{
    QString name;
    QString cmd;
    int format;
};


class Form_fastCmd : public QWidget
{
    Q_OBJECT

public:
    explicit Form_fastCmd(QWidget *parent = nullptr);
    ~Form_fastCmd();

    Ui::Form_fastCmd *ui;

    QLineEdit lineEdit_name;
    QLineEdit lineEdit_cmd;
    QComboBox comboBox_dataFormat;
    QPushButton pushButton_send;
    QPushButton pushButton_showSettings;

//    QString getDataCmd() { return data.cmd; }
//    int getDataFormat() { return data.format; }
//    void setDataCmd(QString cmd) { data.cmd = cmd; }
//    void setDataFormat(int format) { data.format = format; }

    FastCmdData getData();

private slots:
    void sendPressed();


signals:
    void Tx(QByteArray);


};

#endif // FORM_FASTCMD_H
