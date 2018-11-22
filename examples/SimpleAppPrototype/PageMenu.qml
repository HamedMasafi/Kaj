import QtQuick 2.0
import Kaj.App 1.0
import QtQuick.Controls 2.2
import QtQml.Models 2.3

AppPage {
    title: "منو"

    menu: Menu{
        MenuItem{
            text: "گزینه شماره یک"
        }
        MenuItem{
            text: "گزینه شماره دو"
        }
        MenuSeparator{}
        MenuItem{
            text: "یک گزینه دیگر"
        }
    }

    Label {
        anchors.centerIn: parent
        width: 300
        wrapMode: "WordWrap"
        text: "این صفحه منوی جداگانه دارد. با ورود به این صفحه آیتم‌های تولبار که متعلق به صفحه قبل"
        + " بودید ناپدید می‌شوند. برای برگشت به صفحه قبلی می‌توانید از فلش رو به عقب در بالای پنجره"
        + " استفاده کنید"
    }
}
