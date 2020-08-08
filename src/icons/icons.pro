CONFIG += no_app_extension_api_only
load(qt_build_config)

TARGET = QtKajIcons
QT = core quick qml

#MODULE = kajicons

load(qt_module)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
DEFINES += KAJ_ICONS_LIB

HEADERS += \
    $$PWD/icons.h

SOURCES += \
    $$PWD/icons.cpp \
    $$PWD/icons_mdi.cpp
    $$PWD/icons_fa.cpp

