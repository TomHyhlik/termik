#include <QShortcut>
//#include <QSerialPortInfo>        // todo rm
#include <QTimer>
#include <QFileDialog>

#include <QTextStream>
#include <QFile>
#include <QDataStream>

#include <QDateTime>
#include <QDateTimeEdit>
#include <QDebug>

#include <stdio.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include "dialog_connect.h"
#include "dataconverter.h"
#include "saveconfiguration.h"
#include "cliarghandler.h"

#include "communication.h"
#include "serialwparam.h"


/////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QStringList arguments, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    communic = new Communication(this);
    connect(communic, SIGNAL(displayData(int, QByteArray)),
            this, SLOT(terminalOutUpdate(int, QByteArray)));
    connect(communic, SIGNAL(connectionEstablished(bool, QString)),
            this, SLOT(on_connectionEstablished(bool, QString)));


    logFile = new LogFile(this);
    script = new RunScript(this);
    connect(script, SIGNAL(Tx(QByteArray)), this, SLOT(on_Tx(QByteArray)));

    tick_lastRx = 0;
    tick.start();

    setupShortcuts();
    uiInit();
    configInit();

    /* set configuration from the json file */
    currentAppConfig_load();

    /* set configuration from the CLI arguments */
    CliArgHandler cliArgHandler(arguments);
    if (cliArgHandler.getComType() != comType_none) {
        communic->establish(cliArgHandler.getComType());
    }
}
//////////////////////////////////////////////////////////////////////
void MainWindow::on_connectionEstablished(bool success, QString deviceName)
{
    if (success) {
        showMessage(note, QString("Connected to: %1").arg(deviceName));
        terminalInputSetFocus();
    } else {
        showMessage(error, QString("Failed to connect to: %1").arg(deviceName));
        showConnectionSettings();
    }
}

//////////////////////////////////////////////////////////////////////
void MainWindow::connectOrDisconnect()
{
    communic->establishToggle();
}
//////////////////////////////////////////////////////////////////////
/// \brief MainWindow::closeEvent
/// \param event
///     function called when the MainWindow is being closed
void MainWindow::closeEvent(QCloseEvent *event)
{
    currentAppConfig_save();

    qDebug() << "\n" << "Closing" << MAINWINDOWTITLE << "\n";
    //    event->accept(); // todo:error
}
//////////////////////////////////////////////////////////////////////
/// \brief MainWindow::currentAppConfig_save
///     write app configuration to json file at app shutdown
void MainWindow::currentAppConfig_save()
{
    SaveConfiguration saveCfg;

    saveCfg.data.app = config;
    saveCfg.data.LogFileDir = logFile->getFileDirectory();

    saveCfg.write();
}

//////////////////////////////////////////////////////////////////////
/// \brief MainWindow::currentAppConfig_load
///     load app configuration from json file at app startup
void MainWindow::currentAppConfig_load()
{
    SaveConfiguration saveCfg;
    if (saveCfg.read()) {

        /* load script parameters */
        if (!saveCfg.data.script.fileName.isEmpty()) {
            ui->lineEdit_script->setText(saveCfg.data.script.fileName);
        }
        if (!saveCfg.data.LogFileDir.isEmpty()) {
            ui->lineEdit_save->setText(saveCfg.data.LogFileDir);
        }

        /* RunScript settings */
        ui->comboBox_script_dataType->setCurrentIndex(saveCfg.data.script.dFormat);
        ui->lineEdit_script->setText(saveCfg.data.script.fileName);
//        qDebug() << "Configuration loaded from file: " << RunScriptParam::get().fileName;

        ui->checkBox_script_repeat->setChecked(saveCfg.data.script.repeat);
        ui->spinBox_script_period->setValue(saveCfg.data.script.timeout);

        /* todo: continue here, load the saveCfg.data.app to ui */

        qDebug() << "Configuration loaded from file";
    }
}

//////////////////////////////////////////////////////////////////////
void MainWindow::selectScript()
{
    QString openLocation;

    if (!RunScriptParam::get().fileName.isEmpty()) {
        openLocation = RunScriptParam::get().fileName;
    } else {
        openLocation = LOCATION_DEFAULT;
    }

    QString scriptFileName = QFileDialog::getOpenFileName(this,
                                     RunScriptParam::get().fileName);

    if (!scriptFileName.isEmpty()) {
        showScriptUi();
        ui->lineEdit_script->setText(scriptFileName);
        ui->pushButton_script_run->setFocus();
    }

}
//////////////////////////////////////////////////////////////////////
void MainWindow::saveToFile_init()
{
    ui->checkBox_outputSave->setCheckState(Qt::Checked);
    QString fileLocation = ui->lineEdit_save->text();

    logFile->init(fileLocation);
    QString message = QString("Output saved in %1").arg(fileLocation);
    showMessage(info, message);
    qDebug() << message;
}

//////////////////////////////////////////////////////////////////////
void MainWindow::configInit()
{
    config.timeInfoEnabled = false;
    config.timeLogEnabled = true;
    config.clearOutputLine = true;
    config.saveTerminalOutToFile = false;
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

    ui->lineEdit_script->setStyleSheet(QString("color: %1; background-color: %2")
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_script_dataType->setStyleSheet(QString("color: %1; background-color: %2")
                                                .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->spinBox_autoclear_maxCharCnt->setStyleSheet(QString("color: %1; background-color: %2")
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
    pushButton_runScript_setColor_green();

    /*** UI setup ***/

    setWindowTitle(MAINWINDOWTITLE);

    /* setup the help table */
    ui->tableWidget_shortcuts->setColumnCount(2);
    QStringList titles;
    titles << "Shortcut" << "Description";
    ui->tableWidget_shortcuts->setHorizontalHeaderLabels(titles);
    ui->tableWidget_shortcuts->horizontalHeader()->setStretchLastSection(true);  // set column size to widget size

    ui->comboBox_script_dataType->addItem(TITLE_DATA_ASCII);
    ui->comboBox_script_dataType->addItem(TITLE_DATA_HEX);
    ui->spinBox_script_period->setValue(SCRIPTTIMEOUT_DEFAULT);

    /*** UI show/hide widgets ***/

    ui->checkBox_timeLog->setChecked(true);
    ui->checkBox_prefix->setChecked(false);
    ui->checkBox_suffix->setChecked(true);
    ui->checkBox_clearOutputLine->setChecked(true);
    ui->checkBox_script_repeat->setChecked(true);
    ui->lineEdit_suffix->setText(QString(QByteArray(SUFFIX_DEFAULT).toHex().toUpper()));
    ui->spinBox_autoclear_maxCharCnt->setValue(AUTOCLEAR_VAL_DEFAULT);
    ui->spinBox_script_period->setValue(SCRIPT_TXPERIOD_DEFAULT);

    ui->checkBox_autoclear->setChecked(true);
    ui->checkBox_autoclear->setChecked(false);
    ui->spinBox_script_period->setValue(10);

    hideFindUi();
    hideHelp();
    hideScriptUi();
    fillShortcutsTable();
    toggleShowSettings();
    focus_1();
}

/////////////////////////////////////////////////////////////////
void MainWindow::pushButton_runScript_setColor_green()
{
    ui->pushButton_script_run->setStyleSheet(QString("color: %1; background-color: %2")
                                             .arg(COLOR_WHITE).arg(COLOR_GREEN));
}

/////////////////////////////////////////////////////////////////
void MainWindow::pushButton_runScript_setColor_red()
{
    ui->pushButton_script_run->setStyleSheet(QString("color: %1; background-color: %2")
                                             .arg(COLOR_WHITE).arg(COLOR_RED));
}

/////////////////////////////////////////////////////////////////
void MainWindow::showConnectionSettings()
{
    Dialog_connect* dialog_connect = new Dialog_connect(this);
    connect(dialog_connect, SIGNAL(tryConnect(communicationType)), communic,
            SLOT(establish(communicationType)));

    dialog_connect->show();
    /* the dialog_connect deletes itself, when closed */

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
void MainWindow::Tx_fromDataInput(int inputType)
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
    on_Tx(txData);
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_Tx(QByteArray txData)
{
    if (!communic->isEstablished()) {
        showMessage(error, "Can't transmit. No connection established.");
        return;
    }

    TxHistory_add(txData);

    /* add prefix and suffix to the data */
    if (config.prefix_tx_enabled)
        txData.prepend(config.prefix_tx);
    if (config.suffix_tx_enabled)
        txData.append(config.suffix_tx);

    communic->dataTransmit(txData);

    if (config.clearOutputLine) {
        ui->lineEdit_in_ascii->clear();
        ui->lineEdit_in_hex->clear();
        ui->lineEdit_in_dec->clear();
    }
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::
///     slot callet when Enter or Return key is pressed
void MainWindow::keyEnterPressed()
{
    if (ui->lineEdit_in_ascii->hasFocus()) {
        Tx_fromDataInput(data_ascii);
    }
    else if (ui->lineEdit_in_hex->hasFocus()) {
        Tx_fromDataInput(data_hex);
    }
    else if (ui->lineEdit_in_dec->hasFocus()) {
        Tx_fromDataInput(data_dec);
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::keyUpPressed()
{
    if (!history_out.isEmpty()) {
        historyTxUpdate();

        if (history_out.size() > history_out_ptr + 1) {
            history_out_ptr++;
        }
    }
}
/////////////////////////////////////////////////////////////////
void MainWindow::keyDownPressed()
{
    if (!history_out.isEmpty()) {
        historyTxUpdate();

        if (history_out_ptr > 0) {
            history_out_ptr--;
        }
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
void MainWindow::showScriptUi()
{
    ui->label_script->show();
    ui->lineEdit_script->show();
    ui->comboBox_script_dataType->show();
    ui->checkBox_script_repeat->show();
    ui->pushButton_script_run->show();
    ui->spinBox_script_period->show();
}
void MainWindow::hideScriptUi()
{
    ui->label_script->hide();
    ui->lineEdit_script->hide();
    ui->comboBox_script_dataType->hide();
    ui->checkBox_script_repeat->hide();
    ui->pushButton_script_run->hide();
    ui->spinBox_script_period->hide();
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
void MainWindow::showMessage(int type, QString messageData)
{   
    int timeout;

    switch (type)
    {
    case error:
        timeout = LOGTIMEOUT_ERROR;
        messageData.prepend("Error: ");
        break;

    case note:
        timeout = LOGTIMEOUT_NOTE;
        messageData.prepend("Note: ");
        break;

    case info:
        timeout = LOGTIMEOUT_INFO;
        break;
    default:
        timeout = LOGTIMEOUT_ERROR;
    }

    ui->statusBar->showMessage(messageData, timeout);
}

/////////////////////////////////////////////////////////////////
bool MainWindow::preambleShouldBeAddrd(int dataKind)
{
    if (config.timeLogEnabled &&
            (((tick_lastRx + RXDATAEVENT_TIMEOUT) < tick.elapsed()) ||
             (lastTerminalData != dataKind))) {
        return true;
    }    else {
        return false;
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::preambleAdd(int dataKind)
{
    lastTerminalData = dataKind;

    QString preamble = terminalOutGetPreamble(dataKind);

    /* put the preamble into text edits */
    writeToTextedit(ui->textEdit_out_ascii, COLOR_PREAMBLE, preamble);
    writeToTextedit(ui->textEdit_out_hex, COLOR_PREAMBLE, preamble);
    writeToTextedit(ui->textEdit_out_dec, COLOR_PREAMBLE, preamble);

    /* put the preamble into text file */
    if (config.saveTerminalOutToFile) {
        logFile->writeData_ascii(preamble);
        logFile->writeData_hex(preamble);
    }
}
/////////////////////////////////////////////////////////////////
QString MainWindow::terminalOutGetPreamble(int dataKind)
{
    QDateTime dt = QDateTime::currentDateTime();
    QString time = dt.toString(TIME_FORMAT);

    QString preamble;
    preamble.append("\n");
    preamble.append(time);

    switch (dataKind)
    {
    case data_Rx:
        preamble.append(" [Rx] - ");
        break;
    case data_Tx:
        preamble.append(" [Tx] - ");
        break;
    default:
        preamble.append("  ");
    }
    return preamble;
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::terminalOutUpdate
/// \param dataKind
/// \param data
/// update the terminal output event
void MainWindow::terminalOutUpdate(int dataKind, QByteArray data)
{
    if (preambleShouldBeAddrd(dataKind)) {
        preambleAdd(dataKind);
    }

    tick_lastRx = tick.elapsed();

    /* update terminal output logs - textEdits */
    QString dataColor = getDataColor(dataKind);

    dataConverter dataConv;
    dataConv.setByteArray(data);

    /* update terminal output text edits */
    writeToTextedit(ui->textEdit_out_ascii,  dataColor, dataConv.getStrAscii());
    writeToTextedit(ui->textEdit_out_hex,    dataColor, dataConv.getStrHex());
    writeToTextedit(ui->textEdit_out_dec,    dataColor, dataConv.getStrDec());

    /* update terminal output log files */
    if (config.saveTerminalOutToFile) {
        logFile->writeData_ascii(dataConv.getStrAscii());
        logFile->writeData_hex(dataConv.getStrHex());
    }

    /* clear part of the text in the text edits */
    if (config.autoclerTermOut) {
        shortenTextEdit(ui->textEdit_out_ascii);
        shortenTextEdit(ui->textEdit_out_hex);
        shortenTextEdit(ui->textEdit_out_dec);
    }
}

/////////////////////////////////////////////////////////////////
QString MainWindow::getDataColor(int dataKind)
{
    switch (dataKind)
    {
    case data_Rx:
        return COLOR_DATA_RX;
        break;
    case data_Tx:
        return COLOR_DATA_TX;
        break;
    default:
        qDebug() << "ERROR: 29083475";
        return COLOR_DATA_TX;
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::shortenTextEdit(QTextEdit* textEdit)
{
    if (textEdit->document()->blockCount() > config.autoclerTermOut_maxChars) {

        textEdit->clear();
        /* todo autoclear should do better then this */
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

    //    textEdit->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
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
    hideScriptUi();
}
/////////////////////////////////////////////////////////////////
void MainWindow::moveCursorToTerminalInputLine()
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
    }
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
    QString openLocation;

    if (!logFile->getFileDirectory().isEmpty()) {
        openLocation = logFile->getFileDirectory();
    } else {
        openLocation = LOCATION_DEFAULT;
    }

    QString dir = QFileDialog::getExistingDirectory(
                this, tr("Open Directory"),
                openLocation,
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
void MainWindow::on_spinBox_autoclear_maxCharCnt_valueChanged(int arg1)
{
    config.autoclerTermOut_maxChars = arg1;
}
/////////////////////////////////////////////////////////////////
void MainWindow::on_checkBox_prefix_stateChanged(int arg1)
{
    config.prefix_tx_enabled = checkboxChecked(arg1);
}
void MainWindow::on_checkBox_suffix_stateChanged(int arg1)
{
    config.suffix_tx_enabled = checkboxChecked(arg1);
}
void MainWindow::on_checkBox_timeLog_stateChanged(int arg1)
{
    config.timeLogEnabled = checkboxChecked(arg1);
}
void MainWindow::on_checkBox_clearOutputLine_stateChanged(int arg1)
{
    config.clearOutputLine = checkboxChecked(arg1);
}
void MainWindow::on_checkBox_outputSave_stateChanged(int arg1)
{
    config.saveTerminalOutToFile = checkboxChecked(arg1);
}
void MainWindow::on_checkBox_script_repeat_stateChanged(int arg1)
{
    RunScriptParam::get().repeat = checkboxChecked(arg1);
}
void MainWindow::on_checkBox_autoclear_stateChanged(int arg1)
{
    config.autoclerTermOut = checkboxChecked(arg1);
}
/////////////////////////////////////////////////////////////////
bool MainWindow::checkboxChecked(int state)
{
    switch (state)
    {
    case Qt::Checked:
    case Qt::PartiallyChecked:
        return  true;

    case Qt::Unchecked:
    default:
        return false;
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

void MainWindow::on_spinBox_script_period_valueChanged(int arg1)
{
    RunScriptParam::get().timeout = arg1;
}

void MainWindow::on_pushButton_script_run_clicked()
{
    if (script->isRunning()) {
        RunScriptParam::get().fileName = ui->lineEdit_script->text();
        script->stop();
        ui->pushButton_script_run->setText(TITLE_BUTTON_SCRIPT_RUN);
        pushButton_runScript_setColor_green();
    } else {
        ui->pushButton_script_run->setText(TITLE_BUTTON_SCRIPT_STOP);
        pushButton_runScript_setColor_red();
        script->start();
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_comboBox_script_dataType_editTextChanged(const QString &arg1)
{
    if (arg1 == TITLE_DATA_HEX) {
        RunScriptParam::get().dFormat = data_hex;
    }
    else if (arg1 == TITLE_DATA_ASCII) {
        RunScriptParam::get().dFormat = data_ascii;
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_lineEdit_save_textChanged(const QString &arg1)
{
    logFile->setFileDirectory(arg1);
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_comboBox_script_dataType_currentTextChanged(const QString &arg1)
{
    if (arg1 == TITLE_DATA_ASCII) {
        RunScriptParam::get().dFormat = data_ascii;
    }
    else if (arg1 == TITLE_DATA_HEX) {
        RunScriptParam::get().dFormat = data_hex;
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::fillShortcutsTable()
{
    QList <QList <QString>> shortcuts;

    shortcuts <<  QList <QString> { "CTRL + Q" , "Quit this app"};
    shortcuts <<  QList <QString> { "CTRL + L" , "Move cursor to the end of the terminal output"};
    shortcuts <<  QList <QString> { "CTRL + SHIFT + L" , "Clear terminal output"};
    shortcuts <<  QList <QString> { "CTRL + ," , "Show main settongs"};
    shortcuts <<  QList <QString> { "CTRL + P" , "Show connection settongs"};
    shortcuts <<  QList <QString> { "CTRL + O" , "Open script"};
    shortcuts <<  QList <QString> { "CTRL + D" , "Connect / Disconnect"};
    shortcuts <<  QList <QString> { "CTRL + 1" , "Set focus to ASCII tab"};
    shortcuts <<  QList <QString> { "CTRL + 2" , "Set focus to Hex tab"};
    shortcuts <<  QList <QString> { "CTRL + 3" , "Set focus to DEC tab"};
    shortcuts <<  QList <QString> { "CTRL + S" , "Save transmitted data"};
    shortcuts <<  QList <QString> { "CTRL + T" , "Show run script UI"};
    shortcuts <<  QList <QString> { "CTRL + R" , "Run the selected script"};
    shortcuts <<  QList <QString> { "F1"       , "Open help"};
    shortcuts <<  QList <QString> { "Esc"      , "Hide evrything"};

    while (!shortcuts.isEmpty())
    {
        shortcutTable_addItem(shortcuts.at(0));
        shortcuts.pop_front();
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::setupShortcuts()
{
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_T), this, SLOT(showScriptUi()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_pushButton_script_run_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this, SLOT(showFindUi()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(EscPressed()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), this, SLOT(moveCursorToEnd()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_L), this, SLOT(clearOutput()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Comma), this, SLOT(toggleShowSettings()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this, SLOT(showConnectionSettings()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(selectScript()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), this, SLOT(connectOrDisconnect()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_3), this, SLOT(focus_3()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_2), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_3), this, SLOT(focus_3()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_pushButton_save_clicked()));
    new QShortcut(QKeySequence(Qt::Key_Enter), this, SLOT(keyEnterPressed()));
    new QShortcut(QKeySequence(Qt::Key_Return), this, SLOT(keyEnterPressed()));
    new QShortcut(QKeySequence(Qt::Key_Up), this, SLOT(keyUpPressed()));
    new QShortcut(QKeySequence(Qt::Key_Down), this, SLOT(keyDownPressed()));
    new QShortcut(QKeySequence(Qt::Key_F1), this, SLOT(showHelp()));
}
/////////////////////////////////////////////////////////////////
