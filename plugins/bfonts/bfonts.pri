QT += core
 
for(f, KAJ_BFONTS){
    exists("$$PWD/resources/$${f}.qrc"){
        RESOURCES += "$$PWD/resources/$${f}.qrc"
    }else{
        message(The font $${f} does not exists!)
    }
}

DEFINES += KAJ_BFONTS=\"\\\"$$KAJ_BFONTS\\\"\"

HEADERS += \
    $$PWD/src/bfont.h

SOURCES += \
    $$PWD/src/bfont.cpp
