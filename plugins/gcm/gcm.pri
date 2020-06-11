INCLUDEPATH += $$PWD

!defined(FIREBASE_CPP_SDK_DIR, var): {
    message(FIREBASE_CPP_SDK_DIR was not defined)
    message(> If it is not downloaded yet)
    message(> Download it from https://firebase.google.com/download/cpp)
} else {
    exists($$FIREBASE_CPP_SDK_DIR){
        DEFINES += KAJ_PLUGIN_GCM
        INCLUDEPATH += $$FIREBASE_CPP_SDK_DIR/include

        android {
            contains(ANDROID_TARGET_ARCH,armeabi-v7a)  {
                LIBS += -L$$FIREBASE_CPP_SDK_DIR/libs/android/armeabi-v7a/c++
            }
            contains(ANDROID_TARGET_ARCH,arm64-v8a)  {
                LIBS += -L$$FIREBASE_CPP_SDK_DIR/libs/android/arm64-v8a/gnustl
            }
            contains(ANDROID_TARGET_ARCH,x86)  {
                LIBS += -L$$FIREBASE_CPP_SDK_DIR/libs/android/x86/gnustl
            }
            contains(ANDROID_TARGET_ARCH,x86_64)  {
                LIBS += -L$$FIREBASE_CPP_SDK_DIR/libs/android/x86_64/gnustl
            }
        }
        linux {
            LIBS += -L$$FIREBASE_CPP_SDK_DIR/libs/linux/x86_64
        }

        LIBS += \
            -lfirebase_messaging \
            -lfirebase_app

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
