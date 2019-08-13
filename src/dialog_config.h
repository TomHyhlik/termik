#ifndef DIALOG_CONFIG_H
#define DIALOG_CONFIG_H

#include <QDialog>

#include <QMap>
#include "serialworker.h"


class SerialWorker;

namespace Ui {
class dialog_config;
}

class dialog_config : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_config(QWidget *parent = 0);
    ~dialog_config();

    void setSw(SerialWorker *value);        // access SerialWorker class
    SerialWorker *getSw() const;

    void tab_input_init();
    void tab_output_init();

    bool autoClearIn = false;



public slots:
    void on_pushButton_refresh_clicked();


private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_comboBox_portName_currentTextChanged(const QString &arg1);

private:
    Ui::dialog_config *ui;
    SerialWorker *sw;

    /* get opposite value of the searched element in the map */
    int getFirstMapVal(QMap<int,QString> m, QString label);



    /* tab port init */
    void tab_port_init();
    QMap<int,QString> baudRateS;    // create maps
    QMap<int,QString> dataBitsS;
    QMap<int,QString> parityS;
    QMap<int,QString> stopBitsS;
    QMap<int,QString> flowControlS;
    void fillBaudRate();            // fill maps
    void fillDataBits();
    void fillParity();
    void fillstopBits();
    void fillflowControl();



signals:
    void portConfigDisplay(QString, QString, QString, QString, QString, QString);
    void connected(bool);


 //  QList<int> baudRate;
};

#endif // dialog_config_H
