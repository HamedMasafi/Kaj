INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
QML_IMPORT_PATH += $$PWD/qml
DEFINES += KAJ_APP_LIB
DESTDIR = qml/Kaj/App
TARGET = kaj.app

RESOURCES += $$PWD/app.qrc

HEADERS += \
    $$PWD/kajappmodule.h
