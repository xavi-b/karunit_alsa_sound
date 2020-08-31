TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets
TARGET          = karunit_alsa_sound
DESTDIR         = $$PWD/../karunit/app/plugins

LIBS += -lasound

LIBS += -L$$PWD/../karunit/plugininterface/ -lkarunit_plugininterface
INCLUDEPATH += $$PWD/../karunit/plugininterface

LIBS += -L$$PWD/../karunit/common/ -lkarunit_common
INCLUDEPATH += $$PWD/../karunit/common

LIBS += -L$$PWD/../karunit/third-party/xblog/lib -lxblog
INCLUDEPATH += $$PWD/../karunit/third-party/xblog/include

SUBDIRS += \
    src/

include(src/src.pri)
