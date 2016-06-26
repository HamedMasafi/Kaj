android: {
    QT += androidextras

#    tCopyToOutput(android-build)
#    manifest.source = android-build
#    manifest.target = ..
#    COPYFOLDERS += manifest
#    copyData()

#DISTFILES += \
#    $$PWD/android-build/org/tooj/plugins/Notification.java

}else{
    message("Notification plugin work only on android, skipping all settings")
}

INCLUDEPATH += $$PWD
HEADERS += \
    $$PWD/share.h

SOURCES += \
    $$PWD/share.cpp
