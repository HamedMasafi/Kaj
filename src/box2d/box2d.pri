DEFINES += KAJ_BOX2D_LIB
QML_IMPORT_PATH += $$PWD/qml
QML_DESIGNER_IMPORT_PATH += $$PWD/qml
RESOURCES += $$PWD/box2d.qrc

INCLUDEPATH += ../../3rdparty/qml-box2d
include(../../3rdparty/qml-box2d/box2d-static.pri);

HEADERS += \
    $$PWD/kajbox2dplugin.h

SOURCES += \
    $$PWD/kajbox2dplugin.cpp
