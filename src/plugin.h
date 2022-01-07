#ifndef ALSASOUNDPLUGIN_H
#define ALSASOUNDPLUGIN_H

#include <QtPlugin>
#include <QIcon>
#include <QDebug>
#include <QDateTime>
#include "plugininterface.h"
#include "settings.h"

class KU_AlsaSound_Plugin : public QObject, public KU::PLUGIN::PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "xavi-b.karunit.PluginInterface")
    Q_INTERFACES(KU::PLUGIN::PluginInterface)

public:
    virtual QString                   name() const override;
    virtual QString                   id() const override;
    virtual KU::PLUGIN::PluginVersion version() const override;
    virtual QString                   license() const override;
    virtual QString                   icon() const override;
    virtual bool                      initialize() override;
    virtual bool                      stop() override;

    virtual bool loadSettings() override;
    virtual bool saveSettings() override;

    void setVolume(long volume);
    long getVolume();
};

#endif // ALSASOUNDPLUGIN_H
