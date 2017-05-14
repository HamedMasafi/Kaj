#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>
#include <QGuiApplication>
#include <QScreen>
#include <QtQml>
#include <QDebug>

#include <QDesktopWidget>

#include <functional>

#include "kajqmlhelper.h"
#include "kajmodule.h"

QT_BEGIN_NAMESPACE

KajQmlHelper::KajQmlHelper(QObject *parent) : QObject(parent)
{

}

void KajQmlHelper::registerQmlTypes(QQmlApplicationEngine *engine)
{

    qDebug() << "Registering Kaj ver" << KAJ_VERSION_STR;

    engine->addImportPath("qrc:/kaj/qml/");

    KajModule core;
    core.registerTypes("Kaj");

    KajPluginRegisterHelper::instance()->registerAll(engine);
}

void KajQmlHelper::registerPlugins()
{
//    KajPluginRegisterHelper::registerAll();
}

QT_END_NAMESPACE
