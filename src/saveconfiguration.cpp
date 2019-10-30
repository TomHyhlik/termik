#include <QFile>
#include <QTextStream>

#include "saveconfiguration.h"

SaveConfiguration::SaveConfiguration(QObject *parent) : QObject(parent)
{
}

//////////////////////////////////////////////////////////////////////////////
bool SaveConfiguration::read()
{
    const QString filename = SAVECFG_FILENAME;
    if (QFile::exists(filename)) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            /* todo: read the data from the file
                to the SaveConfigurationData* data */

            return true;
        }
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////////
bool SaveConfiguration::write()
{
    const QString filename = SAVECFG_FILENAME;
    QFile file(filename);

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        file.resize(0);
        QTextStream dataStream(&file);

        file.flush();
        file.close();

        return true;
    }
    return false;
}
