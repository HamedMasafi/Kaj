import QtQuick 2.0
import QtQuick.Layouts 1.3
import Kaj 1.0
import Kaj.App 1.0
import QtQuick.Controls 2.2

AppPage {
    title: "Drawer"

    Drawer{
        id: drawer
        width: 0.45 * window.width
        height: window.height

        ColumnLayout{
            anchors {
                topMargin: dp(10)
                leftMargin: dp(10)
                fill: parent
            }

            ToolButton{
                font.family: FontAwesome
                text: fa_arrow_left
                onClicked: drawer.close()
            }

            CircleImage{
                source: "qrc:/hamed.jpg"
                width: 60
                height: 60
            }
            Label {
                text: "Hamed Masafi"
            }
            Label {
                text: '<a href="mailto:Hamed.Masafi@gmail.com">Hamed.Masafi@gmail.com</a>'
            }
            Item{
                Layout.fillHeight: true
            }
        }
    }

    Button{
        anchors.centerIn: parent
        text: "گشودن دراور"
        onClicked: drawer.open()
    }
}
