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
#include "dataconverter.h"


/////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QStringList arguments, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sw = new SerialWorker(this);
    connect(sw, SIGNAL(dataReceived()), this, SLOT(dataArrived()));

    nw = new NetworkWorker(this);
    connect(nw, SIGNAL(dataReceived()), this, SLOT(dataArrived()));

    dialog_connect = new Dialog_connect(this);
    dialog_connect->setSw(sw);
    dialog_connect->setNw(nw);
    dialog_connect->init();
    connect(dialog_connect, SIGNAL(tryConnect(connectionType_t)), this,
            SLOT(tryConnectDevice(connectionType_t)));

    logFile = new LogFile(this);

    tick_lastRx = 0;
    tick.start();

    setupShortcuts();
    uiInit();
    configInit();
    handleAppArguments(arguments);
}
//////////////////////////////////////////////////////////////////////
void MainWindow::saveToFile_init()
{
    ui->checkBox_outputSave->setCheckState(Qt::Checked);
    QString fileLocation = ui->lineEdit_save->text();

    logFile->init(fileLocation);
    QString message = QString("Output saved in %1").arg(fileLocation);
    log(info, message);
    qDebug() << message;
}

//////////////////////////////////////////////////////////////////////
void MainWindow::configInit()
{
    config.connectionType = none;
    config.timeInfoEnabled = false;
    config.timeLogEnabled = true;
    config.clearOutputLine = true;
    config.saveTerminalOutToFile = false;
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

                if (!handleAppArguments_setParam(command, passedData)) {
                    return;
                }
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

    if (config.connectionType != none) {
        tryConnectDevice(config.connectionType);
    }
}

bool MainWindow::handleAppArguments_setParam(QString command, QString passedData)
{
    char cmdChar = command.toUtf8().at(1);
    bool ok = true;

    switch (cmdChar)
    {
    case ARG_NETWORK_IPADDR:
        nw->param.targetIpAddr = QHostAddress(passedData);
        if (nw->param.targetIpAddr.isNull())
            ok = false;
        break;
    case ARG_NETWORK_TXPORT:
        nw->param.port_Tx = quint16(passedData.toInt(&ok, 10));
        break;
    case ARG_NETWORK_RXPORT:
        nw->param.port_Rx = quint16(passedData.toInt(&ok, 10));
        break;

    case ARG_SERIAL_PORTNAME:
        sw->param.portName = passedData;
        break;
    case ARG_SERIAL_BAUDRATE:
        sw->param.baudRate = passedData.toInt(&ok, 10);
        break;
    case ARG_SERIAL_DATABITS:
        sw->param.dataBits = passedData.toInt(&ok, 10);
        break;
    case ARG_SERIAL_PARITY:
        sw->param.parity= passedData.toInt(&ok, 10);
        break;
    case ARG_SERIAL_STOPBITS:
        sw->param.stopBits= passedData.toInt(&ok, 10);
        break;
    case ARG_SERIAL_FLOWCONTROL:
        sw->param.flowControl = passedData.toInt(&ok, 10);
        break;

    case ARG_CONNECTIONTYPE:
        if (passedData == "serial") {
            config.connectionType = serial;
        }
        else if (passedData == "network") {
            config.connectionType = network;
        }
        else {
            ok = false;
        }
        break;
    default:
        qDebug() << "ERROR: Unknown command -" << command;
    }

    if (!ok) {
        qDebug() << "Failed to handle arguments: " << command << " " << passedData;
    } else {
        qDebug() << "Setting" << command << " to " << passedData;
    }

    return ok;
}

void MainWindow::handleAppArguments_printHelp()
{
    qDebug("");
    qDebug() << "*** The options are as follows:";

    qDebug() << "\n\t- Select connection type to connect automatically: ";
    handleAppArguments_printHelp_wrap(ARG_SERIAL_PORTNAME,      "serial or network");


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
void MainWindow::tryConnectDevice(connectionType_t connectionType)
{
    bool connectedSuccessfully;
    QString deviceName;

    switch (connectionType)
    {
    case serial:
        connectedSuccessfully = sw->open();
        deviceName = sw->param.portName;
        break;
    case network:
        connectedSuccessfully = nw->open();
        deviceName = nw->param.targetIpAddr.toString();
        break;
    case none:
        connectedSuccessfully = false;
        break;
    }

    if (connectedSuccessfully) {
        config.connectionType = connectionType;
        log(note, QString("Connected to: %1").arg(deviceName));
        ui->lineEdit_in_ascii->setFocus();
    } else {
        config.connectionType = none;
        log(error, QString("Failed to connect to: %1").arg(deviceName));
        dialog_connect->show();
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
    ui->lineEdit_save->setStyleSheet(QString("color: %1; background-color: %2")
                                     .arg(COLOR_WHITE).arg(COLOR_BLACK));

    /* pushbuttons */
    ui->pushButton_save->setStyleSheet(QString("color: %1; background-color: %2")
                                       .arg(COLOR_WHITE).arg(COLOR_GRAY0));
    ui->pushButton_fnd_dec->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_GRAY0));
    ui->pushButton_fnd_hex->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_GRAY0));
    ui->pushButton_fnd_ascii->setStyleSheet(QString("color: %1; background-color: %2")
                                            .arg(COLOR_WHITE).arg(COLOR_GRAY0));

    /*** UI setup ***/

    setWindowTitle(MAINWINDOWTITLE);

    /* setup the help table */
    ui->tableWidget_shortcuts->setColumnCount(2);
    QStringList titles;
    titles << "Shortcut" << "Description";
    ui->tableWidget_shortcuts->setHorizontalHeaderLabels(titles);
    ui->tableWidget_shortcuts->horizontalHeader()->setStretchLastSection(true);  // set column size to widget size


    /*** UI show/hide widgets ***/

    ui->checkBox_timeLog->setChecked(true);
    ui->checkBox_prefix->setChecked(false);
    ui->checkBox_suffix->setChecked(true);
    ui->checkBox_clearOutputLine->setChecked(true);
    ui->lineEdit_suffix->setText(QString(QByteArray(SUFFIX_DEFAULT).toHex().toUpper()));

    hideFindUi();
    hideHelp();
    fillShortcutsTable();
    toggleShowSettings();
    focus_1();
}
/////////////////////////////////////////////////////////////////
void MainWindow::showConnectionSettings()
{
    dialog_connect->show();
    //    dialog_connect->move(0,0);
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
    QByteArray txData;        // to be transmitted
    dataConverter dataConv;

    /* read the data from UI */
    switch (inputType)
    {
    case data_ascii:
        dataConv.setStrAscii(ui->lineEdit_in_ascii->text());
        break;
    case data_hex:
        dataConv.setStrHex(ui->lineEdit_in_hex->text());
        break;
    case data_dec:
        dataConv.setStrDec(ui->lineEdit_in_dec->text());
        break;
    }

    txData = dataConv.getByteArray();

    /* add prefix and suffix to the data */
    if (config.prefix_tx_enabled)
        txData.prepend(config.prefix_tx);
    if (config.suffix_tx_enabled)
        txData.append(config.suffix_tx);

    /* transmit the data */
    switch (config.connectionType)
    {
    case serial:
        sw->write(txData);
        terminalOutUpdate(data_Tx, txData);
        TxHistory_add(txData);
        break;
    case network:
        nw->send(txData);
        terminalOutUpdate(data_Tx, txData);
        TxHistory_add(txData);
        break;
    case none:
        log(error, "No connection established.");
        return;
    }

    if (config.clearOutputLine) {
        ui->lineEdit_in_ascii->clear();
        ui->lineEdit_in_hex->clear();
        ui->lineEdit_in_dec->clear();
    }
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::
///     slot callet when Enter or Return key is pressed
///
void MainWindow::keyEnterPressed()
{
    ////////////////////////////
    if (ui->lineEdit_in_ascii->hasFocus()) {
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
void MainWindow::keyUpPressed()
{
    historyTxUpdate();

    if (history_out.size() > history_out_ptr + 1) {
        history_out_ptr++;
    }

}
/////////////////////////////////////////////////////////////////
void MainWindow::keyDownPressed()
{
    historyTxUpdate();

    if (history_out_ptr > 0) {
        history_out_ptr--;
    }
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::historyTxUpdate
///     update all lineedits of Tx data
///     based on current state of history_out_ptr
void MainWindow::historyTxUpdate()
{
    if (history_out.size() > history_out_ptr)
    {
        dataConverter dataConv;
        dataConv.setByteArray(history_out.at(history_out_ptr));

        ui->lineEdit_in_ascii->setText(dataConv.getStrAscii());
        ui->lineEdit_in_hex->setText(dataConv.getStrHex());
        ui->lineEdit_in_dec->setText(dataConv.getStrDec());
    }
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
    shortcuts <<  QList <QString> { "CTRL + ," , "Show settongs"};
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
    /* get the data from apropriate class */
    switch (config.connectionType)
    {
    case serial:
        terminalOutUpdate(data_Rx, sw->ReadAllRx());
        break;
    case network:
        terminalOutUpdate(data_Rx, nw->ReadAllRx());
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
        timeout = LOGTIMEOUT_ERROR;
        data.prepend("Error: ");
        break;

    case note:
        timeout = LOGTIMEOUT_NOTE;
        data.prepend("Note: ");
        break;

    case info:
        timeout = LOGTIMEOUT_INFO;
    }

    ui->statusBar->showMessage(data, timeout);
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::
/// \param dataKind depends how the data will be logged
/// \param data to be logged
///
void MainWindow::terminalOutUpdate(terminalData_t dataKind, QByteArray data)
{
    if (config.timeLogEnabled &&
            (((tick_lastRx + RXDATAEVENT_TIMEOUT) < tick.elapsed()) ||
             (config.lastTerminalData != dataKind)))
    {
        config.lastTerminalData = dataKind;

        /* get the time */
        QDateTime dt = QDateTime::currentDateTime();
        QString preamble;
        preamble.append("\n");
        preamble.append(dt.toString(TIME_FORMAT));
        switch (dataKind) {
        case data_Rx:
            preamble.append(" [Rx] - ");
            break;
        case data_Tx:
            preamble.append(" [Tx] - ");
            break;
        }

        /* put the preamble into text edits */
        writeToTextedit(ui->textEdit_out_ascii, COLOR_DATA, preamble);
        writeToTextedit(ui->textEdit_out_hex, COLOR_DATA, preamble);
        writeToTextedit(ui->textEdit_out_dec, COLOR_DATA, preamble);

        /* put the preamble into text file */
        if (config.saveTerminalOutToFile) {
            logFile->writeData_ascii(preamble);
            logFile->writeData_hex(preamble);
        }

    }

    /* refresh */
    tick_lastRx = tick.elapsed();

    dataConverter dataConv;
    dataConv.setByteArray(data);

    /* update terminal output logs - textEdits */
    QString color;
    switch (dataKind)
    {
    case data_Rx:
        color = COLOR_DATA_RX;
        break;
    case data_Tx:
        color = COLOR_DATA_TX;
        break;
    }

    writeToTextedit(ui->textEdit_out_ascii,  color, dataConv.getStrAscii());
    writeToTextedit(ui->textEdit_out_hex,    color, dataConv.getStrHex());
    writeToTextedit(ui->textEdit_out_dec,    color, dataConv.getStrDec());

    /* update terminal output logs - files */
    if (config.saveTerminalOutToFile) {
        logFile->writeData_ascii(dataConv.getStrAscii());
        logFile->writeData_hex(dataConv.getStrHex());
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::writeToTextedit(QTextEdit *textEdit, QString color, QString data)
{
    /* get to end of textedit */
    QTextCursor prev_cursor;
    prev_cursor = textEdit->textCursor();
    textEdit->moveCursor(QTextCursor::End);
    textEdit->setTextColor(color);

    /* write data to textedit */
    textEdit->setTextColor(color);
    textEdit->insertPlainText(data);

    /* return cursor where it was */
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
    history_out_ptr = 0;
}

/////////////////////////////////////////////////////////////////
/// \brief MainWindow::EscPressed
///     slot emited when ESC key is pressed
///     It hides all config UIs
void MainWindow::EscPressed()
{
    hideFindUi();
    hideHelp();
    toggleShowSettings();
    moveCursorToTerminalInputLine();
}
/////////////////////////////////////////////////////////////////
void MainWindow::moveCursorToTerminalInputLine()
{
//#error todo
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::showSettings
///     toggle show / hide
void MainWindow::toggleShowSettings()
{
    if (ui->groupBox_settings->isHidden()) {
        ui->groupBox_settings->show();
    } else {
        ui->groupBox_settings->hide();
    }
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
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        ui->lineEdit_save->setText(dir);
        saveToFile_init();
    }
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
void MainWindow::on_checkBox_timeLog_stateChanged(int arg1)
{
    switch (arg1) {
    case Qt::Checked:
        config.timeLogEnabled = true;
        break;
    case Qt::Unchecked:
        config.timeLogEnabled = false;
        break;
    }
}
void MainWindow::on_checkBox_clearOutputLine_stateChanged(int arg1)
{
    switch (arg1) {
    case Qt::Checked:
        config.clearOutputLine = true;
        break;
    case Qt::Unchecked:
        config.clearOutputLine = false;
        break;
    }
}
/////////////////////////////////////////////////////////////////
void MainWindow::on_checkBox_outputSave_stateChanged(int arg1)
{
    switch (arg1) {
    case Qt::Checked:
        config.saveTerminalOutToFile = true;
        break;
    case Qt::Unchecked:
        config.saveTerminalOutToFile = false;
        break;
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_lineEdit_suffix_textChanged(const QString &arg1)
{
    dataConverter dataConv;
    dataConv.setStrHex(arg1);
    config.suffix_tx = dataConv.getByteArray();
}
void MainWindow::on_lineEdit_prefix_textChanged(const QString &arg1)
{
    dataConverter dataConv;
    dataConv.setStrHex(arg1);
    config.prefix_tx = dataConv.getByteArray();
}

/////////////////////////////////////////////////////////////////
void MainWindow::setupShortcuts()
{
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this, SLOT(showFindUi()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(EscPressed()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), this, SLOT(moveCursorToEnd()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_L), this, SLOT(clearOutput()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Comma), this, SLOT(toggleShowSettings()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this, SLOT(showConnectionSettings()));
    //    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), this, SLOT(on_pushButton_connect_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_3), this, SLOT(focus_3()));
    new QShortcut(QKeySequence(Qt::Key_F1), this, SLOT(showHelp()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_pushButton_save_clicked()));
    new QShortcut(QKeySequence(Qt::Key_Enter), this, SLOT(keyEnterPressed()));
    new QShortcut(QKeySequence(Qt::Key_Return), this, SLOT(keyEnterPressed()));
    new QShortcut(QKeySequence(Qt::Key_Up), this, SLOT(keyUpPressed()));
    new QShortcut(QKeySequence(Qt::Key_Down), this, SLOT(keyDownPressed()));
}
/////////////////////////////////////////////////////////////////
