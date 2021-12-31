#include "plugin.h"
#include "soundcontroller.h"
#include <QQmlEngine>

QString KU_AlsaSound_Plugin::name() const
{
    return "AlsaSound";
}

QString KU_AlsaSound_Plugin::id() const
{
    return "karunit_alsa_sound";
}

KU::PLUGIN::PluginVersion KU_AlsaSound_Plugin::version() const
{
    return {1, 0, 0};
}

QString KU_AlsaSound_Plugin::license() const
{
    return "LGPL";
}

QString KU_AlsaSound_Plugin::icon() const
{
    return QString();
}

bool KU_AlsaSound_Plugin::initialize()
{
    qmlRegisterSingletonInstance("KarunitPlugins", 1, 0, "KUPSoundController", new SoundController(this));

    return true;
}

bool KU_AlsaSound_Plugin::stop()
{
    return true;
}

bool KU_AlsaSound_Plugin::loadSettings()
{
    return true;
}

bool KU_AlsaSound_Plugin::saveSettings() const
{
    return KU::Settings::instance()->status() == QSettings::NoError;
}
