#include <QGuiApplication>

#include "application.h"

KAJ_BEGIN_NAMESPACE

Application::Application(QObject *parent) : QObject(parent)
{
    connect(qApp, &QGuiApplication::applicationStateChanged, this, &Application::qApp_applicationStateChanged);
}

void Application::qApp_applicationStateChanged(Qt::ApplicationState state)
{
    emit applicationStateChanged((ApplicationState)(int)state);
}

KAJ_END_NAMESPACE
