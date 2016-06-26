android: {
    QT += androidextras

    tCopyToOutput(android-build)

    LIBS += $$PWD/android-build/libs/armeabi-v7a/libgpg.a

    INCLUDEPATH += $$PWD \
                $$PWD/include
}else{
    message("Google play service plugin work only on android, skipping all settings")
}

#<meta-data
#            android:name="com.google.android.gms.games.APP_ID"
#            android:value="@string/app_id" />


HEADERS += \
    $$PWD/googleplayservice.h

SOURCES += \
    $$PWD/googleplayservice.cpp


