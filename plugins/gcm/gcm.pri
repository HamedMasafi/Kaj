android{
    INCLUDEPATH += $$PWD

    !defined(FIREBASE_CPP_SDK_DIR, var): {
        message(FIREBASE_CPP_SDK_DIR was not defined)
        message(> If it is not downloaded yet)
        message(> Download it from https://firebase.google.com/download/cpp)
    }

    INCLUDEPATH += $$FIREBASE_CPP_SDK_DIR/include

    LIBS += -L$$FIREBASE_CPP_SDK_DIR/libs/android/armeabi-v7a/gnustl/ \
        -lfirebase_app \
        -lfirebase_messaging

    HEADERS += \
        $$PWD/src/googlegcm.h \
        $$PWD/src/gcmlistener.h

    SOURCES += \
        $$PWD/src/googlegcm.cpp \
        $$PWD/src/gcmlistener.cpp
} else {
    message(GCM plugin does not work an non-android kits)
}
