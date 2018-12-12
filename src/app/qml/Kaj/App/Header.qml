import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

/*!
 * @group App
 * 
 */ 
ToolBar {
    id: header
    width: 100
    height: 62

//    property alias stepMenuButton: stepMenuButton
    property alias showSearch: buttonSearch.visible
    property alias showHome: buttonHome.visible
    property alias title: title.text
    RowLayout {
        anchors.fill: parent
        layoutDirection: Qt.RightToLeft

//        StepMenuButton{
//            id: stepMenuButton
////            parent: header.parent

//            state: navigationDrawer.open ? "next" : "menu"

//            onClicked: navigationDrawer.open = !navigationDrawer.open
//            z: 20

//            Layout.fillHeight: true
//            width: parent.height
//        }

        Item { width: Units.dp(75) }

        Text {
            id: title
            font.family: "B Yekan"
            font.pointSize: 14
        }

        Item { Layout.fillWidth: true }
        IconButton {
            id: buttonHome
            text: fa_home
            Layout.fillHeight: true
            width: parent.height
        }
        IconButton {
            id: buttonSearch
            text: fa_search
            Layout.fillHeight: true
            width: parent.height
            onClicked: header.state = 'search'
        }
    }
    Rectangle{
        id: searchBox
        color: "green"
        height: parent.height
        clip: true
        x: 50

        RowLayout {
            anchors.fill: parent
            layoutDirection: Qt.RightToLeft

            TextField{
            Layout.fillWidth: true
                IconButton {
                    text: fa_remove
                    onClicked: header.state = ''
                    height: parent.height
                    width: parent.height
                }
            }

        }
        Behavior on x { SmoothedAnimation { duration: 100 } }
        Behavior on width { SmoothedAnimation { duration: 100 } }
    }

    states: [
        State {
            name: "search"
            PropertyChanges {
                target: searchBox
                x: 0
                width: header.width

            }
        }
    ]
}

