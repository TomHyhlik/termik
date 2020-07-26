/********************************************************************************
** Form generated from reading UI file 'form_fastcmd.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_FASTCMD_H
#define UI_FORM_FASTCMD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_fastCmd
{
public:
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;

    void setupUi(QWidget *Form_fastCmd)
    {
        if (Form_fastCmd->objectName().isEmpty())
            Form_fastCmd->setObjectName(QString::fromUtf8("Form_fastCmd"));
        Form_fastCmd->resize(325, 38);
        horizontalLayout = new QHBoxLayout(Form_fastCmd);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        horizontalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Form_fastCmd);

        QMetaObject::connectSlotsByName(Form_fastCmd);
    } // setupUi

    void retranslateUi(QWidget *Form_fastCmd)
    {
        Form_fastCmd->setWindowTitle(QCoreApplication::translate("Form_fastCmd", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_fastCmd: public Ui_Form_fastCmd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_FASTCMD_H
