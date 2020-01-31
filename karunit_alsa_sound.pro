TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets
TARGET          = karunit_alsa_sound
DESTDIR         = $$PWD/../karunit/app/plugins

LIBS += -lasound

LIBS += -L$$PWD/../karunit/lib/
LIBS += -L$$PWD/../karunit/app/plugins/

LIBS += -lplugininterface
INCLUDEPATH += $$PWD/../karunit/plugininterface
DEPENDPATH += $$PWD/../karunit/plugininterface

LIBS += -lcommon
INCLUDEPATH += $$PWD/../karunit/common
DEPENDPATH += $$PWD/../karunit/common

SUBDIRS += \
    src/

include(src/src.pri)
