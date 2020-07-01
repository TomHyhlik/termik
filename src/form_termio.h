#ifndef FORM_TERMIO_H
#define FORM_TERMIO_H

#include <QWidget>

#include <QTextEdit>
#include <QLineEdit>

namespace Ui {
class Form_termIO;
}

class Form_termIO : public QWidget
{
    Q_OBJECT

public:
    explicit Form_termIO(QWidget *parent = nullptr);
    ~Form_termIO();

    Ui::Form_termIO *ui;

    QTextEdit textEdit_out;
    QLineEdit lineEdit_in;



};

#endif // FORM_TERMIO_H
