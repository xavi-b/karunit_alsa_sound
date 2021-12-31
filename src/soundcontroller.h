#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QObject>

class SoundController : public QObject
{
    Q_OBJECT

public:
    SoundController(QObject* parent = nullptr);

    // https://stackoverflow.com/questions/6787318/set-alsa-master-volume-from-c-code
    Q_INVOKABLE void setVolume(long volume);

    Q_INVOKABLE long getVolume();
};

#endif // SOUNDCONTROLLER_H
