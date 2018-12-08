android{
    INCLUDEPATH += $$PWD

    !defined(FIREBASE_CPP_SDK_DIR, var): {
        message(FIREBASE_CPP_SDK_DIR was not defined)
        message(> If it is not downloaded yet)
        message(> Download it from https://firebase.google.com/download/cpp)
    }

    exists($$FIREBASE_CPP_SDK_DIR){
        DEFINES += KAJ_PLUGIN_GCM
        INCLUDEPATH += $$FIREBASE_CPP_SDK_DIR/include

        LIBS += -L$$FIREBASE_CPP_SDK_DIR/libs/android/armeabi-v7a/gnustl/ \
            -lfirebase_app \
            -lfirebase_messaging

        HEADERS += \
            $$PWD/src/gcmlistener.h

        SOURCES += \
            $$PWD/src/gcmlistener.cpp
    } else {
        message("$$FIREBASE_CPP_SDK_DIR not exixts")
    }
}

HEADERS += \
    $$PWD/src/googlegcm.h

SOURCES += \
    $$PWD/src/googlegcm.cpp
