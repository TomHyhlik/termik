#ifndef APPCFGPARAM_H
#define APPCFGPARAM_H


#include <QObject>


class AppCfgParam
{
    AppCfgParam() {}

    static AppCfgParam s_Instance;

public:

    AppCfgParam(const AppCfgParam&) = delete;
    static AppCfgParam& get() { return s_Instance; }



    bool timeLogEnabled;

    bool suffix_tx_enabled;
    bool prefix_tx_enabled;

    QByteArray suffix_tx;
    QByteArray prefix_tx;

    bool timeInfoEnabled;
    bool clearOutputLine;

//    bool saveTerminalOutToFile;   // todo rm

    bool autoclerTermOut;
    int autoclerTermOut_maxChars;

    QString outputFileDir;


};




















#endif // APPCFGPARAM_H
