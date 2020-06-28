#include "uilog.h"


UiLog UiLog::s_Instance;


/////////////////////////////////////////////////////////////////
void UiLog::write(int type, QString messageData)
{
    int timeout;

    switch (type)
    {
    case error:
        timeout = LOGTIMEOUT_ERROR;
        messageData.prepend("ERROR: ");
        break;

    case note:
        timeout = LOGTIMEOUT_NOTE;
        messageData.prepend("NOTE: ");
        break;

    case info:
        timeout = LOGTIMEOUT_INFO;
        break;
    default:
        return;
    }
    if (statusBar != nullptr) {
        statusBar->showMessage(messageData, timeout);
    }
//    std::cout << messageData.toStdString() << "\n";
}

/////////////////////////////////////////////////////////////////
void UiLog::write(QString message) {
    write(info, message);
}

/////////////////////////////////////////////////////////////////
