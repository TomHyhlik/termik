#ifndef SHORTCUTS_H
#define SHORTCUTS_H


#include <QShortcut>
#include <QWidget>

/////////////////////////////////////////////////////////////////
const QList <QList <QString>> SHORTCUTS_CONTENT_MAINWINDOW =
{
    { "CTRL + P" , "Show connection settongs"},
    { "CTRL + D" , "Connect/Disconnect toggle"},

    { "CTRL + ," , "Show main settongs"},

    { "CTRL + O" , "Open a file \"script\"to run in terminal later"},
    { "CTRL + R" , "Run/Stop transmission of the selected \"script\""},

    { "CTRL + L" , "Move cursor to the end of the terminal output"},
    { "CTRL + SHIFT + L" , "Clear terminal output"},

    { "CTRL + 1" , "Set focus to ASCII tab"},
    { "CTRL + 2" , "Set focus to Hex tab"},
    { "CTRL + 3" , "Set focus to DEC tab"},

    { "CTRL + S" , "Open location where the terminal output shall be saved"},




    { "Esc"      , "Hide evrything"},
    { "CTRL + Q" , "Quit uiThis app"},
    { "F1"       , "Open help"}

};

/////////////////////////////////////////////////////////////////
void setupShortcuts(QWidget *uiThis)
{
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), uiThis, SLOT(on_pushButton_scriptRun_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), uiThis, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), uiThis, SLOT(showFastCommands()));
    new QShortcut(QKeySequence(Qt::Key_Escape), uiThis, SLOT(pressedKey_esc()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), uiThis, SLOT(moveCursorToEnd()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_L), uiThis, SLOT(clearOutput()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Comma), uiThis, SLOT(toggleShowSettings()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_Comma), uiThis, SLOT(toggleShowSettings()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), uiThis, SLOT(showConnectionSettings()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_P), uiThis, SLOT(showConnectionSettings()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), uiThis, SLOT(connectionToggle()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), uiThis, SLOT(openScript()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), uiThis, SLOT(focus_0()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), uiThis, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_3), uiThis, SLOT(focus_2()));

    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_1), uiThis, SLOT(focus_0()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_2), uiThis, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_3), uiThis, SLOT(focus_2()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), uiThis, SLOT(on_pushButton_save_clicked()));
//    new QShortcut(QKeySequence(Qt::Key_Enter), uiThis, SLOT(pressedKey_enter()));
//    new QShortcut(QKeySequence(Qt::Key_Return), uiThis, SLOT(pressedKey_enter()));
    new QShortcut(QKeySequence(Qt::Key_Up), uiThis, SLOT(pressedKey_up()));
    new QShortcut(QKeySequence(Qt::Key_Down), uiThis, SLOT(pressedKey_down()));
    new QShortcut(QKeySequence(Qt::Key_F1), uiThis, SLOT(toggleShowHelp()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), uiThis, SIGNAL(fastCmds_addCmd()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus), uiThis, SLOT(uiResize_minus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Equal), uiThis, SLOT(uiResize_plus()));


}
/////////////////////////////////////////////////////////////////







#endif // SHORTCUTS_H
