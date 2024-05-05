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
#include "form_fastcmd.h"
#include "savefastcmds.h"

#include <stdlib.h>

/////////////////////////////////////////////////////////////////
MainWindow::MainWindow(int argc, char** argv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUi();
    InitCommunicationWorker();
    InitColors();
    InitShortcuts();
    InitAppParams();
    
    currentAppConfig_loadSaved();
    fastCmds_load();

    CliArgHandler cliArgHandler(argc, argv);
    if (cliArgHandler.getComType() != comType_none)
        communic->establish(cliArgHandler.getComType());
}

/////////////////////////////////////////////////////////////////
void MainWindow::fastCmds_load()
{
    SaveFastCmds saveFastCmds;
    if (saveFastCmds.read())
    {
        for (const FastCmdData cmd : saveFastCmds.cmdDataList)
        {
            fastCmdsHandler->fastCmds_addCmd(cmd);
        }
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::fastCmds_save()
{
    SaveFastCmds saveFastCmds;

    for (int i = 0; i < fastCmdsHandler->count(); i++)
        saveFastCmds.cmdDataList.append(fastCmdsHandler->cmdAt(i)->getData());

    saveFastCmds.write();
}

/////////////////////////////////////////////////////////////////
void MainWindow::toggleShowHelp()
{
    if (ui->tableWidget_shortcuts->isVisible()) { hideHelp(); }
    else    { showHelp(); }
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

    for (const auto &shortcut : SHORTCUTS_CONTENT_MAINWINDOW)
        table_addItem(ui->tableWidget_shortcuts, shortcut);
}

/////////////////////////////////////////////////////////////////
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
    if (saveCfg.read())
    {
        /* load script parameters */
        if (!saveCfg.data.script.fileName.isEmpty()) {
            ui->lineEdit_scriptPath->setText(saveCfg.data.script.fileName);
        }

        /* RunScript settings */
        ui->comboBox_scriptDataFormat->setCurrentIndex(saveCfg.data.script.dFormat);
        ui->lineEdit_scriptPath->setText(saveCfg.data.script.fileName);

        ui->checkBox_scriptRepeatEnable->setChecked(saveCfg.data.script.repeat);
        ui->spinBox_scriptTransmissionPeriod->setValue(saveCfg.data.script.timeout);

        /* todo: continue here, load the saveCfg.data.app to ui */
    }
}

//////////////////////////////////////////////////////////////////////
void MainWindow::openScript()
{
    QString openLocation;

    if (!RunScriptParam::get().fileName.isEmpty())
    {
        openLocation = RunScriptParam::get().fileName;
    }
    else
    {
        openLocation = LOCATION_DEFAULT;
    }

    QString scriptFileName = QFileDialog::getOpenFileName(
                this, RunScriptParam::get().fileName);

    showSettings();
    ui->tabWidget_settings->setCurrentIndex(TABWIDGET_SETTINGS_INDEX_SCRIPT);

    if (!scriptFileName.isEmpty()) {
        ui->lineEdit_scriptPath->setText(scriptFileName);
        ui->lineEdit_scriptPath->setFocus();
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

    fastCmds_save();

    (void)event;
    LOG(QString("\nExitting...\n"));
}

/////////////////////////////////////////////////////////////////
void MainWindow::showConnectionSettings()
{
    Dialog_connect* dialog_connect = new Dialog_connect(this);
    connect(dialog_connect, SIGNAL(tryConnect(communicationType)), communic,
            SLOT(establish(communicationType)));
    dialog_connect->setComType(communic->getLastComType());
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
        LOG_T(error, STATMESSAGE_ERR_NOTCONNECTED);
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
    int terminalInput = terminalInputHasFocus();
    if (terminalInput != -1) {
        Tx_fromDataInput(terminalInput);
    }
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
void MainWindow::terminalOut_addPreamble(int dataKind)
{
    if (AppCfgParam::get().timeLogEnabled)
    {
        if ((RXDATAEVENT_TIMEOUT < sinceLastTermOutUpdate.restart()) ||
                (lastTerminalData != dataKind))
        {
            lastTerminalData = dataKind;

            QString preamble_base = terminalOutGetPreamble(dataKind);
            QString preamble_current;

            /* put the preamble into text edits and text files */
            for (int i = 0; i < TABWIDGET_TABCNT; i++)
            {
                preamble_current = preamble_base;

                /* Remove additional space character in the ascii textEdit */
                switch (i)
                {
                   case data_ascii:
                    {
                        QTextCursor cur = termIO[i].textEdit_out.textCursor();
                        cur.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor, 1);
                        /* Check if the last character has ASCII value bellow the space character */
                        if ((int)cur.selectedText().toStdString().c_str()[0] < 32)
                        {
                            termIO[i].textEdit_out.textCursor().removeSelectedText();
                            preamble_current.remove(0, 1);
                        }
                        break;
                    }
                }

                /* Write the preamble to the textEdit */
                writeToTextedit(&termIO[i].textEdit_out, COLOR_PREAMBLE, preamble_current);

                /* Write the preamble to the file */
                if (outputFile)
                {
                    switch (i)
                    {
                       case data_ascii:
                        outputFile->writeData_ascii(preamble_current);
                        break;
                    case data_hex:
                        outputFile->writeData_hex(preamble_current);
                        break;
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////
QString MainWindow::terminalOutGetPreamble(int dataKind)
{
    QString preamble;
    QDateTime dt = QDateTime::currentDateTime();
    QString time = dt.toString(TIME_FORMAT);

    preamble.append("\n");

    switch (dataKind)
    {
    case data_Rx:
        preamble.append("[Rx]-");
        break;
    case data_Tx:
        preamble.append("[Tx]-");
        break;
    default:
        preamble.append("");
    }

    preamble.append(time);
    preamble.append(" - ");

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
    ui->listWidget_fastCmds->hide();
}

/////////////////////////////////////////////////////////////////
void MainWindow::hideSettings()
{
    ui->tabWidget_settings->hide();
}
/////////////////////////////////////////////////////////////////
void MainWindow::showSettings()
{
    ui->tabWidget_settings->show();
}
/////////////////////////////////////////////////////////////////
void MainWindow::toggleShowSettings()
{
    if (ui->tabWidget_settings->isVisible())
        hideSettings();
    else
        showSettings();
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
    outputFile = (arg1 == Qt::Checked) ?
                std::unique_ptr <OutputFile> (new OutputFile(AppCfgParam::get().outputFileDir))
              : nullptr;
}
void MainWindow::on_checkBox_scriptRepeatEnable_stateChanged(int arg1)
{
    RunScriptParam::get().repeat = (arg1 == Qt::Checked) ? true : false;
}
void MainWindow::on_checkBox_autoclear_stateChanged(int arg1)
{
    AppCfgParam::get().autoclerTermOut = (arg1 == Qt::Checked) ? true : false;
}
void MainWindow::focus_0()
{
    focus_termIO(data_ascii);
}
void MainWindow::focus_1()
{
    focus_termIO(data_hex);
}
void MainWindow::focus_2()
{
    focus_termIO(data_dec);
}

/////////////////////////////////////////////////////////////////
void MainWindow::uiResize_minus()
{
    for (int i = 0; i < TABWIDGET_TABCNT; i++)
    {
        QTextCursor cursor = termIO[i].textEdit_out.textCursor();
        QFont f1 = termIO[i].textEdit_out.font();
        f1.setPointSize(f1.pointSize() - 1);
        termIO[i].textEdit_out.setFont(f1);
        termIO[i].textEdit_out.setTextCursor(cursor);
    }
}


void MainWindow::uiResize_plus()
{
    for (int i = 0; i < TABWIDGET_TABCNT; i++)
    {
        QTextCursor cursor = termIO[i].textEdit_out.textCursor();
        QFont f1 = termIO[i].textEdit_out.font();
        f1.setPointSize(f1.pointSize() + 1);
        termIO[i].textEdit_out.setFont(f1);
        termIO[i].textEdit_out.setTextCursor(cursor);
    }
}


/////////////////////////////////////////////////////////////////
void MainWindow::focus_termIO(int index)
{
    ui->tabWidget->setCurrentIndex(index);
    termIO[index].lineEdit_in.setFocus();
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

void MainWindow::on_spinBox_scriptTransmissionPeriod_valueChanged(int arg1)
{
    if (script != nullptr)  script->setTimeout(arg1);
    else    RunScriptParam::get().timeout = arg1;
}

void MainWindow::on_pushButton_scriptRun_clicked()
{
    if (!communic->isEstablished()) {
        LOG_T(error, STATMESSAGE_ERR_NOTCONNECTED);
        return;
    }

    if (script == nullptr) {
        LOG("Start to run script");
        script = std::unique_ptr <RunScript> (new RunScript());
        connect(script.get(), &RunScript::Tx, this, &MainWindow::Tx);
        connect(script.get(), &RunScript::finished, this, &MainWindow::runScript_finished) ;

        script->start();

        ui->pushButton_scriptRun->setText(TITLE_BUTTON_SCRIPT_STOP);
        ui->pushButton_scriptRun->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                .arg(COLOR_WHITE).arg(COLOR_RED));
    } else {
        script->stop();
        LOG("Running script forced to stop");
    }
}

/////////////////////////////////////////////////////////////////
void MainWindow::runScript_finished()
{
    ui->pushButton_scriptRun->setText(TITLE_BUTTON_SCRIPT_RUN);
    ui->pushButton_scriptRun->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                            .arg(COLOR_WHITE).arg(COLOR_GREEN));
    script = nullptr;
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_lineEdit_save_textChanged(const QString &arg1)
{
    AppCfgParam::get().outputFileDir = arg1;
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_comboBox_scriptDataFormat_currentTextChanged(const QString &arg1)
{
    RunScriptParam::get().dFormat = (dataFormat)title_dataFormat.indexOf(arg1);
}

//////////////////////////////////////////////////////////////////////
void MainWindow::InitAppParams()
{
    AppCfgParam::get().timeInfoEnabled = false;
    AppCfgParam::get().timeLogEnabled = true;
    AppCfgParam::get().clearOutputLine = true;
}

/////////////////////////////////////////////////////////////////
void MainWindow::InitColors()
{
    /* MainWindow background cikirs */
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

    /* PushButton colors */
    ui->pushButton_save->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                       .arg(COLOR_WHITE).arg(COLOR_GRAY0));
    ui->lineEdit_save->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                     .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->pushButton_scriptOpen->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                             .arg(COLOR_WHITE).arg(COLOR_GRAY0));
    ui->comboBox_scriptDataFormat->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                 .arg(COLOR_WHITE).arg(COLOR_BLACK));


    ui->spinBox_autoclear_maxCharCnt->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                    .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->spinBox_scriptTransmissionPeriod->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                        .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->lineEdit_scriptPath->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                           .arg(COLOR_WHITE).arg(COLOR_BLACK));
}

/////////////////////////////////////////////////////////////////
void MainWindow::InitUi()
{
    UiLog::get().setOutput(ui->statusBar);

    connect(ui->pushButton_scriptOpen, &QPushButton::clicked, this,
            &MainWindow::openScript);

    fastCmdsHandler = new FastCmdsHandler(ui->listWidget_fastCmds);
    connect(fastCmdsHandler, &FastCmdsHandler::Tx, this,
            &MainWindow::Tx);
    connect(this, &MainWindow::fastCmds_addCmd,
            fastCmdsHandler, &FastCmdsHandler::fastCmds_addCmdBlank);

    runScript_finished();

    ui->verticalLayout_tabwidget_ascii->addWidget(&termIO[data_ascii]);
    ui->verticalLayout_tabwidget_hex->addWidget(&termIO[data_hex]);
    ui->verticalLayout_tabwidget_dec->addWidget(&termIO[data_dec]);

    for (int i = 0; i < TABWIDGET_TABCNT; i++)
        connect(&termIO[i].lineEdit_in, &QLineEdit::returnPressed,
                this, &MainWindow::pressedKey_enter);

    setWindowTitle(QString("%1 v%2").arg(MAINWINDOWTITLE).arg(VERSION_CODE));

    ui->comboBox_scriptDataFormat->addItem(TITLE_DATA_ASCII);
    ui->comboBox_scriptDataFormat->addItem(TITLE_DATA_HEX);
    ui->spinBox_scriptTransmissionPeriod->setValue(SCRIPTTIMEOUT_DEFAULT);

    ui->checkBox_timeLog->setChecked(true);
    ui->checkBox_prefix->setChecked(false);
    ui->checkBox_suffix->setChecked(true);
    ui->checkBox_clearOutputLine->setChecked(true);
    ui->checkBox_scriptRepeatEnable->setChecked(true);
    ui->lineEdit_suffix->setText(QString(QByteArray(SUFFIX_DEFAULT).toHex().toUpper()));
    ui->spinBox_autoclear_maxCharCnt->setValue(AUTOCLEAR_VAL_DEFAULT);
    ui->spinBox_scriptTransmissionPeriod->setValue(SCRIPT_TXPERIOD_DEFAULT);

    ui->checkBox_autoclear->setChecked(true);
    ui->checkBox_autoclear->setChecked(false);
    ui->listWidget_fastCmds->hide();

    hideHelp();
    hideSettings();
    focus_0();
}

/////////////////////////////////////////////////////////////////
void MainWindow::InitShortcuts()
{
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_pushButton_scriptRun_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this, SLOT(showFastCommands()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(pressedKey_esc()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), this, SLOT(moveCursorToEnd()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_L), this, SLOT(clearOutput()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Comma), this, SLOT(toggleShowSettings()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_Comma), this, SLOT(toggleShowSettings()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this, SLOT(showConnectionSettings()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_P), this, SLOT(showConnectionSettings()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), this, SLOT(connectionToggle()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(openScript()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this, SLOT(focus_0()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_3), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_1), this, SLOT(focus_0()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_2), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_3), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_pushButton_save_clicked()));
    new QShortcut(QKeySequence(Qt::Key_Up), this, SLOT(pressedKey_up()));
    new QShortcut(QKeySequence(Qt::Key_Down), this, SLOT(pressedKey_down()));
    new QShortcut(QKeySequence(Qt::Key_F1), this, SLOT(toggleShowHelp()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this, SIGNAL(fastCmds_addCmd()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus), this, SLOT(uiResize_minus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Equal), this, SLOT(uiResize_plus()));
}
/////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////
void MainWindow::InitCommunicationWorker()
{
    communic = new Communication(this);
    connect(communic, SIGNAL(displayData(int, QByteArray)),
            this, SLOT(terminalOutUpdate(int, QByteArray)));
    connect(communic, SIGNAL(established_success()), this, SLOT(terminalInputSetFocus()));
    connect(communic, SIGNAL(established_failed()), this, SLOT(showConnectionSettings()));
}

/////////////////////////////////////////////////////////////////
void MainWindow::on_lineEdit_scriptPath_textChanged(const QString &arg1)
{
    RunScriptParam::get().fileName = arg1;
}

/////////////////////////////////////////////////////////////////
void MainWindow::showFastCommands()
{
    ui->listWidget_fastCmds->show();
}

/////////////////////////////////////////////////////////////////
