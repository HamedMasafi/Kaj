INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
RESOURCES += $$PWD/game.qrc
DEFINES += KAJ_GAME_LIB
QML_IMPORT_PATH += $$PWD/qml
QML_DESIGNER_IMPORT_PATH += $$PWD/qml

HEADERS += \
#    $$PWD/src/Camera.h \
#    $$PWD/src/CameraMovementLogic.h \
#    $$PWD/src/Logic.h \
    $$PWD/src/gridmap.h \
    $$PWD/src/movementanimation.h \
    $$PWD/src/rotateanimation.h \
    $$PWD/src/gridmap_p.h \
    $$PWD/src/safezone.h \
    $$PWD/src/speedanimation.h \
    $$PWD/src/speedanimation_p.h \
    $$PWD/src/kajgameplugin.h

SOURCES += \
#    $$PWD/src/Camera.cpp \
#    $$PWD/src/CameraMovementLogic.cpp \
#    $$PWD/src/Logic.cpp \
    $$PWD/src/gridmap.cpp \
    $$PWD/src/movementanimation.cpp \
    $$PWD/src/rotateanimation.cpp \
    $$PWD/src/safezone.cpp \
    $$PWD/src/speedanimation.cpp \
    $$PWD/src/kajgameplugin.cpp
