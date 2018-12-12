import QtQuick 2.0
import QtQuick.Layouts 1.1
import Kaj 1.0
ColumnLayout{
    anchors.fill: parent
    spacing: 0

    property alias header: header.data
    property alias menu: menu.data
    Rectangle{
        id: header
        Layout.fillWidth: true
        color:'red'
        height: Units.dp(400)
    }
    Rectangle{
        id: menu
        color:'blue'
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
