import QtQuick 2.0
import Kaj.App 1.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQml.Models 2.3

AppPage {
    title: "No go back from here"
    allowGoBack: false

    Pane{
        anchors.centerIn: parent
        ColumnLayout{
            Label{
                width: 300
                wrapMode: "WordWrap"
                text: "این صفحه اجازه برگشت به عقب را به کاربر نمیدهد. برای بازگشت کلید زیر را کلیک کنید"
            }
            Button{
                text: "بازگشت"
                onClicked: pages.back()
            }
        }
    }
}
