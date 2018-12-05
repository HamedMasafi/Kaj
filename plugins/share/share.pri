android: {
    QT += androidextras

    HEADERS += \
        $$PWD/androidintent.h \
        $$PWD/androidjniarraylist.h

    SOURCES += \
        $$PWD/androidintent.cpp \
        $$PWD/androidjniarraylist.cpp

}else{
    message("Share plugin work only on android, skipping all settings")
}

INCLUDEPATH += $$PWD
HEADERS += \
    $$PWD/share.h

SOURCES += \
    $$PWD/share.cpp
