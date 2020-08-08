load(qt_build_config)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TARGET = QKajQmlCore
QT = core qml quick gui

MODULE = kajqmlcore

load(qt_module)

DEFINES += KAJ_QMLCORE_LIB

HEADERS += \
    $$PWD/units.h \
    $$PWD/kajglobal.h \
    $$PWD/scalecontainer.h \
    $$PWD/shape.h \
    $$PWD/swipegesturemanager.h \
    $$PWD/swipegesturemanager_p.h \
    $$PWD/zoomarea.h \
    $$PWD/zoomarea_p.h \
    kajqmlcoremodule.h

SOURCES += \
    $$PWD/units.cpp \
    $$PWD/scalecontainer.cpp \
    $$PWD/shape.cpp \
    $$PWD/swipegesturemanager.cpp \
    $$PWD/zoomarea.cpp \
    kajqmlcoremodule.cpp
