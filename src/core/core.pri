INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
RESOURCES += $$PWD/core.qrc
DEFINES += KAJ_CORE_LIB
QML_IMPORT_PATH += $$PWD/qml
QML_DESIGNER_IMPORT_PATH += $$PWD/qml/Kaj

HEADERS += \
    $$PWD/src/appcolors.h \
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
    $$PWD/src/request/webrequest.h \
    $$PWD/src/request/webrequestmanager.h \
    $$PWD/src/request/webrequestcache.h \
    $$PWD/src/request/stringrequest.h \
    $$PWD/src/request/imagerequest.h \
    $$PWD/src/request/jsonrequest.h \
    $$PWD/src/request/variantrequest.h \
    $$PWD/src/request/webrequest_p.h \
    $$PWD/src/shape.h \
    $$PWD/src/request/webrequestmanager_p.h

SOURCES += \
    $$PWD/src/appcolors.cpp \
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
    $$PWD/src/request/webrequest.cpp \
    $$PWD/src/request/webrequestmanager.cpp \
    $$PWD/src/request/webrequestcache.cpp \
    $$PWD/src/request/stringrequest.cpp \
    $$PWD/src/request/imagerequest.cpp \
    $$PWD/src/request/jsonrequest.cpp \
    $$PWD/src/request/variantrequest.cpp \
    $$PWD/src/shape.cpp

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

