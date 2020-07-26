/********************************************************************************
** Form generated from reading UI file 'dialog_connect.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_CONNECT_H
#define UI_DIALOG_CONNECT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_connect
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_serial;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget_serialPorts;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_serialPortName;
    QLineEdit *lineEdit_serialPortName;
    QLabel *label_baudRate;
    QComboBox *comboBox_baudRate;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_dataBits;
    QComboBox *comboBox_dataBits;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_stopBits;
    QComboBox *comboBox_stopBits;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_flowControl;
    QComboBox *comboBox_flowControl;
    QLabel *label_parity;
    QComboBox *comboBox_parity;
    QWidget *tab_network;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_networkProtocol;
    QComboBox *comboBox_networkProtocol;
    QCheckBox *checkBox_enableNetworkScan;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_11;
    QGroupBox *groupBox_network_rx;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout;
    QLabel *label_port_rx;
    QLineEdit *lineEdit_selectedAddr_rx;
    QSpinBox *spinBox_ipPort_Rx;
    QTableWidget *tableWidget_addr_rx;
    QGroupBox *groupBox_network_tx;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_ipAddr_port_tx;
    QLineEdit *lineEdit_selectedAddr_tx;
    QSpinBox *spinBox_ipPort_Tx;
    QTableWidget *tableWidget_addr_tx;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog_connect)
    {
        if (Dialog_connect->objectName().isEmpty())
            Dialog_connect->setObjectName(QString::fromUtf8("Dialog_connect"));
        Dialog_connect->resize(1017, 430);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/terminal.png"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog_connect->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(Dialog_connect);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(Dialog_connect);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_serial = new QWidget();
        tab_serial->setObjectName(QString::fromUtf8("tab_serial"));
        verticalLayout_2 = new QVBoxLayout(tab_serial);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableWidget_serialPorts = new QTableWidget(tab_serial);
        tableWidget_serialPorts->setObjectName(QString::fromUtf8("tableWidget_serialPorts"));

        verticalLayout_2->addWidget(tableWidget_serialPorts);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_serialPortName = new QLabel(tab_serial);
        label_serialPortName->setObjectName(QString::fromUtf8("label_serialPortName"));

        horizontalLayout_12->addWidget(label_serialPortName);

        lineEdit_serialPortName = new QLineEdit(tab_serial);
        lineEdit_serialPortName->setObjectName(QString::fromUtf8("lineEdit_serialPortName"));
        lineEdit_serialPortName->setMinimumSize(QSize(180, 0));

        horizontalLayout_12->addWidget(lineEdit_serialPortName);


        horizontalLayout_5->addLayout(horizontalLayout_12);

        label_baudRate = new QLabel(tab_serial);
        label_baudRate->setObjectName(QString::fromUtf8("label_baudRate"));

        horizontalLayout_5->addWidget(label_baudRate);

        comboBox_baudRate = new QComboBox(tab_serial);
        comboBox_baudRate->setObjectName(QString::fromUtf8("comboBox_baudRate"));
        comboBox_baudRate->setMinimumSize(QSize(90, 0));
        comboBox_baudRate->setEditable(false);

        horizontalLayout_5->addWidget(comboBox_baudRate);


        horizontalLayout_8->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_dataBits = new QLabel(tab_serial);
        label_dataBits->setObjectName(QString::fromUtf8("label_dataBits"));

        horizontalLayout_7->addWidget(label_dataBits);

        comboBox_dataBits = new QComboBox(tab_serial);
        comboBox_dataBits->setObjectName(QString::fromUtf8("comboBox_dataBits"));
        comboBox_dataBits->setMinimumSize(QSize(50, 0));

        horizontalLayout_7->addWidget(comboBox_dataBits);


        horizontalLayout_8->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_stopBits = new QLabel(tab_serial);
        label_stopBits->setObjectName(QString::fromUtf8("label_stopBits"));

        horizontalLayout_9->addWidget(label_stopBits);

        comboBox_stopBits = new QComboBox(tab_serial);
        comboBox_stopBits->setObjectName(QString::fromUtf8("comboBox_stopBits"));
        comboBox_stopBits->setMinimumSize(QSize(60, 0));

        horizontalLayout_9->addWidget(comboBox_stopBits);


        horizontalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_flowControl = new QLabel(tab_serial);
        label_flowControl->setObjectName(QString::fromUtf8("label_flowControl"));

        horizontalLayout_10->addWidget(label_flowControl);

        comboBox_flowControl = new QComboBox(tab_serial);
        comboBox_flowControl->setObjectName(QString::fromUtf8("comboBox_flowControl"));
        comboBox_flowControl->setMinimumSize(QSize(70, 0));

        horizontalLayout_10->addWidget(comboBox_flowControl);


        horizontalLayout_8->addLayout(horizontalLayout_10);

        label_parity = new QLabel(tab_serial);
        label_parity->setObjectName(QString::fromUtf8("label_parity"));

        horizontalLayout_8->addWidget(label_parity);

        comboBox_parity = new QComboBox(tab_serial);
        comboBox_parity->setObjectName(QString::fromUtf8("comboBox_parity"));

        horizontalLayout_8->addWidget(comboBox_parity);


        horizontalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab_serial, QString());
        tab_network = new QWidget();
        tab_network->setObjectName(QString::fromUtf8("tab_network"));
        verticalLayout_3 = new QVBoxLayout(tab_network);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_networkProtocol = new QLabel(tab_network);
        label_networkProtocol->setObjectName(QString::fromUtf8("label_networkProtocol"));

        horizontalLayout_4->addWidget(label_networkProtocol);

        comboBox_networkProtocol = new QComboBox(tab_network);
        comboBox_networkProtocol->setObjectName(QString::fromUtf8("comboBox_networkProtocol"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_networkProtocol->sizePolicy().hasHeightForWidth());
        comboBox_networkProtocol->setSizePolicy(sizePolicy);
        comboBox_networkProtocol->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(comboBox_networkProtocol);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        checkBox_enableNetworkScan = new QCheckBox(tab_network);
        checkBox_enableNetworkScan->setObjectName(QString::fromUtf8("checkBox_enableNetworkScan"));

        horizontalLayout_6->addWidget(checkBox_enableNetworkScan);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        groupBox_network_rx = new QGroupBox(tab_network);
        groupBox_network_rx->setObjectName(QString::fromUtf8("groupBox_network_rx"));
        verticalLayout_9 = new QVBoxLayout(groupBox_network_rx);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_port_rx = new QLabel(groupBox_network_rx);
        label_port_rx->setObjectName(QString::fromUtf8("label_port_rx"));

        horizontalLayout->addWidget(label_port_rx);

        lineEdit_selectedAddr_rx = new QLineEdit(groupBox_network_rx);
        lineEdit_selectedAddr_rx->setObjectName(QString::fromUtf8("lineEdit_selectedAddr_rx"));

        horizontalLayout->addWidget(lineEdit_selectedAddr_rx);

        spinBox_ipPort_Rx = new QSpinBox(groupBox_network_rx);
        spinBox_ipPort_Rx->setObjectName(QString::fromUtf8("spinBox_ipPort_Rx"));

        horizontalLayout->addWidget(spinBox_ipPort_Rx);


        verticalLayout_9->addLayout(horizontalLayout);

        tableWidget_addr_rx = new QTableWidget(groupBox_network_rx);
        tableWidget_addr_rx->setObjectName(QString::fromUtf8("tableWidget_addr_rx"));

        verticalLayout_9->addWidget(tableWidget_addr_rx);


        horizontalLayout_11->addWidget(groupBox_network_rx);

        groupBox_network_tx = new QGroupBox(tab_network);
        groupBox_network_tx->setObjectName(QString::fromUtf8("groupBox_network_tx"));
        verticalLayout_8 = new QVBoxLayout(groupBox_network_tx);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_ipAddr_port_tx = new QLabel(groupBox_network_tx);
        label_ipAddr_port_tx->setObjectName(QString::fromUtf8("label_ipAddr_port_tx"));

        horizontalLayout_3->addWidget(label_ipAddr_port_tx);

        lineEdit_selectedAddr_tx = new QLineEdit(groupBox_network_tx);
        lineEdit_selectedAddr_tx->setObjectName(QString::fromUtf8("lineEdit_selectedAddr_tx"));

        horizontalLayout_3->addWidget(lineEdit_selectedAddr_tx);

        spinBox_ipPort_Tx = new QSpinBox(groupBox_network_tx);
        spinBox_ipPort_Tx->setObjectName(QString::fromUtf8("spinBox_ipPort_Tx"));

        horizontalLayout_3->addWidget(spinBox_ipPort_Tx);


        verticalLayout_8->addLayout(horizontalLayout_3);

        tableWidget_addr_tx = new QTableWidget(groupBox_network_tx);
        tableWidget_addr_tx->setObjectName(QString::fromUtf8("tableWidget_addr_tx"));

        verticalLayout_8->addWidget(tableWidget_addr_tx);


        horizontalLayout_11->addWidget(groupBox_network_tx);


        verticalLayout_3->addLayout(horizontalLayout_11);

        tabWidget->addTab(tab_network, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(Dialog_connect);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Dialog_connect);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_connect, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_connect, SLOT(reject()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Dialog_connect);
    } // setupUi

    void retranslateUi(QDialog *Dialog_connect)
    {
        Dialog_connect->setWindowTitle(QCoreApplication::translate("Dialog_connect", "Dialog", nullptr));
        label_serialPortName->setText(QCoreApplication::translate("Dialog_connect", "Name", nullptr));
        label_baudRate->setText(QCoreApplication::translate("Dialog_connect", "Baud rate", nullptr));
        label_dataBits->setText(QCoreApplication::translate("Dialog_connect", "Data bits", nullptr));
        label_stopBits->setText(QCoreApplication::translate("Dialog_connect", "Stop bits", nullptr));
        label_flowControl->setText(QCoreApplication::translate("Dialog_connect", "Flow control", nullptr));
        label_parity->setText(QCoreApplication::translate("Dialog_connect", "Parity", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_serial), QCoreApplication::translate("Dialog_connect", "Tab 1", nullptr));
        label_networkProtocol->setText(QCoreApplication::translate("Dialog_connect", "Protocol:", nullptr));
        checkBox_enableNetworkScan->setText(QCoreApplication::translate("Dialog_connect", "Enable network scan", nullptr));
        groupBox_network_rx->setTitle(QCoreApplication::translate("Dialog_connect", "Rx", nullptr));
        label_port_rx->setText(QCoreApplication::translate("Dialog_connect", "Selected:", nullptr));
        groupBox_network_tx->setTitle(QCoreApplication::translate("Dialog_connect", "Tx", nullptr));
        label_ipAddr_port_tx->setText(QCoreApplication::translate("Dialog_connect", "Selected:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_network), QCoreApplication::translate("Dialog_connect", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_connect: public Ui_Dialog_connect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_CONNECT_H
