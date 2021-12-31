import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import KarunitPlugins 1.0

Item {
    anchors.fill: parent

    Slider {
        property bool completed: false
        from: 1
        to: 100
        onValueChanged: if (completed)
                            KUPSoundController.setVolume(value)

        Component.onCompleted: {
            value = 1.0 * KUPSoundController.getVolume()
            completed = true
        }
    }
}
