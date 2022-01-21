/****************************************************************************
**
** Copyright (C) 2017 BogDan Vatra <bogdan@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "androidintent.h"

#include <QtAndroidExtras/QAndroidJniEnvironment>

QT_BEGIN_NAMESPACE

AndroidIntent::AndroidIntent() : m_handle("android.content.Intent", "()V")
{

}

AndroidIntent::AndroidIntent(const QAndroidJniObject &intent) : m_handle(intent)
{

}

AndroidIntent::AndroidIntent(const QString &action)
    : m_handle("android.content.Intent", "(Ljava/lang/String;)V",
                           QAndroidJniObject::fromString(action).object())
{

}

AndroidIntent::~AndroidIntent()
{

}

    /*
public Intent putExtra(String name, boolean value)
public Intent putExtra(String name, char value)
public Intent putExtra(String name, short value)
public Intent putExtra(String name, int value)
public Intent putExtra(String name, long value)
public Intent putExtra(String name, float value)
public Intent putExtra(String name, double value)
public Intent putExtra(String name, String value)

    public Intent putExtra(String name, byte value)
    public Intent putExtra(String name, CharSequence value)
    public Intent putExtra(String name, Parcelable value)
    public Intent putExtra(String name, Parcelable[] value)
    public Intent putExtra(String name, Serializable value)
    public Intent putExtra(String name, boolean[] value)
    public Intent putExtra(String name, byte[] value)
    public Intent putExtra(String name, short[] value)
    public Intent putExtra(String name, char[] value)
    public Intent putExtra(String name, int[] value)
    public Intent putExtra(String name, long[] value)
    public Intent putExtra(String name, float[] value)
    public Intent putExtra(String name, double[] value)
    public Intent putExtra(String name, String[] value)
    public Intent putExtra(String name, CharSequence[] value)
    public Intent putExtra(String name, Bundle value)
    public Intent putExtra(String name, IBinder value)

    jboolean    Z
    jbyte       B
    jchar       C
    jshort      S
    jint        I
    jlong       J
    jfloat      F
    jdouble     D
    */

void AndroidIntent::setType(const QString &type)
{
    QAndroidJniExceptionCleaner cleaner;
    m_handle.callObjectMethod("setType",
                            "(Ljava/lang/String;)Landroid/content/Intent;",
                            QAndroidJniObject::fromString(type).object());
}

void AndroidIntent::putExtra(const QString &key, const int &value)
{
    QAndroidJniExceptionCleaner cleaner;
    m_handle.callObjectMethod("putExtra",
                              "(Ljava/lang/String;I)Landroid/content/Intent;",
                              QAndroidJniObject::fromString(key).object(),
                              value);
}

void AndroidIntent::putExtra(const QString &key, const short &value)
{
    QAndroidJniExceptionCleaner cleaner;
    m_handle.callObjectMethod("putExtra",
                              "(Ljava/lang/String;S)Landroid/content/Intent;",
                              QAndroidJniObject::fromString(key).object(),
                              value);
}

void AndroidIntent::putExtra(const QString &key, const long long &value)
{
    QAndroidJniExceptionCleaner cleaner;
    m_handle.callObjectMethod("putExtra",
                              "(Ljava/lang/String;I)Landroid/content/Intent;",
                              QAndroidJniObject::fromString(key).object(),
                              value);
}

void AndroidIntent::putExtra(const QString &key, const float &value)
{
    QAndroidJniExceptionCleaner cleaner;
    m_handle.callObjectMethod("putExtra",
                              "(Ljava/lang/String;F)Landroid/content/Intent;",
                              QAndroidJniObject::fromString(key).object(),
                              value);
}

void AndroidIntent::putExtra(const QString &key, const double &value)
{
    QAndroidJniExceptionCleaner cleaner;
    m_handle.callObjectMethod("putExtra",
                              "(Ljava/lang/String;D)Landroid/content/Intent;",
                              QAndroidJniObject::fromString(key).object(),
                              value);
}

void AndroidIntent::putExtra(const QString &key, const char &value)
{
    QAndroidJniExceptionCleaner cleaner;
    m_handle.callObjectMethod("putExtra",
                              "(Ljava/lang/String;B)Landroid/content/Intent;",
                              QAndroidJniObject::fromString(key).object(),
                              value);
}

void AndroidIntent::putExtra(const QString &key, const QChar &value)
{
    QAndroidJniExceptionCleaner cleaner;
    m_handle.callObjectMethod("putExtra",
                              "(Ljava/lang/String;C)Landroid/content/Intent;",
                              QAndroidJniObject::fromString(key).object(),
                              value.cell());
}

void AndroidIntent::putExtra(const QString &key, const QString &value)
{
    QAndroidJniExceptionCleaner cleaner;
    m_handle.callObjectMethod("putExtra",
                              "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                              QAndroidJniObject::fromString(key).object(),
                              QAndroidJniObject::fromString(value).object());
}

void AndroidIntent::putExtra(const QString &key, const QByteArray &value)
{
    QAndroidJniExceptionCleaner cleaner;
    QAndroidJniEnvironment env;
    jbyteArray array = env->NewByteArray(value.size());
    env->SetByteArrayRegion(array, 0, value.length(), reinterpret_cast<const jbyte*>(value.constData()));
    m_handle.callMethod<void>("putExtra",
                              "(Ljava/lang/String;[B)Landroid.content.Intent;",
                              QAndroidJniObject::fromString(key).object(),
                              array);
    env->DeleteLocalRef(array);
}

QAndroidJniObject AndroidIntent::handle() const
{
    return m_handle;
}

AndroidIntent AndroidIntent::createChooser(const AndroidIntent &intent, const QString &title)
{
    QAndroidJniExceptionCleaner cleaner;
    return AndroidIntent(QAndroidJniObject::callStaticObjectMethod(
                "android/content/Intent",
                "createChooser",
                "(Landroid/content/Intent;Ljava/lang/CharSequence;)Landroid/content/Intent;",
                intent.m_handle.object(),
                QAndroidJniObject::fromString(title).object()));
}

QT_END_NAMESPACE
