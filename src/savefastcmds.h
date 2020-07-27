#ifndef SAVEFASTCMDS_H
#define SAVEFASTCMDS_H

#include <QObject>

#include "savetojson.h"
#include "uilog.h"
#include "form_fastcmd.h"

#define SAVEFASTCMDS_FILENAME "./termik_fastCmds.json"




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
