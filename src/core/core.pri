INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
RESOURCES += $$PWD/core.qrc
DEFINES += KAJ_CORE_LIB
QML_IMPORT_PATH += $$PWD/qml
QML_DESIGNER_IMPORT_PATH += $$PWD/qml/Kaj

HEADERS += \
    $$PWD/src/appcolors.h \
    $$PWD/src/contactsmodel.h \
    $$PWD/src/icons.h \
    $$PWD/src/swipegesturemanager.h \
    $$PWD/src/units.h \
    $$PWD/src/zoomarea.h \
    $$PWD/src/scalecontainer.h \
    $$PWD/src/zoomarea_p.h \
    $$PWD/src/swipegesturemanager_p.h \
    $$PWD/src/kajqmlhelper.h \
    $$PWD/src/kajpluginbase.h \
    $$PWD/src/kajglobal.h \
    $$PWD/src/platforms.h \
    $$PWD/src/kajmodule.h \
    $$PWD/src/application.h \
    $$PWD/src/mobility.h \
    $$PWD/src/fileutils.h \
#    $$PWD/src/request/webrequest.h \
#    $$PWD/src/request/webrequestmanager.h \
#    $$PWD/src/request/webrequestcache.h \
#    $$PWD/src/request/stringrequest.h \
#    $$PWD/src/request/imagerequest.h \
#    $$PWD/src/request/jsonrequest.h \
#    $$PWD/src/request/variantrequest.h \
#    $$PWD/src/request/webrequest_p.h \
#    $$PWD/src/request/webrequestmanager_p.h
    $$PWD/src/shape.h \

SOURCES += \
    $$PWD/src/appcolors.cpp \
    $$PWD/src/contactsmodel.cpp \
    $$PWD/src/icons.cpp \
    $$PWD/src/swipegesturemanager.cpp \
    $$PWD/src/units.cpp \
    $$PWD/src/zoomarea.cpp \
    $$PWD/src/scalecontainer.cpp \
    $$PWD/src/kajpluginbase.cpp \
    $$PWD/src/kajqmlhelper.cpp \
    $$PWD/src/platforms.cpp \
    $$PWD/src/kajmodule.cpp \
    $$PWD/src/application.cpp \
    $$PWD/src/mobility.cpp \
    $$PWD/src/fileutils.cpp \
#    $$PWD/src/request/webrequest.cpp \
#    $$PWD/src/request/webrequestmanager.cpp \
#    $$PWD/src/request/webrequestcache.cpp \
#    $$PWD/src/request/stringrequest.cpp \
#    $$PWD/src/request/imagerequest.cpp \
#    $$PWD/src/request/jsonrequest.cpp \
#    $$PWD/src/request/variantrequest.cpp \
    $$PWD/src/shape.cpp

contains(KAJ_PLUGINS, fontawesome) {
    KAJ_ICON += fontawesome
    DEFINES += KAJ_ICON=\\\"fontawesome\\\"
    SOURCES += $$PWD/src/icons_fa.cpp
    message(KAJ_ICON set to fontawesome)
} else {
    contains(KAJ_PLUGINS, mdi) {
        KAJ_ICON += mdi
        DEFINES += "KAJ_ICON=\"mdi\""
        SOURCES += $$PWD/src/icons_mdi.cpp
        message(KAJ_ICON set to mdi)
    } else {
        KAJ_PLUGINS += fontawesome
        KAJ_ICON += fontawesome
        DEFINES += KAJ_ICON=\\\"fontawesome\\\"
        SOURCES += $$PWD/src/icons_fa.cpp
        message(KAJ_ICON set to fontawesome)
    }
}

static {
    # Create the resource file
    GENERATED_RESOURCE_FILE = $$OUT_PWD/core_gen.qrc

    INCLUDED_RESOURCE_FILES = \
        $$OTHER_FILES

    RESOURCE_CONTENT = \
        "<RCC>" \
        "<qresource prefix=\"/kaj\">"

    for(resourcefile, INCLUDED_RESOURCE_FILES) {
        resourcefileabsolutepath = $$absolute_path($$resourcefile)
        relativepath_in = $$relative_path($$resourcefileabsolutepath, $$PWD)
        relativepath_out = $$relative_path($$resourcefileabsolutepath, $$OUT_PWD)
        RESOURCE_CONTENT += "<file alias=\"$$relativepath_in\">$$relativepath_out</file>"
    }

    RESOURCE_CONTENT += \
        "</qresource>" \
        "</RCC>"

    write_file($$GENERATED_RESOURCE_FILE, RESOURCE_CONTENT)|error("Aborting.")

#    RESOURCES += $$GENERATED_RESOURCE_FILE
} else {

}

