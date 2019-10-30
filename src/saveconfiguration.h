#ifndef SAVECONFIGURATION_H
#define SAVECONFIGURATION_H

#include <QObject>

#define SAVECFG_FILENAME "termik_cfg.json"


class SaveConfigurationData {
public:




};






class SaveConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit SaveConfiguration(QObject *parent = nullptr);


    bool read();
    bool write();

    SaveConfigurationData data;

signals:

public slots:
};

#endif // SAVECONFIGURATION_H
