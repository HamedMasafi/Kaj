INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
RESOURCES += $$PWD/core.qrc
DEFINES += KAJ_CORE_LIB

HEADERS += \
    $$PWD/src/swipegesturemanager.h \
    $$PWD/src/units.h \
    $$PWD/src/zoomarea.h \
    $$PWD/src/scalecontainer.h \
    $$PWD/src/zoomarea_p.h \
    $$PWD/src/swipegesturemanager_p.h \
    $$PWD/src/kajqmlhelper.h \
    $$PWD/src/kajpluginbase.h \
    $$PWD/src/kajglobal.h \
    $$PWD/src/platforms.h

SOURCES += \
    $$PWD/src/swipegesturemanager.cpp \
    $$PWD/src/units.cpp \
    $$PWD/src/zoomarea.cpp \
    $$PWD/src/scalecontainer.cpp \
    $$PWD/src/kajpluginbase.cpp \
    $$PWD/src/kajqmlhelper.cpp \
    $$PWD/src/platforms.cpp

OTHER_FILES = $$PWD/qml/Kaj/AutoLayout.qml \
            $$PWD/qml/Kaj/CircleButton.qml \
            $$PWD/qml/Kaj/CircleImage.qml \
            $$PWD/qml/Kaj/PagesView.qml
