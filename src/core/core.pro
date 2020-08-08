CONFIG += no_app_extension_api_only
load(qt_build_config)

TARGET = QtKajCore
QT = quick qml

MODULE = kajcore

load(qt_module)

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
RESOURCES += $$PWD/core.qrc
DEFINES += KAJ_GAME_LIB
QML_IMPORT_PATH += $$PWD/qml
QML_DESIGNER_IMPORT_PATH += $$PWD/qml

HEADERS += \
    $$PWD/src/appcolors.h \
    $$PWD/src/contactsmodel.h \
    $$PWD/src/icons.h \
    $$PWD/src/swipegesturemanager.h \
    $$PWD/src/units.h \
    $$PWD/src/zoomarea.h \
    $$PWD/src/scalecontainer.h \
    $$PWD/src/zoomarea_p.h \
    $$PWD/src/swipegesturemanager_p.h \
    $$PWD/src/kajqmlhelper.h \
    $$PWD/src/kajpluginbase.h \
    $$PWD/src/kajglobal.h \
    $$PWD/src/platforms.h \
    $$PWD/src/kajmodule.h \
    $$PWD/src/application.h \
    $$PWD/src/mobility.h \
    $$PWD/src/fileutils.h \
    $$PWD/src/shape.h

SOURCES += \
    $$PWD/src/appcolors.cpp \
    $$PWD/src/contactsmodel.cpp \
    $$PWD/src/icons.cpp \
    $$PWD/src/swipegesturemanager.cpp \
    $$PWD/src/units.cpp \
    $$PWD/src/zoomarea.cpp \
    $$PWD/src/scalecontainer.cpp \
    $$PWD/src/kajpluginbase.cpp \
    $$PWD/src/kajqmlhelper.cpp \
    $$PWD/src/platforms.cpp \
    $$PWD/src/kajmodule.cpp \
    $$PWD/src/application.cpp \
    $$PWD/src/mobility.cpp \
    $$PWD/src/fileutils.cpp \
    $$PWD/src/shape.cpp
