android: {
    QT += androidextras

    tCopyToOutput(android-build)
    ANDROID_PERMISSIONS += com.farsitel.bazaar.permission.PAY_THROUGH_BAZAAR
    export(ANDROID_PERMISSIONS)
}else{
    message("CafeBazaar plugin work only on android, skipping all settings")
}

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/cafebazaarplugin.h

SOURCES += \
    $$PWD/cafebazaarplugin.cpp


#<uses-permission android:name="com.farsitel.bazaar.permission.PAY_THROUGH_BAZAAR"></uses-permission>
