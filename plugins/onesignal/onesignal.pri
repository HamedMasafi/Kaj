android: {
    QT += androidextras

#    tCopyToOutput(android-build)

    ANDROID_JAVA_SOURCES.path = /src/org/kaj/plugins
    ANDROID_JAVA_SOURCES.files = $$files($$PWD/java/*.java)
    INSTALLS += ANDROID_JAVA_SOURCES

OTHER_FILES += ANDROID_JAVA_SOURCES.files

#    manifest.source = android-build
#    manifest.target = ..
#    COPYFOLDERS += manifest
#    copyData()

#DISTFILES += \
#    $$PWD/android-build/org/kaj/plugins/Notification.java

}else{
    #message("OneSignal plugin work only on android, skipping all settings")
#    QT += webengine webenginecore webenginewidgets
}

INCLUDEPATH += $$PWD
HEADERS += \
    $$PWD/onesignal.h

SOURCES += \
    $$PWD/onesignal_android.cpp \
    $$PWD/onesignal.cpp \
    $$PWD/onesignal_desktop.cpp

RESOURCES += \
    $$PWD/res.qrc

