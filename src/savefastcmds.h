#ifndef SAVEFASTCMDS_H
#define SAVEFASTCMDS_H

#include <QObject>

#include "savetojson.h"
#include "uilog.h"
#include "form_fastcmd.h"

#define SAVEFASTCMDS_FILENAME "./termik_fastCmds.json"

#define JSONTITLE_FCMD_NAME     "Name"
#define JSONTITLE_FCMD_DATA     "Data"
#define JSONTITLE_FCMD_FORMAT   "Format"
#define JSONTITLE_FCMD_ID       "Cmd_%1"

class SaveFastCmds : public SaveToJson
{
    Q_OBJECT

    QList <FastCmdData> cmdDataList;

    bool jsonData_parse(QByteArray) override;
    QByteArray jsonData_make() override;

public:

    SaveFastCmds();

    void addCmdData(FastCmdData cmdData);




signals:

};

#endif // SAVEFASTCMDS_H
