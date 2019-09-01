# termik
A terminal for data transmission via serial or network
I had to make my own, cause none of the available tools does not include all the features I need and also this one can be recompiled for Mac, Linux and Windows.

## Description
Everything is done using shortcuts which is shown after pressing F1.
Transmit data in the terminal is done by pressing Enter.


## todo:
    prepsat nasledujici funkce, je to moc napraseny
        void MainWindow::keyEnterPressed()
        void MainWindow::terminalOutUpdate(terminalData_t dataKind, QByteArray data)
    pridat spousteni programu pres cmd s argumenty