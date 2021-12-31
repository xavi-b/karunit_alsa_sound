#include "soundcontroller.h"
#include <alsa/asoundlib.h>

SoundController::SoundController(QObject* parent) : QObject(parent)
{
}

// https://stackoverflow.com/questions/6787318/set-alsa-master-volume-from-c-code
Q_INVOKABLE void SoundController::setVolume(long volume)
{
    long                  min, max;
    snd_mixer_t*          handle;
    snd_mixer_selem_id_t* sid;
    const char*           card       = "default";
    const char*           selem_name = "Master";

    snd_mixer_open(&handle, 0);

    if (handle == NULL)
        return;

    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);

    if (sid != NULL)
    {
        snd_mixer_selem_id_set_index(sid, 0);
        snd_mixer_selem_id_set_name(sid, selem_name);
        snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

        if (elem != NULL)
        {
            snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
            snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);
        }
    }

    snd_mixer_close(handle);
}

Q_INVOKABLE long SoundController::getVolume()
{
    long                  volume = 0, min = 0, max = 100;
    snd_mixer_t*          handle;
    snd_mixer_selem_id_t* sid;
    const char*           card       = "default";
    const char*           selem_name = "Master";

    snd_mixer_open(&handle, 0);

    if (handle == NULL)
        return 0;

    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);

    if (sid != NULL)
    {
        snd_mixer_selem_id_set_index(sid, 0);
        snd_mixer_selem_id_set_name(sid, selem_name);
        snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

        if (elem != NULL)
        {
            snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
            snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_MONO, &volume);
        }
    }

    snd_mixer_close(handle);

    if (max == 0)
        return 0;

    return volume * 100 / max;
}
