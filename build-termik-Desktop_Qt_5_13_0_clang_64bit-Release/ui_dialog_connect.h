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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
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
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_name;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout;
    QComboBox *comboBox_portName;
    QLabel *label_portDescription;
    QLabel *label_manufacturer;
    QLabel *label_serialNumber;
    QLabel *label_location;
    QLabel *label_vendorIdentifier;
    QLabel *label_productIdentifier;
    QGroupBox *groupBox_parameters;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_baudRate;
    QComboBox *comboBox_baudRate;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_dataBits;
    QComboBox *comboBox_dataBits;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_parity;
    QComboBox *comboBox_parity;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_stopBits;
    QComboBox *comboBox_stopBits;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_flowControl;
    QComboBox *comboBox_flowControl;
    QWidget *tab_network;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_9;
    QTableWidget *tableWidget_addr_rx;
    QHBoxLayout *horizontalLayout;
    QLabel *label_port_rx;
    QLineEdit *lineEdit_selectedAddr_rx;
    QSpinBox *spinBox_ipPort_Rx;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_8;
    QTableWidget *tableWidget_addr_tx;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_ipAddr_port_tx;
    QLineEdit *lineEdit_selectedAddr_tx;
    QSpinBox *spinBox_ipPort_Tx;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_networkProtocol;
    QComboBox *comboBox_networkProtocol;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog_connect)
    {
        if (Dialog_connect->objectName().isEmpty())
            Dialog_connect->setObjectName(QString::fromUtf8("Dialog_connect"));
        Dialog_connect->resize(835, 389);
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
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox_name = new QGroupBox(tab_serial);
        groupBox_name->setObjectName(QString::fromUtf8("groupBox_name"));
        verticalLayout_5 = new QVBoxLayout(groupBox_name);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox_portName = new QComboBox(groupBox_name);
        comboBox_portName->setObjectName(QString::fromUtf8("comboBox_portName"));
        comboBox_portName->setEditable(true);

        gridLayout->addWidget(comboBox_portName, 0, 0, 1, 1);

        label_portDescription = new QLabel(groupBox_name);
        label_portDescription->setObjectName(QString::fromUtf8("label_portDescription"));

        gridLayout->addWidget(label_portDescription, 1, 0, 1, 1);

        label_manufacturer = new QLabel(groupBox_name);
        label_manufacturer->setObjectName(QString::fromUtf8("label_manufacturer"));

        gridLayout->addWidget(label_manufacturer, 2, 0, 1, 1);

        label_serialNumber = new QLabel(groupBox_name);
        label_serialNumber->setObjectName(QString::fromUtf8("label_serialNumber"));

        gridLayout->addWidget(label_serialNumber, 3, 0, 1, 1);

        label_location = new QLabel(groupBox_name);
        label_location->setObjectName(QString::fromUtf8("label_location"));

        gridLayout->addWidget(label_location, 4, 0, 1, 1);

        label_vendorIdentifier = new QLabel(groupBox_name);
        label_vendorIdentifier->setObjectName(QString::fromUtf8("label_vendorIdentifier"));

        gridLayout->addWidget(label_vendorIdentifier, 5, 0, 1, 1);

        label_productIdentifier = new QLabel(groupBox_name);
        label_productIdentifier->setObjectName(QString::fromUtf8("label_productIdentifier"));

        gridLayout->addWidget(label_productIdentifier, 6, 0, 1, 1);


        verticalLayout_5->addLayout(gridLayout);


        horizontalLayout_2->addWidget(groupBox_name);

        groupBox_parameters = new QGroupBox(tab_serial);
        groupBox_parameters->setObjectName(QString::fromUtf8("groupBox_parameters"));
        verticalLayout_6 = new QVBoxLayout(groupBox_parameters);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_baudRate = new QLabel(groupBox_parameters);
        label_baudRate->setObjectName(QString::fromUtf8("label_baudRate"));

        horizontalLayout_5->addWidget(label_baudRate);

        comboBox_baudRate = new QComboBox(groupBox_parameters);
        comboBox_baudRate->setObjectName(QString::fromUtf8("comboBox_baudRate"));
        comboBox_baudRate->setMinimumSize(QSize(50, 0));
        comboBox_baudRate->setEditable(false);

        horizontalLayout_5->addWidget(comboBox_baudRate);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_dataBits = new QLabel(groupBox_parameters);
        label_dataBits->setObjectName(QString::fromUtf8("label_dataBits"));

        horizontalLayout_7->addWidget(label_dataBits);

        comboBox_dataBits = new QComboBox(groupBox_parameters);
        comboBox_dataBits->setObjectName(QString::fromUtf8("comboBox_dataBits"));

        horizontalLayout_7->addWidget(comboBox_dataBits);


        verticalLayout_7->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_parity = new QLabel(groupBox_parameters);
        label_parity->setObjectName(QString::fromUtf8("label_parity"));

        horizontalLayout_8->addWidget(label_parity);

        comboBox_parity = new QComboBox(groupBox_parameters);
        comboBox_parity->setObjectName(QString::fromUtf8("comboBox_parity"));

        horizontalLayout_8->addWidget(comboBox_parity);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_stopBits = new QLabel(groupBox_parameters);
        label_stopBits->setObjectName(QString::fromUtf8("label_stopBits"));

        horizontalLayout_9->addWidget(label_stopBits);

        comboBox_stopBits = new QComboBox(groupBox_parameters);
        comboBox_stopBits->setObjectName(QString::fromUtf8("comboBox_stopBits"));

        horizontalLayout_9->addWidget(comboBox_stopBits);


        verticalLayout_7->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_flowControl = new QLabel(groupBox_parameters);
        label_flowControl->setObjectName(QString::fromUtf8("label_flowControl"));

        horizontalLayout_10->addWidget(label_flowControl);

        comboBox_flowControl = new QComboBox(groupBox_parameters);
        comboBox_flowControl->setObjectName(QString::fromUtf8("comboBox_flowControl"));

        horizontalLayout_10->addWidget(comboBox_flowControl);


        verticalLayout_7->addLayout(horizontalLayout_10);


        verticalLayout_6->addLayout(verticalLayout_7);


        horizontalLayout_2->addWidget(groupBox_parameters);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab_serial, QString());
        tab_network = new QWidget();
        tab_network->setObjectName(QString::fromUtf8("tab_network"));
        verticalLayout_3 = new QVBoxLayout(tab_network);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        groupBox = new QGroupBox(tab_network);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_9 = new QVBoxLayout(groupBox);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        tableWidget_addr_rx = new QTableWidget(groupBox);
        tableWidget_addr_rx->setObjectName(QString::fromUtf8("tableWidget_addr_rx"));

        verticalLayout_9->addWidget(tableWidget_addr_rx);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_port_rx = new QLabel(groupBox);
        label_port_rx->setObjectName(QString::fromUtf8("label_port_rx"));

        horizontalLayout->addWidget(label_port_rx);

        lineEdit_selectedAddr_rx = new QLineEdit(groupBox);
        lineEdit_selectedAddr_rx->setObjectName(QString::fromUtf8("lineEdit_selectedAddr_rx"));

        horizontalLayout->addWidget(lineEdit_selectedAddr_rx);

        spinBox_ipPort_Rx = new QSpinBox(groupBox);
        spinBox_ipPort_Rx->setObjectName(QString::fromUtf8("spinBox_ipPort_Rx"));

        horizontalLayout->addWidget(spinBox_ipPort_Rx);


        verticalLayout_9->addLayout(horizontalLayout);


        horizontalLayout_11->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab_network);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_8 = new QVBoxLayout(groupBox_2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        tableWidget_addr_tx = new QTableWidget(groupBox_2);
        tableWidget_addr_tx->setObjectName(QString::fromUtf8("tableWidget_addr_tx"));

        verticalLayout_8->addWidget(tableWidget_addr_tx);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_ipAddr_port_tx = new QLabel(groupBox_2);
        label_ipAddr_port_tx->setObjectName(QString::fromUtf8("label_ipAddr_port_tx"));

        horizontalLayout_3->addWidget(label_ipAddr_port_tx);

        lineEdit_selectedAddr_tx = new QLineEdit(groupBox_2);
        lineEdit_selectedAddr_tx->setObjectName(QString::fromUtf8("lineEdit_selectedAddr_tx"));

        horizontalLayout_3->addWidget(lineEdit_selectedAddr_tx);

        spinBox_ipPort_Tx = new QSpinBox(groupBox_2);
        spinBox_ipPort_Tx->setObjectName(QString::fromUtf8("spinBox_ipPort_Tx"));

        horizontalLayout_3->addWidget(spinBox_ipPort_Tx);


        verticalLayout_8->addLayout(horizontalLayout_3);


        horizontalLayout_11->addWidget(groupBox_2);


        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_networkProtocol = new QLabel(tab_network);
        label_networkProtocol->setObjectName(QString::fromUtf8("label_networkProtocol"));

        horizontalLayout_4->addWidget(label_networkProtocol);

        comboBox_networkProtocol = new QComboBox(tab_network);
        comboBox_networkProtocol->setObjectName(QString::fromUtf8("comboBox_networkProtocol"));
        comboBox_networkProtocol->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(comboBox_networkProtocol);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_6);

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
        groupBox_name->setTitle(QCoreApplication::translate("Dialog_connect", "Name", nullptr));
        label_portDescription->setText(QCoreApplication::translate("Dialog_connect", "Description:", nullptr));
        label_manufacturer->setText(QCoreApplication::translate("Dialog_connect", "Manufacturer:", nullptr));
        label_serialNumber->setText(QCoreApplication::translate("Dialog_connect", "Serial number:", nullptr));
        label_location->setText(QCoreApplication::translate("Dialog_connect", "Location:", nullptr));
        label_vendorIdentifier->setText(QCoreApplication::translate("Dialog_connect", "Vendor identifier:", nullptr));
        label_productIdentifier->setText(QCoreApplication::translate("Dialog_connect", "Product identifier:", nullptr));
        groupBox_parameters->setTitle(QCoreApplication::translate("Dialog_connect", "Parameters", nullptr));
        label_baudRate->setText(QCoreApplication::translate("Dialog_connect", "Baud rate", nullptr));
        label_dataBits->setText(QCoreApplication::translate("Dialog_connect", "Data bits", nullptr));
        label_parity->setText(QCoreApplication::translate("Dialog_connect", "Parity", nullptr));
        label_stopBits->setText(QCoreApplication::translate("Dialog_connect", "Stop bits", nullptr));
        label_flowControl->setText(QCoreApplication::translate("Dialog_connect", "Flow control", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_serial), QCoreApplication::translate("Dialog_connect", "Tab 1", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog_connect", "Rx", nullptr));
        label_port_rx->setText(QCoreApplication::translate("Dialog_connect", "Selected:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog_connect", "Tx", nullptr));
        label_ipAddr_port_tx->setText(QCoreApplication::translate("Dialog_connect", "Selected:", nullptr));
        label_networkProtocol->setText(QCoreApplication::translate("Dialog_connect", "Protocol:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_network), QCoreApplication::translate("Dialog_connect", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_connect: public Ui_Dialog_connect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_CONNECT_H
