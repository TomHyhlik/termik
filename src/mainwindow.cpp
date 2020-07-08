#include <QFileDialog>

#include <QDateTime>
#include <QDateTimeEdit>
#include <memory>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include "dialog_connect.h"
#include "dataconverter.h"
#include "saveconfiguration.h"
#include "cliarghandler.h"
#include "uilog.h"
#include "shortcuts.h"
#include "utils_tabWidget.h"

#include "communication.h"
#include "serialwparam.h"


/////////////////////////////////////////////////////////////////
MainWindow::MainWindow(int argc, char** argv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_ui();
    init_communication();
    init_colors();
    setupShortcuts(this);
    init_appParams();
    currentAppConfig_loadSaved();

    CliArgHandler cliArgHandler(argc, argv);
    if (cliArgHandler.getComType() != comType_none)
        communic->establish(cliArgHandler.getComType());

}

/////////////////////////////////////////////////////////////////
void MainWindow::toggleShowHelp()
{
    if (ui->tableWidget_shortcuts->isVisible()) {
        hideHelp();
    } else {
        showHelp();
    }
}

/////////////////////////////////////////////////////////////////
/// \brief MainWindow::showHelp
///     actually just show shortcuts table
void MainWindow::showHelp()
{
    ui->tableWidget_shortcuts->show();

    ui->tableWidget_shortcuts->setColumnCount(2);
    ui->tableWidget_shortcuts->setHorizontalHeaderLabels(
    {TITLE_HELPTABLE_SHORTCUT, TITLE_HELPTABLE_DESCRIPTION});

    for (const auto &shortcut : SHORTCUTS_CONTENT_MAINWINDOW) {
        table_addItem(ui->tableWidget_shortcuts, shortcut);
    }
}
void MainWindow::hideHelp()
{
    table_clear(ui->tableWidget_shortcuts);
    ui->tableWidget_shortcuts->hide();
}

//////////////////////////////////////////////////////////////////////
/// \brief MainWindow::currentAppConfig_loadSaved
///     load app configuration from json file at app startup
void MainWindow::currentAppConfig_loadSaved()
{
    SaveConfiguration saveCfg;
    if (saveCfg.read()) {

        /* load script parameters */
        if (!saveCfg.data.script.fileName.isEmpty()) {
            ui->lineEdit_script->setText(saveCfg.data.script.fileName);
        }

        /* RunScript settings */
        ui->comboBox_script_dataType->setCurrentIndex(saveCfg.data.script.dFormat);
        ui->lineEdit_script->setText(saveCfg.data.script.fileName);

        ui->checkBox_script_repeat->setChecked(saveCfg.data.script.repeat);
        ui->spinBox_script_period->setValue(saveCfg.data.script.timeout);

        /* todo: continue here, load the saveCfg.data.app to ui */

        LOG("Configuration loaded from json file");
    } else {
        LOG("No previous saved configuration found");
    }
}

//////////////////////////////////////////////////////////////////////
void MainWindow::selectScript()
{
    QString openLocation;

    if (!RunScriptParam::get().fileName.isEmpty())
        openLocation = RunScriptParam::get().fileName;
    else
        openLocation = LOCATION_DEFAULT;

    QString scriptFileName = QFileDialog::getOpenFileName(
                this, RunScriptParam::get().fileName);

    if (!scriptFileName.isEmpty()) {
        showScriptUi();
        ui->lineEdit_script->setText(scriptFileName);
        ui->pushButton_script_run->setFocus();
    }
}

//////////////////////////////////////////////////////////////////////
void MainWindow::connectionToggle()
{
    communic->establishToggle();
}

//////////////////////////////////////////////////////////////////////
/// \brief MainWindow::closeEvent
/// \param event
///     function called when the MainWindow is being closed
void MainWindow::closeEvent(QCloseEvent *event)
{
    SaveConfiguration saveCfg;
    saveCfg.write();

    (void)event;
    LOG(QString("\nClosing %1\n").arg(MAINWINDOWTITLE));
}

/////////////////////////////////////////////////////////////////
void MainWindow::showConnectionSettings()
{
    Dialog_connect* dialog_connect = new Dialog_connect(this);
    connect(dialog_connect, SIGNAL(tryConnect(communicationType)), communic,
            SLOT(establish(communicationType)));

    dialog_connect->show();
}

/////////////////////////////////////////////////////////////////
void MainWindow::terminalInputSetFocus()
{
    termIO[ui->tabWidget->currentIndex()].lineEdit_in.setFocus();
}

/////////////////////////////////////////////////////////////////
int MainWindow::terminalInputHasFocus()
{
    for (int i = 0; i < TABWIDGET_TABCNT; i++)
        if (termIO[i].lineEdit_in.hasFocus())
            return i;
    return -1;
}

/////////////////////////////////////////////////////////////////
void MainWindow::clearOutput()
{
    for (int i = 0; i < TABWIDGET_TABCNT; i++)
        termIO[i].textEdit_out.clear();
}

/////////////////////////////////////////////////////////////////
void MainWindow::Tx_fromDataInput(int inputType)
{
    QByteArray txData;
    dataConverter dataConv;
    QString termInData;

    termInData = termIO[inputType].lineEdit_in.text();

    dataConv.setStrOfIndex(inputType, termInData);
    txData = dataConv.getByteArray();

    Tx(txData);
}

/////////////////////////////////////////////////////////////////
void MainWindow::Tx(QByteArray txData)
{
    if (!communic->isEstablished()) {
        LOG_T(error, "Can't transmit. No connection established");
        return;
    }

    TxHistory_add(txData);

    if (AppCfgParam::get().prefix_tx_enabled)
        txData.prepend(AppCfgParam::get().prefix_tx);
    if (AppCfgParam::get().suffix_tx_enabled)
        txData.append(AppCfgParam::get().suffix_tx);

    if (!communic->dataTransmit(txData))
        LOG_T(error, "Failed to transmit data");

    if (AppCfgParam::get().clearOutputLine)
        for (int i = 0; i < TABWIDGET_TABCNT; i++)
            termIO[i].lineEdit_in.clear();
}

/////////////////////////////////////////////////////////////////
void MainWindow::pressedKey_enter()
{            
    int index = terminalInputHasFocus();
    if (index != -1)
        Tx_fromDataInput(index);
}

/////////////////////////////////////////////////////////////////
void MainWindow::pressedKey_up()
{
    if (!history_out.isEmpty()) {
        historyTxUpdate();

        if (history_out.size() > history_out_ptr + 1)
            history_out_ptr++;
    }
}
void MainWindow::pressedKey_down()
{
    if (!history_out.isEmpty()) {
        historyTxUpdate();

        if (history_out_ptr > 0)
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

        for (int i = 0; i < TABWIDGET_TABCNT; i++)
            termIO[i].lineEdit_in.setText(dataConv.getStrOfIndex(i));
    }
}

/////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////
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
void MainWindow::focus_0()
{
    ui->tabWidget->setCurrentIndex(TABWIDGET_INDEX_ASCII);
    termIO[TABWIDGET_INDEX_ASCII].lineEdit_in.setFocus();
}
void MainWindow::focus_1()
{
    ui->tabWidget->setCurrentIndex(TABWIDGET_INDEX_HEX);
    termIO[TABWIDGET_INDEX_HEX].lineEdit_in.setFocus();
}
void MainWindow::focus_2()
{
    ui->tabWidget->setCurrentIndex(TABWIDGET_INDEX_DEC);
    termIO[TABWIDGET_INDEX_DEC].lineEdit_in.setFocus();
}

/////////////////////////////////////////////////////////////////
void MainWindow::terminalOut_addPreamble(int dataKind)
{
    if (AppCfgParam::get().timeLogEnabled)
    {
        if ((RXDATAEVENT_TIMEOUT < sinceLastTermOutUpdate.restart()) ||
                (lastTerminalData != dataKind))
        {
            lastTerminalData = dataKind;

            QString preamble = terminalOutGetPreamble(dataKind);

            /* put the preamble into text edits */
            for (int i = 0; i < TABWIDGET_TABCNT; i++)
                writeToTextedit(&termIO[i].textEdit_out, COLOR_PREAMBLE, preamble);

            /* put the preamble into text file */
            if (outputFile) {
                outputFile->writeData_ascii(preamble);
                outputFile->writeData_hex(preamble);
            }
        }

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
    terminalOut_addPreamble(dataKind);

    QString dataColor = getDataColor(dataKind);

    dataConverter dataConv;
    dataConv.setByteArray(data);

    /* update terminal output text edits */
    for (int i = 0; i < TABWIDGET_TABCNT; i++)
        writeToTextedit(&termIO[i].textEdit_out,
                        dataColor, dataConv.getStrOfIndex(i));

    /* update terminal output log files */
    if (outputFile) {
        outputFile->writeData_ascii(dataConv.getStrAscii());
        outputFile->writeData_hex(dataConv.getStrHex());
    }

    /* clear part of the text in the text edits */
    if (AppCfgParam::get().autoclerTermOut)
        for (int i = 0; i < TABWIDGET_TABCNT; i++)
            shortenTextEdit(&termIO[i].textEdit_out);

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
        return "";
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::shortenTextEdit(QTextEdit* textEdit)
{
    if (textEdit->document()->blockCount() >
            AppCfgParam::get().autoclerTermOut_maxChars) {

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
/// \brief MainWindow::pressedKey_esc
///     slot emited when ESC key is pressed
///     It hides all config UIs
void MainWindow::pressedKey_esc()
{
    hideHelp();
    hideSettings();
    terminalInputSetFocus();
    hideScriptUi();
}

/////////////////////////////////////////////////////////////////
void MainWindow::hideSettings()
{
    ui->groupBox_settings->hide();
}
/////////////////////////////////////////////////////////////////
void MainWindow::showSettings()
{
    ui->groupBox_settings->show();
}
/////////////////////////////////////////////////////////////////
void MainWindow::toggleShowSettings()
{
    if (ui->groupBox_settings->isVisible()) {
        hideSettings();
    } else {
        showSettings();
    }
}

/////////////////////////////////////////////////////////////////
/// \brief MainWindow::moveCursorToEnd
// slot generated by hotkey moves cursor to end of text edit in all tabs
void MainWindow::moveCursorToEnd()
{
    for (int i = 0; i < TABWIDGET_TABCNT; i++)
        termIO[i].textEdit_out.moveCursor(QTextCursor::End);
}
/////////////////////////////////////////////////////////////////
void MainWindow::on_pushButton_save_clicked()
{
    QString openLocation =  (AppCfgParam::get().outputFileDir.isEmpty()) ?
                LOCATION_DEFAULT : AppCfgParam::get().outputFileDir;

    QString dir = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory where the terminal output data will be stored"),
                openLocation,
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        ui->lineEdit_save->setText(dir);
        ui->checkBox_outputSave->setCheckState(Qt::Unchecked);
        ui->checkBox_outputSave->setCheckState(Qt::Checked);
    }
}

/////////////////////////////////////////////////////////////////
///     switch focus to corresponding lineedit data input
void MainWindow::on_tabWidget_currentChanged(int index)
{
    termIO[index].lineEdit_in.setFocus();
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_spinBox_autoclear_maxCharCnt_valueChanged(int arg1)
{
    AppCfgParam::get().autoclerTermOut_maxChars = arg1;
}
/////////////////////////////////////////////////////////////////
void MainWindow::on_checkBox_prefix_stateChanged(int arg1)
{
    AppCfgParam::get().prefix_tx_enabled = (arg1 == Qt::Checked) ? true : false;
}
void MainWindow::on_checkBox_suffix_stateChanged(int arg1)
{
    AppCfgParam::get().suffix_tx_enabled = (arg1 == Qt::Checked) ? true : false;
}
void MainWindow::on_checkBox_timeLog_stateChanged(int arg1)
{
    AppCfgParam::get().timeLogEnabled = (arg1 == Qt::Checked) ? true : false;
}
void MainWindow::on_checkBox_clearOutputLine_stateChanged(int arg1)
{
    AppCfgParam::get().clearOutputLine = (arg1 == Qt::Checked) ? true : false;
}
void MainWindow::on_checkBox_outputSave_stateChanged(int arg1)
{
    bool state = (arg1 == Qt::Checked) ? true : false;
    // todo
    if (state) {
        outputFile = std::unique_ptr <OutputFile>
                (new OutputFile(AppCfgParam::get().outputFileDir));
    } else {
        outputFile = nullptr;
    }
}
void MainWindow::on_checkBox_script_repeat_stateChanged(int arg1)
{
    RunScriptParam::get().repeat = (arg1 == Qt::Checked) ? true : false;
}
void MainWindow::on_checkBox_autoclear_stateChanged(int arg1)
{
    AppCfgParam::get().autoclerTermOut = (arg1 == Qt::Checked) ? true : false;
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_lineEdit_suffix_textChanged(const QString &arg1)
{
    dataConverter dataConv;
    dataConv.setStrHex(arg1);
    AppCfgParam::get().suffix_tx = dataConv.getByteArray();
}

void MainWindow::on_lineEdit_prefix_textChanged(const QString &arg1)
{
    dataConverter dataConv;
    dataConv.setStrHex(arg1);
    AppCfgParam::get().prefix_tx = dataConv.getByteArray();
}

void MainWindow::on_spinBox_script_period_valueChanged(int arg1)
{
    if (script == nullptr) {
        RunScriptParam::get().timeout = arg1;
    } else {
        script->setTimeout(arg1);
    }
}

void MainWindow::on_pushButton_script_run_clicked()
{
    if (!communic->isEstablished())
        return;

    if (script == nullptr) {
        script = std::unique_ptr <RunScript> (new RunScript());
        connect(script.get(), SIGNAL(Tx(QByteArray)), this, SLOT(Tx(QByteArray)));
        connect(script.get(), SIGNAL(finished()), this, SLOT(runScript_finished()));
        connect(script.get(), SIGNAL(Uilog(int, QString)), &UiLog::get(), SLOT(write(int, QString)));

        script->start();

        ui->pushButton_script_run->setText(TITLE_BUTTON_SCRIPT_STOP);
        ui->pushButton_script_run->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                 .arg(COLOR_WHITE).arg(COLOR_RED));
    } else {
        script->stop();
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::runScript_finished()
{
    ui->pushButton_script_run->setText(TITLE_BUTTON_SCRIPT_RUN);
    ui->pushButton_script_run->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                             .arg(COLOR_WHITE).arg(COLOR_GREEN));
    script = nullptr;
    LOG("");
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
    AppCfgParam::get().outputFileDir = arg1;
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
void MainWindow::on_lineEdit_script_textChanged(const QString &arg1)
{
    RunScriptParam::get().fileName = arg1;
}

//////////////////////////////////////////////////////////////////////
void MainWindow::init_appParams()
{
    AppCfgParam::get().timeInfoEnabled = false;
    AppCfgParam::get().timeLogEnabled = true;
    AppCfgParam::get().clearOutputLine = true;
}

/////////////////////////////////////////////////////////////////
void MainWindow::init_colors()
{
    /* MainWindow background */
    this->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                        .arg(COLOR_WHITE).arg(COLOR_GRAY2));

    ui->lineEdit_save->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                     .arg(COLOR_WHITE).arg(COLOR_GRAY4));

    ui->statusBar->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                 .arg(COLOR_WHITE).arg(COLOR_GRAY1));

    ui->lineEdit_prefix->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_suffix->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->tab_ascii->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                 .arg(COLOR_WHITE).arg(COLOR_GRAY3));
    ui->tab_hex->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                               .arg(COLOR_WHITE).arg(COLOR_GRAY3));
    ui->tab_dec->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                               .arg(COLOR_WHITE).arg(COLOR_GRAY3));

    for (int i = 0; i < TABWIDGET_TABCNT; i++)
    {
        termIO[i].textEdit_out.setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                             .arg(COLOR_WHITE).arg(COLOR_BLACK));
        termIO[i].lineEdit_in.setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                            .arg(COLOR_WHITE).arg(COLOR_BLACK));
    }

    /* pushbuttons */
    ui->pushButton_save->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                       .arg(COLOR_WHITE).arg(COLOR_GRAY0));
    ui->lineEdit_save->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                     .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->lineEdit_script->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_script_dataType->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->spinBox_autoclear_maxCharCnt->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                    .arg(COLOR_WHITE).arg(COLOR_BLACK));
}

/////////////////////////////////////////////////////////////////
void MainWindow::init_ui()
{
    UiLog::get().setOutput(ui->statusBar);

    runScript_finished();

    ui->verticalLayout_tabwidget_ascii->addWidget(&termIO[TABWIDGET_INDEX_ASCII]);
    ui->verticalLayout_tabwidget_hex->addWidget(&termIO[TABWIDGET_INDEX_HEX]);
    ui->verticalLayout_tabwidget_dec->addWidget(&termIO[TABWIDGET_INDEX_DEC]);

    setWindowTitle(MAINWINDOWTITLE);

    ui->comboBox_script_dataType->addItem(TITLE_DATA_ASCII);
    ui->comboBox_script_dataType->addItem(TITLE_DATA_HEX);
    ui->spinBox_script_period->setValue(SCRIPTTIMEOUT_DEFAULT);

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

    hideHelp();
    hideScriptUi();
    hideSettings();
    focus_0();
}

/////////////////////////////////////////////////////////////////
void MainWindow::init_communication()
{
    communic = new Communication(this);
    connect(communic, SIGNAL(displayData(int, QByteArray)),
            this, SLOT(terminalOutUpdate(int, QByteArray)));
    connect(communic, SIGNAL(established_success()), this, SLOT(terminalInputSetFocus()));
    connect(communic, SIGNAL(established_failed()), this, SLOT(showConnectionSettings()));
}

/////////////////////////////////////////////////////////////////
