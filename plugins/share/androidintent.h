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

#ifndef QANDROIDINTENT_H
#define QANDROIDINTENT_H

#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QtAndroidExtras/QAndroidJniObject>

#define ACTION_MAIN	"android.intent.action.MAIN"
#define ACTION_VIEW	"android.intent.action.VIEW"
#define ACTION_DEFAULT  ACTION_VIEW
#define ACTION_ATTACH_DATA	"android.intent.action.ATTACH_DATA"
#define ACTION_EDIT	"android.intent.action.EDIT"
#define ACTION_INSERT_OR_EDIT	"android.intent.action.INSERT_OR_EDIT"
#define ACTION_PICK	"android.intent.action.PICK"
#define ACTION_CREATE_SHORTCUT	"android.intent.action.CREATE_SHORTCUT"
#define ACTION_CHOOSER	"android.intent.action.CHOOSER"
#define ACTION_GET_CONTENT	"android.intent.action.GET_CONTENT"
#define ACTION_DIAL	"android.intent.action.DIAL"
#define ACTION_CALL	"android.intent.action.CALL"
#define ACTION_CALL_EMERGENCY	"android.intent.action.CALL_EMERGENCY"
#define ACTION_CALL_PRIVILEGED	"android.intent.action.CALL_PRIVILEGED"
#define ACTION_SENDTO	"android.intent.action.SENDTO"
#define ACTION_SEND	"android.intent.action.SEND"
#define ACTION_SEND_MULTIPLE	"android.intent.action.SEND_MULTIPLE"
#define ACTION_ANSWER	"android.intent.action.ANSWER"
#define ACTION_INSERT	"android.intent.action.INSERT"
#define ACTION_PASTE	"android.intent.action.PASTE"
#define ACTION_DELETE	"android.intent.action.DELETE"
#define ACTION_RUN	"android.intent.action.RUN"
#define ACTION_SYNC	"android.intent.action.SYNC"
#define ACTION_PICK_ACTIVITY	"android.intent.action.PICK_ACTIVITY"
#define ACTION_SEARCH	"android.intent.action.SEARCH"
#define ACTION_SYSTEM_TUTORIAL	"android.intent.action.SYSTEM_TUTORIAL"
#define ACTION_WEB_SEARCH	"android.intent.action.WEB_SEARCH"
#define ACTION_ALL_APPS	"android.intent.action.ALL_APPS"
#define ACTION_SET_WALLPAPER	"android.intent.action.SET_WALLPAPER"
#define ACTION_BUG_REPORT	"android.intent.action.BUG_REPORT"
#define ACTION_FACTORY_TEST	"android.intent.action.FACTORY_TEST"
#define ACTION_CALL_BUTTON	"android.intent.action.CALL_BUTTON"
#define ACTION_VOICE_COMMAND	"android.intent.action.VOICE_COMMAND"
#define ACTION_SEARCH_LONG_PRESS	"android.intent.action.SEARCH_LONG_PRESS"
#define ACTION_APP_ERROR	"android.intent.action.APP_ERROR"
#define ACTION_POWER_USAGE_SUMMARY	"android.intent.action.POWER_USAGE_SUMMARY"
#define ACTION_UPGRADE_SETUP	"android.intent.action.UPGRADE_SETUP"
#define ACTION_INSTALL_PACKAGE	"android.intent.action.INSTALL_PACKAGE"
#define ACTION_UNINSTALL_PACKAGE	"android.intent.action.UNINSTALL_PACKAGE"
#define ACTION_SCREEN_OFF	"android.intent.action.SCREEN_OFF"
#define ACTION_SCREEN_ON	"android.intent.action.SCREEN_ON"
#define ACTION_USER_PRESENT	"android.intent.action.USER_PRESENT"
#define ACTION_TIME_TICK	"android.intent.action.TIME_TICK"
#define ACTION_TIME_CHANGED	"android.intent.action.TIME_SET"
#define ACTION_DATE_CHANGED	"android.intent.action.DATE_CHANGED"
#define ACTION_TIMEZONE_CHANGED	"android.intent.action.TIMEZONE_CHANGED"
#define ACTION_CLEAR_DNS_CACHE	"android.intent.action.CLEAR_DNS_CACHE"
#define ACTION_ALARM_CHANGED	"android.intent.action.ALARM_CHANGED"
#define ACTION_BOOT_COMPLETED	"android.intent.action.BOOT_COMPLETED"
#define ACTION_CLOSE_SYSTEM_DIALOGS	"android.intent.action.CLOSE_SYSTEM_DIALOGS"
#define ACTION_PACKAGE_INSTALL	"android.intent.action.PACKAGE_INSTALL"
#define ACTION_PACKAGE_ADDED	"android.intent.action.PACKAGE_ADDED"
#define ACTION_PACKAGE_REPLACED	"android.intent.action.PACKAGE_REPLACED"
#define ACTION_MY_PACKAGE_REPLACED	"android.intent.action.MY_PACKAGE_REPLACED"
#define ACTION_PACKAGE_REMOVED	"android.intent.action.PACKAGE_REMOVED"
#define ACTION_PACKAGE_CHANGED	"android.intent.action.PACKAGE_CHANGED"
#define ACTION_QUERY_PACKAGE_RESTART	"android.intent.action.QUERY_PACKAGE_RESTART"
#define ACTION_PACKAGE_RESTARTED	"android.intent.action.PACKAGE_RESTARTED"
#define ACTION_PACKAGE_DATA_CLEARED	"android.intent.action.PACKAGE_DATA_CLEARED"
#define ACTION_UID_REMOVED	"android.intent.action.UID_REMOVED"
#define ACTION_PACKAGE_FIRST_LAUNCH	"android.intent.action.PACKAGE_FIRST_LAUNCH"
#define ACTION_PACKAGE_NEEDS_VERIFICATION	"android.intent.action.PACKAGE_NEEDS_VERIFICATION"
#define ACTION_WALLPAPER_CHANGED	"android.intent.action.WALLPAPER_CHANGED"
#define ACTION_CONFIGURATION_CHANGED	"android.intent.action.CONFIGURATION_CHANGED"
#define ACTION_LOCALE_CHANGED	"android.intent.action.LOCALE_CHANGED"
#define ACTION_BATTERY_CHANGED	"android.intent.action.BATTERY_CHANGED"
#define ACTION_BATTERY_LOW	"android.intent.action.BATTERY_LOW"
#define ACTION_BATTERY_OKAY	"android.intent.action.BATTERY_OKAY"
#define ACTION_POWER_CONNECTED	"android.intent.action.ACTION_POWER_CONNECTED"
#define ACTION_SHUTDOWN	"android.intent.action.ACTION_SHUTDOWN"
#define ACTION_REQUEST_SHUTDOWN	"android.intent.action.ACTION_REQUEST_SHUTDOWN"
#define ACTION_DEVICE_STORAGE_LOW	"android.intent.action.DEVICE_STORAGE_LOW"
#define ACTION_DEVICE_STORAGE_OK	"android.intent.action.DEVICE_STORAGE_OK"
#define ACTION_DEVICE_STORAGE_FULL	"android.intent.action.DEVICE_STORAGE_FULL"
#define ACTION_DEVICE_STORAGE_NOT_FULL	"android.intent.action.DEVICE_STORAGE_NOT_FULL"
#define ACTION_MANAGE_PACKAGE_STORAGE	"android.intent.action.MANAGE_PACKAGE_STORAGE"
#define ACTION_UMS_CONNECTED	"android.intent.action.UMS_CONNECTED"
#define ACTION_UMS_DISCONNECTED	"android.intent.action.UMS_DISCONNECTED"
#define ACTION_MEDIA_REMOVED	"android.intent.action.MEDIA_REMOVED"
#define ACTION_MEDIA_UNMOUNTED	"android.intent.action.MEDIA_UNMOUNTED"
#define ACTION_MEDIA_CHECKING	"android.intent.action.MEDIA_CHECKING"
#define ACTION_MEDIA_NOFS	"android.intent.action.MEDIA_NOFS"
#define ACTION_MEDIA_MOUNTED	"android.intent.action.MEDIA_MOUNTED"
#define ACTION_MEDIA_SHARED	"android.intent.action.MEDIA_SHARED"
#define ACTION_MEDIA_UNSHARED	"android.intent.action.MEDIA_UNSHARED"
#define ACTION_MEDIA_BAD_REMOVAL	"android.intent.action.MEDIA_BAD_REMOVAL"
#define ACTION_MEDIA_UNMOUNTABLE	"android.intent.action.MEDIA_UNMOUNTABLE"
#define ACTION_MEDIA_EJECT	"android.intent.action.MEDIA_EJECT"
#define ACTION_MEDIA_SCANNER_STARTED	"android.intent.action.MEDIA_SCANNER_STARTED"
#define ACTION_MEDIA_SCANNER_FINISHED	"android.intent.action.MEDIA_SCANNER_FINISHED"
#define ACTION_MEDIA_SCANNER_SCAN_FILE	"android.intent.action.MEDIA_SCANNER_SCAN_FILE"
#define ACTION_MEDIA_BUTTON	"android.intent.action.MEDIA_BUTTON"
#define ACTION_CAMERA_BUTTON	"android.intent.action.CAMERA_BUTTON"
#define ACTION_AIRPLANE_MODE_CHANGED	"android.intent.action.AIRPLANE_MODE"

#define EXTRA_SHORTCUT_INTENT "android.intent.extra.shortcut.INTENT"
#define EXTRA_SHORTCUT_NAME "android.intent.extra.shortcut.NAME"
#define EXTRA_SHORTCUT_ICON "android.intent.extra.shortcut.ICON"
#define EXTRA_TEMPLATE "android.intent.extra.TEMPLATE"
#define EXTRA_TEXT "android.intent.extra.TEXT"
#define EXTRA_STREAM "android.intent.extra.STREAM"
#define EXTRA_EMAIL       "android.intent.extra.EMAIL"
#define EXTRA_CC       "android.intent.extra.CC"
#define EXTRA_BCC      "android.intent.extra.BCC"
#define EXTRA_SUBJECT  "android.intent.extra.SUBJECT"
#define EXTRA_INTENT "android.intent.extra.INTENT"
#define EXTRA_TITLE "android.intent.extra.TITLE"
#define EXTRA_INITIAL_INTENTS "android.intent.extra.INITIAL_INTENTS"
#define EXTRA_KEY_EVENT "android.intent.extra.KEY_EVENT"
#define EXTRA_KEY_CONFIRM "android.intent.extra.KEY_CONFIRM"
#define EXTRA_DONT_KILL_APP "android.intent.extra.DONT_KILL_APP"
#define EXTRA_PHONE_NUMBER "android.intent.extra.PHONE_NUMBER"
#define EXTRA_UID "android.intent.extra.UID"
#define EXTRA_PACKAGES "android.intent.extra.PACKAGES"
#define EXTRA_DATA_REMOVED "android.intent.extra.DATA_REMOVED"
#define EXTRA_REPLACING "android.intent.extra.REPLACING"
#define EXTRA_ALARM_COUNT "android.intent.extra.ALARM_COUNT"
#define EXTRA_DOCK_STATE "android.intent.extra.DOCK_STATE"
#define EXTRA_BUG_REPORT "android.intent.extra.BUG_REPORT"

QT_BEGIN_NAMESPACE

class AndroidIntent
{
public:
    AndroidIntent();
    explicit AndroidIntent(const QAndroidJniObject &intent);
    explicit AndroidIntent(const QString &action);
    virtual ~AndroidIntent();

    void putExtra(const QString &key, const QVariant &value);

    void setType(const QString &type);

    void putExtra(const QString &key, const int &value);
    void putExtra(const QString &key, const short &value);
    void putExtra(const QString &key, const long long &value);
    void putExtra(const QString &key, const float &value);
    void putExtra(const QString &key, const double &value);
    void putExtra(const QString &key, const char &value);
    void putExtra(const QString &key, const QChar &value);
    void putExtra(const QString &key, const QString &value);
    void putExtra(const QString &key, const QByteArray &value);

    QAndroidJniObject handle() const;

    static AndroidIntent createChooser(const AndroidIntent &intent, const QString &title);

private:
    QAndroidJniObject m_handle;
};

QT_END_NAMESPACE

#endif // QANDROIDINTENT_H
