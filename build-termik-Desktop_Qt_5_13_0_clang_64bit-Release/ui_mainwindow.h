/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget_shortcuts;
    QTabWidget *tabWidget_settings;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkBox_autoclear;
    QSpinBox *spinBox_autoclear_maxCharCnt;
    QCheckBox *checkBox_timeLog;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_outputSave;
    QLineEdit *lineEdit_save;
    QPushButton *pushButton_save;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *checkBox_prefix;
    QLineEdit *lineEdit_prefix;
    QHBoxLayout *horizontalLayout_15;
    QCheckBox *checkBox_suffix;
    QLineEdit *lineEdit_suffix;
    QCheckBox *checkBox_clearOutputLine;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_scriptPath;
    QPushButton *pushButton_scriptOpen;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_scriptDataFormat;
    QComboBox *comboBox_scriptDataFormat;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_scriptTransmissionPeriod;
    QSpinBox *spinBox_scriptTransmissionPeriod;
    QCheckBox *checkBox_scriptRepeatEnable;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_scriptRun;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSplitter *splitter;
    QListWidget *listWidget_fastCmds;
    QTabWidget *tabWidget;
    QWidget *tab_ascii;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_tabwidget_ascii;
    QWidget *tab_hex;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_tabwidget_hex;
    QWidget *tab_dec;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_tabwidget_dec;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(601, 908);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/terminal.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableWidget_shortcuts = new QTableWidget(centralWidget);
        tableWidget_shortcuts->setObjectName(QString::fromUtf8("tableWidget_shortcuts"));

        verticalLayout_2->addWidget(tableWidget_shortcuts);

        tabWidget_settings = new QTabWidget(centralWidget);
        tabWidget_settings->setObjectName(QString::fromUtf8("tabWidget_settings"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget_settings->sizePolicy().hasHeightForWidth());
        tabWidget_settings->setSizePolicy(sizePolicy);
        tabWidget_settings->setMaximumSize(QSize(16777215, 245));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        checkBox_autoclear = new QCheckBox(tab_2);
        checkBox_autoclear->setObjectName(QString::fromUtf8("checkBox_autoclear"));

        horizontalLayout_8->addWidget(checkBox_autoclear);

        spinBox_autoclear_maxCharCnt = new QSpinBox(tab_2);
        spinBox_autoclear_maxCharCnt->setObjectName(QString::fromUtf8("spinBox_autoclear_maxCharCnt"));
        spinBox_autoclear_maxCharCnt->setMaximum(100000);

        horizontalLayout_8->addWidget(spinBox_autoclear_maxCharCnt);


        verticalLayout->addLayout(horizontalLayout_8);

        checkBox_timeLog = new QCheckBox(tab_2);
        checkBox_timeLog->setObjectName(QString::fromUtf8("checkBox_timeLog"));

        verticalLayout->addWidget(checkBox_timeLog);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        checkBox_outputSave = new QCheckBox(tab_2);
        checkBox_outputSave->setObjectName(QString::fromUtf8("checkBox_outputSave"));

        horizontalLayout_7->addWidget(checkBox_outputSave);

        lineEdit_save = new QLineEdit(tab_2);
        lineEdit_save->setObjectName(QString::fromUtf8("lineEdit_save"));

        horizontalLayout_7->addWidget(lineEdit_save);

        pushButton_save = new QPushButton(tab_2);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));

        horizontalLayout_7->addWidget(pushButton_save);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        checkBox_prefix = new QCheckBox(tab_2);
        checkBox_prefix->setObjectName(QString::fromUtf8("checkBox_prefix"));

        horizontalLayout_14->addWidget(checkBox_prefix);

        lineEdit_prefix = new QLineEdit(tab_2);
        lineEdit_prefix->setObjectName(QString::fromUtf8("lineEdit_prefix"));

        horizontalLayout_14->addWidget(lineEdit_prefix);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        checkBox_suffix = new QCheckBox(tab_2);
        checkBox_suffix->setObjectName(QString::fromUtf8("checkBox_suffix"));

        horizontalLayout_15->addWidget(checkBox_suffix);

        lineEdit_suffix = new QLineEdit(tab_2);
        lineEdit_suffix->setObjectName(QString::fromUtf8("lineEdit_suffix"));

        horizontalLayout_15->addWidget(lineEdit_suffix);


        verticalLayout->addLayout(horizontalLayout_15);

        checkBox_clearOutputLine = new QCheckBox(tab_2);
        checkBox_clearOutputLine->setObjectName(QString::fromUtf8("checkBox_clearOutputLine"));

        verticalLayout->addWidget(checkBox_clearOutputLine);

        tabWidget_settings->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_3 = new QVBoxLayout(tab_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_scriptPath = new QLineEdit(tab_3);
        lineEdit_scriptPath->setObjectName(QString::fromUtf8("lineEdit_scriptPath"));

        horizontalLayout->addWidget(lineEdit_scriptPath);

        pushButton_scriptOpen = new QPushButton(tab_3);
        pushButton_scriptOpen->setObjectName(QString::fromUtf8("pushButton_scriptOpen"));
        pushButton_scriptOpen->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton_scriptOpen);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_scriptDataFormat = new QLabel(tab_3);
        label_scriptDataFormat->setObjectName(QString::fromUtf8("label_scriptDataFormat"));

        horizontalLayout_2->addWidget(label_scriptDataFormat);

        comboBox_scriptDataFormat = new QComboBox(tab_3);
        comboBox_scriptDataFormat->setObjectName(QString::fromUtf8("comboBox_scriptDataFormat"));
        comboBox_scriptDataFormat->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(comboBox_scriptDataFormat);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_scriptTransmissionPeriod = new QLabel(tab_3);
        label_scriptTransmissionPeriod->setObjectName(QString::fromUtf8("label_scriptTransmissionPeriod"));

        horizontalLayout_3->addWidget(label_scriptTransmissionPeriod);

        spinBox_scriptTransmissionPeriod = new QSpinBox(tab_3);
        spinBox_scriptTransmissionPeriod->setObjectName(QString::fromUtf8("spinBox_scriptTransmissionPeriod"));
        spinBox_scriptTransmissionPeriod->setMaximumSize(QSize(100, 16777215));
        spinBox_scriptTransmissionPeriod->setMaximum(99999);

        horizontalLayout_3->addWidget(spinBox_scriptTransmissionPeriod);


        verticalLayout_3->addLayout(horizontalLayout_3);

        checkBox_scriptRepeatEnable = new QCheckBox(tab_3);
        checkBox_scriptRepeatEnable->setObjectName(QString::fromUtf8("checkBox_scriptRepeatEnable"));
        checkBox_scriptRepeatEnable->setMaximumSize(QSize(10000, 16777215));

        verticalLayout_3->addWidget(checkBox_scriptRepeatEnable);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        pushButton_scriptRun = new QPushButton(tab_3);
        pushButton_scriptRun->setObjectName(QString::fromUtf8("pushButton_scriptRun"));
        pushButton_scriptRun->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(pushButton_scriptRun);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget_settings->addTab(tab_3, QString());

        verticalLayout_2->addWidget(tabWidget_settings);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        listWidget_fastCmds = new QListWidget(splitter);
        listWidget_fastCmds->setObjectName(QString::fromUtf8("listWidget_fastCmds"));
        splitter->addWidget(listWidget_fastCmds);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab_ascii = new QWidget();
        tab_ascii->setObjectName(QString::fromUtf8("tab_ascii"));
        verticalLayout_5 = new QVBoxLayout(tab_ascii);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_tabwidget_ascii = new QVBoxLayout();
        verticalLayout_tabwidget_ascii->setSpacing(6);
        verticalLayout_tabwidget_ascii->setObjectName(QString::fromUtf8("verticalLayout_tabwidget_ascii"));

        verticalLayout_5->addLayout(verticalLayout_tabwidget_ascii);

        tabWidget->addTab(tab_ascii, QString());
        tab_hex = new QWidget();
        tab_hex->setObjectName(QString::fromUtf8("tab_hex"));
        verticalLayout_6 = new QVBoxLayout(tab_hex);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_tabwidget_hex = new QVBoxLayout();
        verticalLayout_tabwidget_hex->setSpacing(6);
        verticalLayout_tabwidget_hex->setObjectName(QString::fromUtf8("verticalLayout_tabwidget_hex"));

        verticalLayout_6->addLayout(verticalLayout_tabwidget_hex);

        tabWidget->addTab(tab_hex, QString());
        tab_dec = new QWidget();
        tab_dec->setObjectName(QString::fromUtf8("tab_dec"));
        verticalLayout_8 = new QVBoxLayout(tab_dec);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_tabwidget_dec = new QVBoxLayout();
        verticalLayout_tabwidget_dec->setSpacing(6);
        verticalLayout_tabwidget_dec->setObjectName(QString::fromUtf8("verticalLayout_tabwidget_dec"));

        verticalLayout_8->addLayout(verticalLayout_tabwidget_dec);

        tabWidget->addTab(tab_dec, QString());
        splitter->addWidget(tabWidget);

        verticalLayout_2->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget_settings->setCurrentIndex(0);
        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        checkBox_autoclear->setText(QCoreApplication::translate("MainWindow", "Auto clear output, maximum of characters: ", nullptr));
        checkBox_timeLog->setText(QCoreApplication::translate("MainWindow", "Enable time log", nullptr));
        checkBox_outputSave->setText(QCoreApplication::translate("MainWindow", "Save terminal output to:", nullptr));
        pushButton_save->setText(QCoreApplication::translate("MainWindow", "browse", nullptr));
        checkBox_prefix->setText(QCoreApplication::translate("MainWindow", "Enable Tx Prefix:", nullptr));
        checkBox_suffix->setText(QCoreApplication::translate("MainWindow", "Enable Tx Suffix:", nullptr));
        checkBox_clearOutputLine->setText(QCoreApplication::translate("MainWindow", "Clear output line automatically", nullptr));
        tabWidget_settings->setTabText(tabWidget_settings->indexOf(tab_2), QCoreApplication::translate("MainWindow", "General", nullptr));
        pushButton_scriptOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        label_scriptDataFormat->setText(QCoreApplication::translate("MainWindow", "Data format: ", nullptr));
        label_scriptTransmissionPeriod->setText(QCoreApplication::translate("MainWindow", "Transmission period:", nullptr));
        checkBox_scriptRepeatEnable->setText(QCoreApplication::translate("MainWindow", "repeat", nullptr));
        pushButton_scriptRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        tabWidget_settings->setTabText(tabWidget_settings->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Script", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_ascii), QCoreApplication::translate("MainWindow", "ASCII", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_hex), QCoreApplication::translate("MainWindow", "HEX", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_dec), QCoreApplication::translate("MainWindow", "DEC", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
