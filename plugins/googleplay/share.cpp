#include "share.h"

#if QT_ANDROIDEXTRAS_LIB
#   include <QAndroidJniObject>
#endif

#include <QtQml>

Share::Share(QObject *parent) : KajPluginBase(parent)
{

}

void Share::shareApp()
{
#if QT_ANDROIDEXTRAS_LIB
    QAndroidJniObject::callStaticMethod<void>(KAJ_JAVA_CLASS_NAME(share, Share),
                                              "ShareApp",
                                              "()V");
#endif
}

void Share::registerQmlType()
{
    qmlRegisterType<Share>(KAJ_QML_URI, 1, 0, CLASS_NAME(Share));
}

