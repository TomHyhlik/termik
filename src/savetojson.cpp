#include "savetojson.h"
#include "uilog.h"

#include <QFile>
#include <QTextStream>

//////////////////////////////////////////////////////////////////////////////
bool SaveToJson::read()
{
    if (QFile::exists(fileName)) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray fileContent = file.readAll();
            file.close();
            if (jsonData_parse(fileContent)) {
                return true;
            } else {
                LOG_T(error, tr("Failed to parse json data in file %1")
                      .arg(fileName));
            }
        } else {
            LOG_T(error, tr("Failed to read file %1")
                  .arg(fileName));
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////
bool SaveToJson::write()
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        file.resize(0);
        QByteArray jsonData = jsonData_make();
        QTextStream dataStream(&file);
        dataStream << jsonData;
        file.flush();
        file.close();
        return true;
    }
    LOG(tr("Failed to write to: %1").arg(fileName));
    return false;
}

//////////////////////////////////////////////////////////////////////////////
