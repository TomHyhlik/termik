/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_11;
    QTableWidget *tableWidget_shortcuts;
    QGroupBox *groupBox_settings;
    QVBoxLayout *verticalLayout_7;
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
    QTabWidget *tabWidget;
    QWidget *tab_ascii;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit_out_ascii;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_find_ascii;
    QPushButton *pushButton_fnd_ascii;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_in_ascii;
    QWidget *tab_hex;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEdit_out_hex;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_find_hex;
    QPushButton *pushButton_fnd_hex;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_in_hex;
    QWidget *tab_dec;
    QVBoxLayout *verticalLayout_8;
    QTextEdit *textEdit_out_dec;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEdit_find_dec;
    QPushButton *pushButton_fnd_dec;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_in_dec;
    QHBoxLayout *horizontalLayout_script;
    QLabel *label_script;
    QLineEdit *lineEdit_script;
    QComboBox *comboBox_script_dataType;
    QCheckBox *checkBox_script_repeat;
    QSpinBox *spinBox_script_period;
    QPushButton *pushButton_script_run;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(488, 908);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/terminal.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_11 = new QVBoxLayout(centralWidget);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        tableWidget_shortcuts = new QTableWidget(centralWidget);
        tableWidget_shortcuts->setObjectName(QString::fromUtf8("tableWidget_shortcuts"));

        verticalLayout_11->addWidget(tableWidget_shortcuts);

        groupBox_settings = new QGroupBox(centralWidget);
        groupBox_settings->setObjectName(QString::fromUtf8("groupBox_settings"));
        verticalLayout_7 = new QVBoxLayout(groupBox_settings);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        checkBox_autoclear = new QCheckBox(groupBox_settings);
        checkBox_autoclear->setObjectName(QString::fromUtf8("checkBox_autoclear"));

        horizontalLayout_8->addWidget(checkBox_autoclear);

        spinBox_autoclear_maxCharCnt = new QSpinBox(groupBox_settings);
        spinBox_autoclear_maxCharCnt->setObjectName(QString::fromUtf8("spinBox_autoclear_maxCharCnt"));
        spinBox_autoclear_maxCharCnt->setMaximum(100000);

        horizontalLayout_8->addWidget(spinBox_autoclear_maxCharCnt);


        verticalLayout_7->addLayout(horizontalLayout_8);

        checkBox_timeLog = new QCheckBox(groupBox_settings);
        checkBox_timeLog->setObjectName(QString::fromUtf8("checkBox_timeLog"));

        verticalLayout_7->addWidget(checkBox_timeLog);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        checkBox_outputSave = new QCheckBox(groupBox_settings);
        checkBox_outputSave->setObjectName(QString::fromUtf8("checkBox_outputSave"));

        horizontalLayout_7->addWidget(checkBox_outputSave);

        lineEdit_save = new QLineEdit(groupBox_settings);
        lineEdit_save->setObjectName(QString::fromUtf8("lineEdit_save"));

        horizontalLayout_7->addWidget(lineEdit_save);

        pushButton_save = new QPushButton(groupBox_settings);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));

        horizontalLayout_7->addWidget(pushButton_save);


        verticalLayout_7->addLayout(horizontalLayout_7);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        checkBox_prefix = new QCheckBox(groupBox_settings);
        checkBox_prefix->setObjectName(QString::fromUtf8("checkBox_prefix"));

        horizontalLayout_14->addWidget(checkBox_prefix);

        lineEdit_prefix = new QLineEdit(groupBox_settings);
        lineEdit_prefix->setObjectName(QString::fromUtf8("lineEdit_prefix"));

        horizontalLayout_14->addWidget(lineEdit_prefix);


        verticalLayout_7->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        checkBox_suffix = new QCheckBox(groupBox_settings);
        checkBox_suffix->setObjectName(QString::fromUtf8("checkBox_suffix"));

        horizontalLayout_15->addWidget(checkBox_suffix);

        lineEdit_suffix = new QLineEdit(groupBox_settings);
        lineEdit_suffix->setObjectName(QString::fromUtf8("lineEdit_suffix"));

        horizontalLayout_15->addWidget(lineEdit_suffix);


        verticalLayout_7->addLayout(horizontalLayout_15);

        checkBox_clearOutputLine = new QCheckBox(groupBox_settings);
        checkBox_clearOutputLine->setObjectName(QString::fromUtf8("checkBox_clearOutputLine"));

        verticalLayout_7->addWidget(checkBox_clearOutputLine);


        verticalLayout_11->addWidget(groupBox_settings);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab_ascii = new QWidget();
        tab_ascii->setObjectName(QString::fromUtf8("tab_ascii"));
        verticalLayout_5 = new QVBoxLayout(tab_ascii);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        textEdit_out_ascii = new QTextEdit(tab_ascii);
        textEdit_out_ascii->setObjectName(QString::fromUtf8("textEdit_out_ascii"));

        verticalLayout_2->addWidget(textEdit_out_ascii);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_find_ascii = new QLineEdit(tab_ascii);
        lineEdit_find_ascii->setObjectName(QString::fromUtf8("lineEdit_find_ascii"));

        horizontalLayout->addWidget(lineEdit_find_ascii);

        pushButton_fnd_ascii = new QPushButton(tab_ascii);
        pushButton_fnd_ascii->setObjectName(QString::fromUtf8("pushButton_fnd_ascii"));

        horizontalLayout->addWidget(pushButton_fnd_ascii);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit_in_ascii = new QLineEdit(tab_ascii);
        lineEdit_in_ascii->setObjectName(QString::fromUtf8("lineEdit_in_ascii"));

        horizontalLayout_2->addWidget(lineEdit_in_ascii);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_5->addLayout(verticalLayout_2);

        tabWidget->addTab(tab_ascii, QString());
        tab_hex = new QWidget();
        tab_hex->setObjectName(QString::fromUtf8("tab_hex"));
        verticalLayout_6 = new QVBoxLayout(tab_hex);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        textEdit_out_hex = new QTextEdit(tab_hex);
        textEdit_out_hex->setObjectName(QString::fromUtf8("textEdit_out_hex"));

        verticalLayout_3->addWidget(textEdit_out_hex);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit_find_hex = new QLineEdit(tab_hex);
        lineEdit_find_hex->setObjectName(QString::fromUtf8("lineEdit_find_hex"));

        horizontalLayout_3->addWidget(lineEdit_find_hex);

        pushButton_fnd_hex = new QPushButton(tab_hex);
        pushButton_fnd_hex->setObjectName(QString::fromUtf8("pushButton_fnd_hex"));

        horizontalLayout_3->addWidget(pushButton_fnd_hex);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit_in_hex = new QLineEdit(tab_hex);
        lineEdit_in_hex->setObjectName(QString::fromUtf8("lineEdit_in_hex"));

        horizontalLayout_4->addWidget(lineEdit_in_hex);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(verticalLayout_3);

        tabWidget->addTab(tab_hex, QString());
        tab_dec = new QWidget();
        tab_dec->setObjectName(QString::fromUtf8("tab_dec"));
        verticalLayout_8 = new QVBoxLayout(tab_dec);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        textEdit_out_dec = new QTextEdit(tab_dec);
        textEdit_out_dec->setObjectName(QString::fromUtf8("textEdit_out_dec"));

        verticalLayout_8->addWidget(textEdit_out_dec);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lineEdit_find_dec = new QLineEdit(tab_dec);
        lineEdit_find_dec->setObjectName(QString::fromUtf8("lineEdit_find_dec"));

        horizontalLayout_5->addWidget(lineEdit_find_dec);

        pushButton_fnd_dec = new QPushButton(tab_dec);
        pushButton_fnd_dec->setObjectName(QString::fromUtf8("pushButton_fnd_dec"));

        horizontalLayout_5->addWidget(pushButton_fnd_dec);


        verticalLayout_9->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        lineEdit_in_dec = new QLineEdit(tab_dec);
        lineEdit_in_dec->setObjectName(QString::fromUtf8("lineEdit_in_dec"));

        horizontalLayout_6->addWidget(lineEdit_in_dec);


        verticalLayout_9->addLayout(horizontalLayout_6);


        verticalLayout_8->addLayout(verticalLayout_9);

        tabWidget->addTab(tab_dec, QString());

        verticalLayout_11->addWidget(tabWidget);

        horizontalLayout_script = new QHBoxLayout();
        horizontalLayout_script->setSpacing(6);
        horizontalLayout_script->setObjectName(QString::fromUtf8("horizontalLayout_script"));
        label_script = new QLabel(centralWidget);
        label_script->setObjectName(QString::fromUtf8("label_script"));

        horizontalLayout_script->addWidget(label_script);

        lineEdit_script = new QLineEdit(centralWidget);
        lineEdit_script->setObjectName(QString::fromUtf8("lineEdit_script"));

        horizontalLayout_script->addWidget(lineEdit_script);

        comboBox_script_dataType = new QComboBox(centralWidget);
        comboBox_script_dataType->setObjectName(QString::fromUtf8("comboBox_script_dataType"));

        horizontalLayout_script->addWidget(comboBox_script_dataType);

        checkBox_script_repeat = new QCheckBox(centralWidget);
        checkBox_script_repeat->setObjectName(QString::fromUtf8("checkBox_script_repeat"));

        horizontalLayout_script->addWidget(checkBox_script_repeat);

        spinBox_script_period = new QSpinBox(centralWidget);
        spinBox_script_period->setObjectName(QString::fromUtf8("spinBox_script_period"));
        spinBox_script_period->setMaximum(99999);

        horizontalLayout_script->addWidget(spinBox_script_period);

        pushButton_script_run = new QPushButton(centralWidget);
        pushButton_script_run->setObjectName(QString::fromUtf8("pushButton_script_run"));

        horizontalLayout_script->addWidget(pushButton_script_run);


        verticalLayout_11->addLayout(horizontalLayout_script);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_settings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        checkBox_autoclear->setText(QCoreApplication::translate("MainWindow", "Auto clear output, maximum of characters: ", nullptr));
        checkBox_timeLog->setText(QCoreApplication::translate("MainWindow", "Enable time log", nullptr));
        checkBox_outputSave->setText(QCoreApplication::translate("MainWindow", "Save terminal output to:", nullptr));
        pushButton_save->setText(QCoreApplication::translate("MainWindow", "browse", nullptr));
        checkBox_prefix->setText(QCoreApplication::translate("MainWindow", "Enable Tx Prefix:", nullptr));
        checkBox_suffix->setText(QCoreApplication::translate("MainWindow", "Enable Tx Suffix:", nullptr));
        checkBox_clearOutputLine->setText(QCoreApplication::translate("MainWindow", "Clear output line automatically", nullptr));
        pushButton_fnd_ascii->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_ascii), QCoreApplication::translate("MainWindow", "ASCII", nullptr));
        pushButton_fnd_hex->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_hex), QCoreApplication::translate("MainWindow", "HEX", nullptr));
        pushButton_fnd_dec->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_dec), QCoreApplication::translate("MainWindow", "DEC", nullptr));
        label_script->setText(QCoreApplication::translate("MainWindow", "Script:", nullptr));
        checkBox_script_repeat->setText(QCoreApplication::translate("MainWindow", "repeat", nullptr));
        pushButton_script_run->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
