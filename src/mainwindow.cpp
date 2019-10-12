/*
 * colors set from this source:
 * https://en.wikipedia.org/wiki/Web_colors
 */

#include <QShortcut>
#include <QSerialPortInfo>
#include <QTimer>
#include <QFileDialog>

#include <QTextStream>
#include <QFile>
#include <QDataStream>

#include <QDateTime>
#include <QDateTimeEdit>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include "dialog_connect.h"


/////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QStringList arguments, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tick.start();

    sw = new SerialWorker(this);
    connect(sw, SIGNAL(dataReceived()), this, SLOT(dataArrived()));

    nw = new NetworkWorker(this);
    connect(nw, SIGNAL(dataReceived()), this, SLOT(dataArrived()));

    dialog_connect = new Dialog_connect(this);
    //    connect(dialog_connect, SIGNAL(log(int, QString)), this, SLOT(log(int, QString)));
    dialog_connect->setSw(sw);
    dialog_connect->setNw(nw);
    dialog_connect->init();

    connect(dialog_connect, SIGNAL(connectVia_serial()), this, SLOT(connectVia_serial()));
    connect(dialog_connect, SIGNAL(connectVia_network()), this, SLOT(connectVia_network()));


    /*************************** Shortcuts ****************************/
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this, SLOT(showFindUi()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(EscPressed()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), this, SLOT(moveCursorToEnd()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_L), this, SLOT(clearOutput()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Comma), this, SLOT(showConnectionSettings()));
    //    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), this, SLOT(on_pushButton_connect_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_3), this, SLOT(focus_3()));
    new QShortcut(QKeySequence(Qt::Key_F1), this, SLOT(showHelp()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(showWrap()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(showSaveSettings()));
    new QShortcut(QKeySequence(Qt::Key_Enter), this, SLOT(keyEnterPressed()));
    new QShortcut(QKeySequence(Qt::Key_Return), this, SLOT(keyEnterPressed()));
    new QShortcut(QKeySequence(Qt::Key_Up), this, SLOT(keyUpPressed()));
    new QShortcut(QKeySequence(Qt::Key_Down), this, SLOT(keyDownPressed()));

    uiInit();
    config.connectionType = none;

    handleAppArguments(arguments);
}
//////////////////////////////////////////////////////////////////////
/// \brief MainWindow::handleAppArguments
/// \param arguments is the QStringList of terminal passed arguments
///     This function is called in MainWindow initialization
///     it controls the syntax of app terminal arguments and calls
///     handleAppArguments_setParam() to use these parameters
void MainWindow::handleAppArguments(QStringList arguments)
{
    /* the first argument is the cmd of calling the app */
    arguments.removeFirst();

//    /* at first look if there is long argument */
//    if (arguments.first() == ARG_HELP_LONG) {
//        handleAppArguments_printHelp();
//        exit(0);
//    }

    /* now look at the pairs of arguments */
    while (!arguments.isEmpty())
    {
        QString command, passedData;

        command = arguments.at(0);
        arguments.removeFirst();

            /* check if the command has syntax like: -x */
            if (command.at(0) == ARG_PREFIX_SHORT &&
                    command.size() == 2) {
                if (!arguments.isEmpty()) {
                    passedData = arguments.at(0);
                    arguments.removeFirst();

                    handleAppArguments_setParam(command, passedData);
                } else {
                    qDebug() << "ERROR: No passed data for command " << command;
                    handleAppArguments_printHelp();
                }
            } else {
                qDebug() << "ERROR: Failed to handle input arguments, "
                            "the command has invalid syntax.";
                handleAppArguments_printHelp();
            }
    }
}

void MainWindow::handleAppArguments_setParam(QString command, QString passedData)
{
    qDebug() << "Setting" << command << " to " << passedData;
    char cmdChar = command.toUtf8().at(1);

    /* todo: continue here, implement the setting of parameters bellow */

    switch (cmdChar)
    {
    case ARG_NETWORK_IPADDR:

        break;
    case ARG_NETWORK_TXPORT:

        break;
    case ARG_NETWORK_RXPORT:

        break;


    case ARG_SERIAL_PORTNAME:

        break;
    case ARG_SERIAL_BAUDRATE:

        break;
    case ARG_SERIAL_DATABITS:

        break;
    case ARG_SERIAL_PARITY:

        break;
    case ARG_SERIAL_STOPBITS:

        break;
    case ARG_SERIAL_FLOWCONTROL:

        break;
    default:
        qDebug() << "ERROR: Unknown command -" << command;
    }
}

void MainWindow::handleAppArguments_printHelp()
{
    qDebug("");
    qDebug() << "*** The options are as follows:";

    qDebug() << "\n\t- Parameters for connection via serial: ";
    handleAppArguments_printHelp_wrap(ARG_SERIAL_PORTNAME,      "serial port name");
    handleAppArguments_printHelp_wrap(ARG_SERIAL_BAUDRATE,      "baud rate");
    handleAppArguments_printHelp_wrap(ARG_SERIAL_DATABITS,      "data bits");
    handleAppArguments_printHelp_wrap(ARG_SERIAL_PARITY,        "parity");
    handleAppArguments_printHelp_wrap(ARG_SERIAL_STOPBITS,      "stop bits");
    handleAppArguments_printHelp_wrap(ARG_SERIAL_FLOWCONTROL,   "flow control");

    qDebug() << "\n\t- Parameters for connection via network: ";
    handleAppArguments_printHelp_wrap(ARG_NETWORK_IPADDR,   "IP address");
    handleAppArguments_printHelp_wrap(ARG_NETWORK_TXPORT,   "Tx port");
    handleAppArguments_printHelp_wrap(ARG_NETWORK_RXPORT,   "Rx port");

    qDebug("");
}

void MainWindow::handleAppArguments_printHelp_wrap(char cmd, QString argTitle)
{
    // todo: odstranit warning mozna...
    qDebug("\t\t" + QString(ARG_PREFIX_SHORT).toLatin1() +
           QString(cmd).toLatin1() + "\t" + argTitle.toLatin1());
}

//////////////////////////////////////////////////////////////////////
void MainWindow::connectVia_serial()
{
    if(sw->isOpen()) {
        sw->close();
    }

    if (sw->open()) {
        config.connectionType = serial;
        log(note, "Connected via Serial");
    } else {
        config.connectionType = none;
        log(note, "Failed to connect via Serial");
    }
}
//////////////////////////////////////////////////////////////////////
void MainWindow::connectVia_network()
{
    if (nw->open()) {
        config.connectionType = network;
        log(note, "Connected via Network");
    } else {
        config.connectionType = none;
        log(note, "Failed to connect via Network");
    }
}
/////////////////////////////////////////////////////////////////
void MainWindow::uiInit()
{
    /*** set colors ***/

    /* MainWindow background */
    this->setStyleSheet(QString("color: %1; background-color: %2")
                        .arg(COLOR_WHITE).arg(COLOR_GRAY2));

    ui->lineEdit_save->setStyleSheet(QString("color: %1; background-color: %2")
                                     .arg(COLOR_WHITE).arg(COLOR_GRAY4));

    ui->statusBar->setStyleSheet(QString("color: %1; background-color: %2")
                                 .arg(COLOR_WHITE).arg(COLOR_GRAY1));

    ui->lineEdit_prefix->setStyleSheet(QString("color: %1; background-color: %2")
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_suffix->setStyleSheet(QString("color: %1; background-color: %2")
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->lineEdit_find_ascii->setStyleSheet(QString("color: %1; background-color: %2")
                                           .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_find_hex->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_find_dec->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->tab_ascii->setStyleSheet(QString("color: %1; background-color: %2")
                                 .arg(COLOR_WHITE).arg(COLOR_GRAY3));
    ui->tab_hex->setStyleSheet(QString("color: %1; background-color: %2")
                               .arg(COLOR_WHITE).arg(COLOR_GRAY3));
    ui->tab_dec->setStyleSheet(QString("color: %1; background-color: %2")
                               .arg(COLOR_WHITE).arg(COLOR_GRAY3));

    ui->textEdit_out_ascii->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->textEdit_out_hex->setStyleSheet(QString("color: %1; background-color: %2")
                                        .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->textEdit_out_dec->setStyleSheet(QString("color: %1; background-color: %2")
                                        .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->lineEdit_in_ascii->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_in_hex->setStyleSheet(QString("color: %1; background-color: %2")
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_in_dec->setStyleSheet(QString("color: %1; background-color: %2")
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->checkBox_clearIn_ascii->setStyleSheet(QString("color: %1; background-color: %2")
                                              .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->checkBox_clearIn_hex->setStyleSheet(QString("color: %1; background-color: %2")
                                            .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->checkBox_clearIn_dec->setStyleSheet(QString("color: %1; background-color: %2")
                                            .arg(COLOR_WHITE).arg(COLOR_BLACK));


    /*** UI setup ***/

    setWindowTitle(MAINWINDOWTITLE);

    /* setup the help table */
    ui->tableWidget_shortcuts->setColumnCount(2);
    QStringList titles;
    titles << "Shortcut" << "description";
    ui->tableWidget_shortcuts->setHorizontalHeaderLabels(titles);
    ui->tableWidget_shortcuts->horizontalHeader()->setStretchLastSection(true);  // set column size to widget size


    /*** UI show/hide widgets ***/

    ui->checkBox_clearIn_ascii->setChecked(true);
    ui->checkBox_clearIn_hex->setChecked(true);
    ui->checkBox_clearIn_dec->setChecked(true);

    ui->checkBox_prefix->setChecked(false);
    ui->checkBox_suffix->setChecked(true);
    ui->lineEdit_suffix->setText(QString(QByteArray(SUFFIX_DEFAULT).toHex().toUpper()));

    hideFindUi();
    hideHelp();
    hideSaveSettings();
    fillShortcutsTable();
    focus_1();
}
/////////////////////////////////////////////////////////////////
void MainWindow::showConnectionSettings()
{
    dialog_connect->show();
    dialog_connect->move(0,0);
}
/////////////////////////////////////////////////////////////////
void MainWindow::showSaveSettings()
{
    ui->lineEdit_save->show();
    ui->label_save->show();
    ui->pushButton_save->show();
    ui->groupBox_save->show();
    ui->lineEdit_save->setFocus();
    on_pushButton_save_clicked();
}
/////////////////////////////////////////////////////////////////
void MainWindow::hideSaveSettings()
{
    ui->lineEdit_save->hide();
    ui->label_save->hide();
    ui->pushButton_save->hide();
    ui->groupBox_save->hide();
    terminalInputSetFocus();
}
/////////////////////////////////////////////////////////////////
void MainWindow::terminalInputSetFocus()
{
    switch (ui->tabWidget->currentIndex())
    {
    case data_ascii:
        ui->lineEdit_in_ascii->setFocus();
        break;
    case data_hex:
        ui->lineEdit_in_hex->setFocus();
        break;
    case data_dec:
        ui->lineEdit_in_dec->setFocus();
        break;
    }
}
/////////////////////////////////////////////////////////////////
void MainWindow::clearOutput()
{
    ui->textEdit_out_ascii->clear();
    ui->textEdit_out_hex->clear();
    ui->textEdit_out_dec->clear();
}
/////////////////////////////////////////////////////////////////
void MainWindow::Tx(dataFormat_t inputType)
{
    QByteArray data;        // to be transmitted
    QString data_str;       // just a helper for data conversion

    /* read the data from UI */
    switch (inputType)
    {
    case data_ascii:
        data_str = ui->lineEdit_in_ascii->text();
        data = conv_strAscii_to_ba(data_str);
        if (ui->checkBox_clearIn_ascii->isChecked())
            ui->lineEdit_in_ascii->clear();
        break;
    case data_hex:
        data_str = ui->lineEdit_in_hex->text();
        data = conv_strHex_to_ba(data_str);
        if (ui->checkBox_clearIn_hex->isChecked())
            ui->lineEdit_in_hex->clear();
        break;
    case data_dec:
        QString data_str = ui->lineEdit_in_dec->text();
        QByteArray data_ba = conv_strDec_to_ba(data_str);
        if (ui->checkBox_clearIn_dec->isChecked())
            ui->lineEdit_in_dec->clear();
        break;
    }

    /* add prefix and suffix to the data */
    if (config.prefix_tx_enabled)
        data.prepend(config.prefix_tx);
    if (config.suffix_tx_enabled)
        data.append(config.suffix_tx);


    /* transmit the data */
    switch (config.connectionType)
    {
    case serial:
        sw->write(data);
        terminalOutUpdate(data_Tx, data);
        log(info, "Data sent via serial");
        break;
    case network:
        nw->send(data);
        terminalOutUpdate(data_Tx, data);
        log(note, "Data sent via network");
        break;
    case none:
        log(error, "Data can't be sent, no connection selected");
        break;
    }
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::
///     slot callet when Enter or Return key is pressed
///
void MainWindow::keyEnterPressed()
{
    ////////////////////////////
    if (ui->lineEdit_save->hasFocus()) {
            /* todo: start to save the new data into entered file */
//        QString fileLocation = ui->lineEdit_save->text();

//        QDateTime dt = QDateTime::currentDateTime();
//        QString timeStr = dt.toString( "yyyy-MM-dd_hh:mm:ss" );
//        //        ui->textEdit_out_ascii->append(timeStr); to debug
//        QString fileName = QString("TerminalOutput_%1").arg(timeStr);

//        file.setFileName(fileName);

//        qDebug() << "todo: 65464138";
//        fileDataFormat = data_ascii;

//        hideSaveSettings();
//        log(info, QString("Output saved to: %1%2").arg(fileLocation).arg(fileName));

    }

    ////////////////////////////
    else if (ui->lineEdit_in_ascii->hasFocus()) {
        Tx(data_ascii);
    }
    else if (ui->lineEdit_in_hex->hasFocus()) {
        Tx(data_hex);
    }
    else if (ui->lineEdit_in_dec->hasFocus()) {
        Tx(data_dec);
    }
}

/////////////////////////////////////////////////////////////////
QString MainWindow::conv_ba_to_strAscii(QByteArray data)
{
    QString out;
    out = QString(data);
    return out;
}

QString MainWindow::conv_ba_to_strHex(QByteArray data)
{
    QString out;
    for(int i = 0; i < data.size(); i++){
        QString numStr = QString::number(quint8(data.at(i)), 16);
        while(numStr.size() < 2){
            numStr.prepend("0");
        }
        out.append(QString(" %1").arg(numStr));
    }
    return out;
}

QString MainWindow::conv_ba_to_strDec(QByteArray data)
{
    QString out;
    for(int i = 0; i < data.size(); i++){
        QString numStr = QString::number(quint8(data.at(i)), 10);
        while(numStr.size() < 3){
            numStr.prepend("0");
        }
        out.append(QString(" %1").arg(numStr));
    }
    return out;
}

/////////////////////////////////////////////////////////////////
QByteArray MainWindow::conv_strAscii_to_ba(QString data_str)
{
    return data_str.toUtf8();
}
QByteArray MainWindow::conv_strHex_to_ba(QString sata_str)
{
    return QByteArray::fromHex(sata_str.toUtf8());
}
QByteArray MainWindow::conv_strDec_to_ba(QString data_str)
{
    bool ok;
    QString element;
    QByteArray data_ba;
    for (int i = 0; i <= data_str.size(); i += DIGIT_NUM_DEC) {
        element = data_str.mid(i, DIGIT_NUM_DEC);
        if (element.size() != 0) {
            while (element.size() < DIGIT_NUM_DEC) {
                element.append("0");
            }
            quint32 num = element.toUInt(&ok, 10);
            data_ba.append(qint8(num));
        }
    }
    return data_ba;
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::keyUpPressed
///     for browsing in history of transmitted data
///     todo: only the ascii input is supported by now
void MainWindow::keyUpPressed()
{
    /* handle Tx data history */
    if (history_out.size() > history_out_pointer)
    {
        if (ui->lineEdit_in_ascii->hasFocus()){
            ui->lineEdit_in_ascii->setText(
                        QString(history_out.at(history_out_pointer)));
        }
        else if (ui->lineEdit_in_hex->hasFocus()){
            /*  */
        }
        else if (ui->lineEdit_in_dec->hasFocus()){
            /*  */
        }
    }
    if (history_out.size() > history_out_pointer + 1)
        history_out_pointer++;

}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::keyDownPressed
///     for browsing in history of transmitted data
///     todo: only the ascii input is supported by now
void MainWindow::keyDownPressed()
{
    /* handle Tx data history */
    if (history_out.size() > history_out_pointer)
    {
        if (ui->lineEdit_in_ascii->hasFocus()){
            ui->lineEdit_in_ascii->setText(
                        QString(history_out.at(history_out_pointer)));
        }
        else if (ui->lineEdit_in_hex->hasFocus()){
            /* todo */
        }
        else if (ui->lineEdit_in_dec->hasFocus()){
            /* todo */
        }
    }
    if (history_out_pointer > 0)
        history_out_pointer--;

}
/////////////////////////////////////////////////////////////////
void MainWindow::showHelp()
{
    ui->tableWidget_shortcuts->show();
}
void MainWindow::hideHelp()
{
    ui->tableWidget_shortcuts->hide();
}
/////////////////////////////////////////////////////////////////
void MainWindow::fillShortcutsTable()
{
    QList <QList <QString>> shortcuts;

    shortcuts <<  QList <QString> { "CTRL + Q" , "Quit application"};
    shortcuts <<  QList <QString> { "Esc"      , "Hide evrything"};
    shortcuts <<  QList <QString> { "CTRL + L" , "Move cursor to the end of the terminal output"};
    shortcuts <<  QList <QString> { "CTRL + SHIFT + L" , "Clear terminal output"};
    shortcuts <<  QList <QString> { "CTRL + T" , "Change theme (not supported yet)"};
    shortcuts <<  QList <QString> { "CTRL + ," , "Open settongs"};
    shortcuts <<  QList <QString> { "CTRL + D" , "Connect / Disconnect"};
    shortcuts <<  QList <QString> { "CTRL + 1" , "Set focus to ASCII tab"};
    shortcuts <<  QList <QString> { "CTRL + 2" , "Set focus to Hex tab"};
    shortcuts <<  QList <QString> { "CTRL + 3" , "Set focus to DEC tab"};
    shortcuts <<  QList <QString> { "CTRL + W" , "Show terminal input wrap options"};
    shortcuts <<  QList <QString> { "CTRL + F" , "Find (not supported yet)"};
    shortcuts <<  QList <QString> { "CTRL + S" , "Save transmitted data"};
    shortcuts <<  QList <QString> { "F1"       , "Open help"};

    while (!shortcuts.isEmpty())
    {
        shortcutTable_addItem(shortcuts.at(0));
        shortcuts.pop_front();
    }
}
///////////////////////////////////////////////////////////////////////
/// \brief MainWindow::table_addItem
///     creates new row in the table and puts data into the row
/// \param element  is a List from whom are gained the data
void MainWindow::shortcutTable_addItem(QList<QString> element)
{
    /* add row to the table */
    ui->tableWidget_shortcuts->insertRow(ui->tableWidget_shortcuts->rowCount());
    /* get number of the new row */
    int newRow = ui->tableWidget_shortcuts->rowCount() - 1;
    /* for each element in the row */
    for (int i = 0; i < element.size(); i++) {
        /* create new item to the table */
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(element.at(i)));
        /* make the item non-editable */
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        /* add the item to specified column and row */
        ui->tableWidget_shortcuts->setItem(newRow, i, item);
    }
}

/////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////
/// \brief MainWindow::showFindUi
///     show UI for searching in the text terminal output of all tabs
void MainWindow::showFindUi()
{
    ui->pushButton_fnd_ascii->show();
    ui->pushButton_fnd_hex->show();
    ui->pushButton_fnd_dec->show();
    ui->lineEdit_find_dec->show();
    ui->lineEdit_find_hex->show();
    ui->lineEdit_find_ascii->show();
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::hideFindUi
///     hide UI for searching in the text terminal output of all tabs
void MainWindow::hideFindUi()
{
    ui->pushButton_fnd_ascii->hide();
    ui->pushButton_fnd_hex->hide();
    ui->pushButton_fnd_dec->hide();
    ui->lineEdit_find_dec->hide();
    ui->lineEdit_find_hex->hide();
    ui->lineEdit_find_ascii->hide();
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::focus_1
///     set focus to ASCII tab
void MainWindow::focus_1()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->lineEdit_in_ascii->setFocus();
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::focus_2
///     set focus to HEX tab
void MainWindow::focus_2()
{
    ui->tabWidget->setCurrentIndex(1);
    ui->lineEdit_in_hex->setFocus();
}

/////////////////////////////////////////////////////////////////
/// \brief MainWindow::focus_3
///     set focus to DEC tab
void MainWindow::focus_3()
{
    ui->tabWidget->setCurrentIndex(2);
    ui->lineEdit_in_dec->setFocus();
}

/////////////////////////////////////////////////////////////////
/// \brief MainWindow::dataArrived
///     process the list of received data
void MainWindow::dataArrived()
{
    tick_lastRx = tick.elapsed();

    /* get the data from apropriate class */
    switch (config.connectionType)
    {
    case serial:
        terminalOutUpdate(data_Rx, sw->Rx_buffer.data());
        sw->Rx_buffer.clear();
        break;
    case network:
        terminalOutUpdate(data_Rx, nw->Rx_buffer.data());
        nw->Rx_buffer.clear();
        break;
    case none:
        break;
    }
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::log
///         display event in the statusBar
/// \param logType  depending on this is set timeout
/// \param data     to be displayed
void MainWindow::log(logType_t logType, QString data)
{   
    int timeout;

    switch(logType)
    {
    case error:
        timeout = 300*1000;
        data.prepend("Error: ");
        break;

    case note:
        timeout = 50*1000;
        data.prepend("Note: ");
        break;

    case info:
        timeout = 60*1000;
    }

    ui->statusBar->showMessage(data, timeout);
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::
/// \param dataKind     to set the color
/// \param data         to be put to all text edits in corresponding format
///
void MainWindow::terminalOutUpdate(terminalData_t dataKind, QByteArray data)
{
    QString color;

    switch (dataKind)
    {
    case data_Rx:
        color = COLOR_DATA_RX;
        break;
    case data_Tx:
        color = COLOR_DATA_TX;
        TxHistory_add(data);
        break;
    }

    /* update all terminal outputs (textEdits) */

    /* ASCII */
    QString data_str_ascii = conv_ba_to_strAscii(data);
    updateTextEdit(ui->textEdit_out_ascii, color, data_str_ascii);

    /* HEX */
    QString data_str_hex = conv_ba_to_strHex(data);
    updateTextEdit(ui->textEdit_out_hex, color, data_str_hex);

    /* DEC */
    QString data_str_dec = conv_ba_to_strDec(data);
    updateTextEdit(ui->textEdit_out_dec, color, data_str_dec);

//    /* todo: put the data into txt file */
//    switch (fileDataFormat)
//    {
//    case data_ascii:
//        saveToFile(data_str_ascii);
//        break;
//    case data_hex:
//        saveToFile(data_str_hex);
//        break;
//    case data_dec:
//        saveToFile(data_str_dec);
//        break;
//    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::updateTextEdit(QTextEdit *textEdit, QString color, QString data)
{
    QTextCursor prev_cursor;
    prev_cursor = textEdit->textCursor();
    textEdit->moveCursor(QTextCursor::End);
    textEdit->setTextColor(color);
    textEdit->insertPlainText(data);
    textEdit->setTextCursor(prev_cursor);
}

/////////////////////////////////////////////////////////////////
void MainWindow::TxHistory_add(QByteArray data)
{
    if (history_out.isEmpty()) {
        history_out.prepend(data);
    }
    else if (history_out.at(0) != data) {
        history_out.prepend(data);
    }
    history_out_pointer = 0;
}
/////////////////////////////////////////////////////////////////
void MainWindow::saveToFile(QString data)
{
    //    QTextStream outStream(&file);
    //    if (file.open(QFile::WriteOnly | QFile::Text | QIODevice::Append)) {
    //        outStream <<  data;
    //        file.flush();
    //        file.close();
    //    } else {
    //       log(error, "Can't open the file.");
    //    }
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::EscPressed
///     slot emited when ESC key is pressed
///     It hides all config UIs
void MainWindow::EscPressed()
{
    hideFindUi();
    hideHelp();
    hideWrap();
    hideSaveSettings();
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::showWrap
///     Wrap ui is to add prefix and suffix to the data to be send via terminal
void MainWindow::showWrap()
{
    ui->groupBox_wrap->show();
}
void MainWindow::hideWrap()
{
    ui->groupBox_wrap->hide();
}

/////////////////////////////////////////////////////////////////
/// \brief MainWindow::moveCursorToEnd
// slot generated by hotkey moves cursor to end of text edit in all tabs
void MainWindow::moveCursorToEnd()
{
    ui->textEdit_out_ascii->moveCursor(QTextCursor::End);
    ui->textEdit_out_hex->moveCursor(QTextCursor::End);
    ui->textEdit_out_dec->moveCursor(QTextCursor::End);
}
/////////////////////////////////////////////////////////////////
void MainWindow::on_pushButton_save_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        "~/Desktop/",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);

    ui->lineEdit_save->setText(dir);
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::on_tabWidget_currentChanged
/// \param index of data type
///     switch focus to corresponding lineedit data input
///     according to selected tabwidget data type
void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index)
    {
    case data_ascii:
        ui->lineEdit_in_ascii->setFocus();
        break;
    case data_hex:
        ui->lineEdit_in_hex->setFocus();
        break;
    case data_dec:
        ui->lineEdit_in_dec->setFocus();
        break;
    default:
        ui->lineEdit_in_ascii->setFocus();
    }
}
/////////////////////////////////////////////////////////////////
void MainWindow::on_checkBox_prefix_stateChanged(int arg1)
{
    switch (arg1) {
    case Qt::Checked:
        config.prefix_tx_enabled = true;
        break;
    case Qt::Unchecked:
        config.prefix_tx_enabled = false;
        break;
    }
}
void MainWindow::on_checkBox_suffix_stateChanged(int arg1)
{
    switch (arg1) {
    case Qt::Checked:
        config.suffix_tx_enabled = true;
        break;
    case Qt::Unchecked:
        config.suffix_tx_enabled = false;
        break;
    }
}
/////////////////////////////////////////////////////////////////
void MainWindow::on_lineEdit_suffix_textChanged(const QString &arg1)
{
    config.suffix_tx = QByteArray::fromHex(arg1.toUtf8());
}

void MainWindow::on_lineEdit_prefix_textChanged(const QString &arg1)
{
    config.prefix_tx = QByteArray::fromHex(arg1.toUtf8());
}
/////////////////////////////////////////////////////////////////
