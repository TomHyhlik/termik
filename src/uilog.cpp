#include "uilog.h"


Log Log::s_Instance;


/////////////////////////////////////////////////////////////////
void Log::write(int type, QString messageData)
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
void Log::write(QString message) {
    write(info, message);
}

/////////////////////////////////////////////////////////////////
