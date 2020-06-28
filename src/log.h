#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QStatusBar>

#include <iostream>


#define LOG(x)      Log::get().write(x)
#define LOG_T(x, y) Log::get().write(x, y)



#define LOGTIMEOUT_ERROR    300*1000
#define LOGTIMEOUT_NOTE     300*1000
#define LOGTIMEOUT_INFO     30*1000


enum logType {
    error, note, info
};



class Log : public QObject
{
    Q_OBJECT

    Log(){}
    static Log s_Instance;

    QStatusBar *statusBar = nullptr;


public:
    Log(const Log&) = delete;
    static Log& get() { return s_Instance; }

    void setOutput(QStatusBar *val) { statusBar = val; }


public slots:
    void write(int type, QString messageData);
    void write(QString message);



};










#endif // LOG_H
