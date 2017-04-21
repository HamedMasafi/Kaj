TEMPLATE = lib
QT += core qml quick quickcontrols2 gui widgets
android: {
    QT += androidextras
}
TARGET = kaj
DESTDIR = qml/Kaj

include(core.pri)

QML_FILES.files = $$OTHER_FILES
QML_FILES.path = $$OUT_PWD/qml/Kaj
INSTALLS += QML_FILES
