#include "plugin.h"

QString KU_AlsaSound_Plugin::name() const
{
    return "AlsaSound";
}

QString KU_AlsaSound_Plugin::id() const
{
    return "AlsaSound.me";
}

KU::PLUGIN::PluginVersion KU_AlsaSound_Plugin::version() const
{
    return { 1, 0, 0 };
}

QSet<KU::PLUGIN::PluginInfo> KU_AlsaSound_Plugin::dependencies() const
{
    return QSet<KU::PLUGIN::PluginInfo>();
}

QString KU_AlsaSound_Plugin::license() const
{
    return "LGPL";
}

QIcon KU_AlsaSound_Plugin::icon() const
{
    return QIcon();
}

bool KU_AlsaSound_Plugin::initialize(const QSet<KU::PLUGIN::PluginInterface*>& plugins)
{
    return true;
}

bool KU_AlsaSound_Plugin::stop()
{
    return true;
}

QWidget* KU_AlsaSound_Plugin::createWidget()
{
    return nullptr;
}

QWidget* KU_AlsaSound_Plugin::createSettingsWidget()
{
    QWidget* widget = new QWidget;
    QFormLayout* layout = new QFormLayout;

    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setMaximumWidth(300);
    slider->setRange(0, 100);
    slider->setValue(this->getVolume());
    connect(slider, &QSlider::valueChanged, this, &KU_AlsaSound_Plugin::setVolume);
    layout->addRow(tr("Master volume"), slider);

    widget->setLayout(layout);
    return widget;
}

bool KU_AlsaSound_Plugin::loadSettings()
{
    return true;
}

bool KU_AlsaSound_Plugin::saveSettings() const
{
    return KU::Settings::instance()->status() == QSettings::NoError;
}

// https://stackoverflow.com/questions/6787318/set-alsa-master-volume-from-c-code
void KU_AlsaSound_Plugin::setVolume(long volume)
{
    long min, max;
    snd_mixer_t* handle;
    snd_mixer_selem_id_t* sid;
    const char* card = "default";
    const char* selem_name = "Master";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_close(handle);
}

long KU_AlsaSound_Plugin::getVolume()
{
    long volume, min, max;
    snd_mixer_t* handle;
    snd_mixer_selem_id_t* sid;
    const char* card = "default";
    const char* selem_name = "Master";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_MONO, &volume);

    snd_mixer_close(handle);

    return volume * 100 / max;
}
