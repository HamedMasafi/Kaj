#include "mdi.h"

#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>
#include "_mdi_functions.h"

MDI::MDI(QObject *parent) : KajPluginBase(parent)
{

}

#if QT_QML_LIB
bool MDI::init(const QQmlApplicationEngine *engine)
{
    int n = QFontDatabase::addApplicationFont(":/fonts/mdi");

    if (n == -1) {
        qDebug() << "Unable to load mdi font";
        return false;
    }

    qDebug() << QFontDatabase::applicationFontFamilies(n);

#include "_mdi_qml.h"
//#define CONTEXT_PROPERTY(name, data)   engine->rootContext()->setContextProperty("mdi_" #name , data);
//    __mdi_foreach(CONTEXT_PROPERTY)
//#undef CONTEXT_PROPERTY
    return true;
}
#endif
