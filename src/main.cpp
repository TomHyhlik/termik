#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /* put the application arguments into QList
        and pass it to the Mainwindow class */
    QStringList arguments;
    for (int i = 0; i < argc; i++) {
        arguments << argv[i];
    }

    QApplication a(argc, argv);

    MainWindow w(arguments);

    w.show();

    return a.exec();
}
