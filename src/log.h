#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QStatusBar>

#include <iostream>


#define LOG(x)      Log::get().write(x)
#define LOG_T(x, y) Log::get().write(x, y)



#define LOGTIMEOUT_ERROR    300*1000
#define LOGTIMEOUT_NOTE     60*1000
#define LOGTIMEOUT_INFO     30*1000


enum logType {
    error, note, info
};



class Log
{
    Log(){}
    static Log s_Instance;

    QStatusBar *statusBar = nullptr;

    /////////////////////////////////
public:

    Log(const Log&) = delete;
    static Log& get() { return s_Instance; }

    void setEntities(QStatusBar *val) { statusBar = val; }


    void write(int type, QString messageData)
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
        std::cout << messageData.toStdString() << "\n";
    }

    void write(QString message) {
        write(info, message);
    }




};










#endif // LOG_H
