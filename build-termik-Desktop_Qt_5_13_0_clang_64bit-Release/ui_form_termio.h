/********************************************************************************
** Form generated from reading UI file 'form_termio.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_TERMIO_H
#define UI_FORM_TERMIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_termIO
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *Form_termIO)
    {
        if (Form_termIO->objectName().isEmpty())
            Form_termIO->setObjectName(QString::fromUtf8("Form_termIO"));
        Form_termIO->resize(277, 564);
        verticalLayout = new QVBoxLayout(Form_termIO);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(Form_termIO);

        QMetaObject::connectSlotsByName(Form_termIO);
    } // setupUi

    void retranslateUi(QWidget *Form_termIO)
    {
        Form_termIO->setWindowTitle(QCoreApplication::translate("Form_termIO", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_termIO: public Ui_Form_termIO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_TERMIO_H
