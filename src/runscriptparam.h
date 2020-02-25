#ifndef RUNSCRIPTPARAM_H
#define RUNSCRIPTPARAM_H

#include <QObject>
#include "mainwindow.h"

class RunScriptParam
{
    RunScriptParam()
    {
    }

    static RunScriptParam s_Instance;


public:
    RunScriptParam(const RunScriptParam&) = delete;
    static RunScriptParam& get() { return s_Instance; }


    QString fileName;
    bool repeat;
    int timeout;
    dataFormat dFormat;

};






#endif // RUNSCRIPTPARAM_H
