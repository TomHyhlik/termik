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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include "dialog_connect.h"


/////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("USB terminal");       // set name of this dialog

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
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this, SLOT(showConnectionSettings()));
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

}
//////////////////////////////////////////////////////////////////////
void MainWindow::connectVia_serial()
{
    connectionType = serial;

    if(sw->isOpen()) {
        sw->close();
    }

    if (sw->open()) {
        log(note, "Connected via Serial");
    } else {
        log(note, "Failed to connect via Serial");
    }
}
//////////////////////////////////////////////////////////////////////
void MainWindow::connectVia_network()
{
    connectionType = network;
    if (nw->open()) {
        log(note, "Connected via Network");
    } else {
        log(note, "Failed to connect via Network");
    }
}
/////////////////////////////////////////////////////////////////
void MainWindow::uiInit()
{
    setWindowTitle(MAINWINDOWTITLE);

    /*************************** set colors ***************************/
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


    /*************************** UI setup ****************************/

    /* setup the help table */
    ui->tableWidget_shortcuts->setColumnCount(2);
    QStringList titles;
    titles << "Shortcut" << "description";
    ui->tableWidget_shortcuts->setHorizontalHeaderLabels(titles);
    ui->tableWidget_shortcuts->horizontalHeader()->setStretchLastSection(true);  // set column size to widget size

    /*************************** UI show/hide widgets ******************/
    ui->checkBox_clearIn_ascii->setChecked(true);
    ui->checkBox_clearIn_hex->setChecked(true);
    ui->checkBox_clearIn_dec->setChecked(true);

    ui->checkBox_prefix->setChecked(false);
    ui->checkBox_suffix->setChecked(true);
    ui->lineEdit_prefix->setText(sw->prefix.toHex());
    ui->lineEdit_suffix->setText(sw->suffix.toHex());

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
    case 0:
        ui->lineEdit_in_ascii->setFocus();
        break;
    case 1:
        ui->lineEdit_in_hex->setFocus();
        break;
    case 2:
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
/// \brief MainWindow::keyEnterPressed
///     slot callet when Enter or Return key is pressed
///
void MainWindow::keyEnterPressed()
{
    ////////////////////////////
    if (ui->lineEdit_save->hasFocus()) {
        QString fileLocation = ui->lineEdit_save->text();

        QDateTime dt = QDateTime::currentDateTime();
        QString timeStr = dt.toString( "yyyy-MM-dd_hh:mm:ss" );
//        ui->textEdit_out_ascii->append(timeStr); to debug
        QString fileName = QString("TerminalOutput_%1").arg(timeStr);

        file.setFileName(fileName);
        /*  todo */
        fileDataFormat = data_ascii;

        hideSaveSettings();
        log(info, QString("Output saved to: %1%2").arg(fileLocation).arg(fileName));
    }
    ////////////////////////////
    else if (ui->lineEdit_in_ascii->hasFocus()) {
        if(sw->isOpen()){
            QString data = ui->lineEdit_in_ascii->text();
            QByteArray out = data.toUtf8();
            terminalOutUpdate(usbTx, out);
            sw->write(out);
            log(note, "Data was sent");
       } else {
            log(error, "USB port is not opened");
        }
        /* clear the line */
        if(ui->checkBox_clearIn_ascii->isChecked())
            ui->lineEdit_in_ascii->clear();
    }
    ////////////////////////////
    else if (ui->lineEdit_in_hex->hasFocus()) {
        if(sw->isOpen()){
            QString data = ui->lineEdit_in_hex->text();
            QByteArray out = data.toUtf8();
            out = QByteArray::fromHex(out);
            sw->write(out);
            terminalOutUpdate(usbTx, out);
            log(note, "Data was sent");
       } else {
            log(error, "USB port is not opened");
        }
        /* clear the line */
        if(ui->checkBox_clearIn_hex->isChecked())
            ui->lineEdit_in_hex->clear();
    }
    ////////////////////////////
    else if (ui->lineEdit_in_dec->hasFocus()) {
        if (sw->isOpen()) {
            QString data = ui->lineEdit_in_dec->text();
            bool ok;
            QString element;
            QByteArray out;
            for (int i = 0; i <= data.size(); i += DIGIT_NUM_DEC) {
                element = data.mid(i, DIGIT_NUM_DEC);
                if (element.size() != 0) {
                    while (element.size() < DIGIT_NUM_DEC) {
                        element.append("0");
                    }
                    quint32 num = element.toUInt(&ok, 10);
                    out.append(qint8(num));
                }
            }
            sw->write(out);
            terminalOutUpdate(usbTx, out);

            log(note, "Data was sent");
       } else {
            log(error, "USB port is not opened");
        }
        /* clear the line */
        if(ui->checkBox_clearIn_dec->isChecked())
            ui->lineEdit_in_dec->clear();
    }

}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::keyUpPressed
///     slot called when arrow Up is pressed
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
            /* todo */
        }
        else if (ui->lineEdit_in_dec->hasFocus()){
            /* todo */
        }
    }
    if (history_out.size() > history_out_pointer + 1)
        history_out_pointer++;

}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::keyDownPressed
///     slot called when arrow Down is pressed
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
/// \brief MainWindow::fillShortcutsTable
///         fill the table of shortcuts
void MainWindow::fillShortcutsTable()
{
    QList <QString> shortcuts;

    shortcuts << "CTRL + Q" << "Quit application";
    shortcuts << "Esc"      << "Hide evrything";
    shortcuts << "CTRL + L" << "Move cursor to the end of the terminal output";
    shortcuts << "CTRL + SHIFT + L" << "Clear terminal output";
    shortcuts << "CTRL + T" << "Change theme (not supported yet)";
    shortcuts << "CTRL + O" << "Open port settongs";
    shortcuts << "CTRL + D" << "Connect / Disconnect";
    shortcuts << "CTRL + 1" << "Set focus to ASCII tab";
    shortcuts << "CTRL + 2" << "Set focus to Hex tab";
    shortcuts << "CTRL + 3" << "Set focus to DEC tab";
    shortcuts << "CTRL + W" << "Show terminal input wrap options";
    shortcuts << "CTRL + F" << "Find (not supported yet)";
    shortcuts << "CTRL + S" << "Show save settings";
    shortcuts << "F1"       << "Open help";

    while (!shortcuts.isEmpty())
    {
        QList<QString> row;
        row << shortcuts.at(0) << shortcuts.at(1);
        shortcuts.pop_front();
        shortcuts.pop_front();
        shortcutTable_addItem(row);
    }

//    ui->tableWidget_shortcuts->resizeColumnToContents(0);
//    ui->tableWidget_shortcuts->resizeColumnToContents(1);

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
/// \brief dialog_config::getFirstMapVal return the opposite value
/// of the map
/// \param m: map
/// \param label the second value of the map
/// \return tohe opposite value
int MainWindow::getFirstMapVal(QMap<int,QString> m, QString label)
{
    for(auto e : m.toStdMap())
    {
        if(label == e.second)
            return e.first;
    }
    return 0;
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

/////////////////////////////////////////////////////////////////
/// \brief MainWindow::dataArrived
///     process the list of received data
void MainWindow::dataArrived()
{
    tick_lastRx = tick.elapsed();

     /* get the data from apropriate class */
    switch (connectionType)
    {
    case serial:
        terminalOutUpdate(usbRx, sw->Rx_buffer.data());
        sw->Rx_buffer.clear();
        break;
    case network:
        terminalOutUpdate(usbRx, nw->Rx_buffer.data());
        nw->Rx_buffer.clear();
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
        data.prepend("Info: ");
    }

    ui->statusBar->showMessage(data, timeout);
}
/////////////////////////////////////////////////////////////////
/// \brief MainWindow::terminalOutUpdate
/// \param dataKind     to set the color
/// \param data         to be put to all text edits in corresponding format
///
void MainWindow::terminalOutUpdate(terminalData_t dataKind, QByteArray data)
{
    QString color;

    switch(dataKind)
    {
    case usbRx:
        color = COLOR_DATA_RX;
        break;

    case usbTx:
        color = COLOR_DATA_TX;
        /* add the Tx data to the history_out */
        if (history_out.isEmpty()) {
            history_out.prepend(data);
        }
        else if (history_out.at(0) != data) {
            history_out.prepend(data);
        }
        history_out_pointer = 0;

        /* append / prepend */
        if (ui->checkBox_suffix->isChecked())
            data.append(sw->suffix);
        if (ui->checkBox_prefix->isChecked())
            data.prepend(sw->prefix);
        break;
    }

    /* update all terminal outputs (textEdits) */

    QTextCursor prev_cursor;

    /************** ASCII **************/
    prev_cursor = ui->textEdit_out_ascii->textCursor();
    ui->textEdit_out_ascii->moveCursor(QTextCursor::End);

    ui->textEdit_out_ascii->setTextColor(color);
    QString data_str_ascii = QString(data);
    ui->textEdit_out_ascii->insertPlainText(data_str_ascii);

    ui->textEdit_out_ascii->setTextCursor(prev_cursor);


    /************** HEX **************/
    prev_cursor = ui->textEdit_out_hex->textCursor();
    ui->textEdit_out_hex->moveCursor(QTextCursor::End);
    QString data_str_hex;

    for(int i = 0; i < data.size(); i++){
        QString numStr = QString::number(quint8(data.at(i)), 16);
        while(numStr.size() < 2){
            numStr.prepend("0");
        }
        data_str_hex.append(QString(" %1").arg(numStr));
    }
    ui->textEdit_out_hex->setTextColor(color);
    ui->textEdit_out_hex->insertPlainText(data_str_hex);       // insert the data
    ui->textEdit_out_hex->setTextCursor(prev_cursor);           // set the cursor back


    /************** DEC **************/
    prev_cursor = ui->textEdit_out_dec->textCursor();
    ui->textEdit_out_dec->moveCursor(QTextCursor::End);
    QString data_str_dec;

    for(int i = 0; i < data.size(); i++){
        QString numStr = QString::number(quint8(data.at(i)), 10);
        while(numStr.size() < 3){
            numStr.prepend("0");
        }
        data_str_dec.append(QString(" %1").arg(numStr));
    }

    ui->textEdit_out_dec->setTextColor(color);
    ui->textEdit_out_dec->insertPlainText(data_str_dec);       // insert the data
    ui->textEdit_out_dec->setTextCursor(prev_cursor);           // set the cursor back

    /* put the data into txt file */
    switch (fileDataFormat)
    {
    case data_ascii:
        saveToFile(data_str_ascii);
        break;
    case data_hex:
        saveToFile(data_str_hex);
        break;
    case data_dec:
        saveToFile(data_str_dec);
        break;
    case data_bin:
       /* todo (maybe) */
        break;
    }
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
    sw->prefix_enabled = ui->checkBox_prefix->isChecked();
    sw->suffix_enabled = ui->checkBox_suffix->isChecked();

    QByteArray data;
    data = ui->lineEdit_prefix->text().toUtf8();
    sw->prefix = QByteArray::fromHex(data);

    data.clear();
    data = ui->lineEdit_suffix->text().toUtf8();
    sw->suffix = QByteArray::fromHex(data);

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
                                                 "/Users/tomashyhlik/Dropbox/program/Workplaces/Qt/projects/USB_terminal",
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















