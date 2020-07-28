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


#define FCMD_MAXCNT     1000


class SaveFastCmds : public SaveToJson
{
    Q_OBJECT

    bool jsonData_parse(QByteArray) override;
    QByteArray jsonData_make() override;

public:

    SaveFastCmds();
    QList <FastCmdData> cmdDataList;


signals:

};

#endif // SAVEFASTCMDS_H
