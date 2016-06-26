QT += qml quick widgets

#CONFIG(debug, debug|release):{
#    QML_IMPORT_PATH = \
#        $$PWD/src/qml \
#        qrc:/kaj/qml
#}


INCLUDEPATH += $$PWD/include

DEFINES += KAJ_COMPILE_STATIC

#Function for copy to output
defineTest(tCopyToOutput){
    source = $$PWD/$$1
    target = $$OUT_PWD/$$2
    target ~= s,\\\\\\.?\\\\,\\,

    win32 {
        source = $$replace(source, /, \\)
        target = $$replace(target, /, \\)
        target ~= s,\\\\\\.?\\\\,\\,
        copyCommand += xcopy /E /I /Y \"$$source\" \"$$target\"
    } else {
        source = $$replace(source, \\\\, /)
        target = $$replace(target, \\\\, /)
        copyCommand += test -d \"$$target\" || mkdir -p \"$$target\" && cp -R \"$$source\" \"$$target\"
    }
    message(Copy \"$$source\" to \"$$target\")

    copydeploymentfolders.commands += $$copyCommand
    first.depends += $(first) copydeploymentfolders
    export(first.depends)
    export(copydeploymentfolders.commands)
    QMAKE_EXTRA_TARGETS += first copydeploymentfolders

    export (QMAKE_EXTRA_TARGETS)
}

#include($$PWD/copyData.pri)

#android.source = android-build
#android.target = ..
#COPYFOLDERS += android

!contains(KAJ_MODULES, core) {
    message(Core module is not included. It will be incude automaticaly)
    KAJ_MODULES += core
}
for(m, KAJ_MODULES){
    include($$PWD/src/$${m}/$${m}.pri)
    QML_IMPORT_PATH += $$PWD/src/$${m}/qml
}
for(m, KAJ_PLUGINS){
    include($$PWD/plugins/$${m}/$${m}.pri)
}

#copyData()
tCopyToOutput(android-build)
