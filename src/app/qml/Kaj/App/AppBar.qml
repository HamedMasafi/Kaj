import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import Kaj 1.0

ToolBar {
    id: appBar
    property variant layoutDirection: Qt.LeftToRight
    property Menu menu: null
    property bool showMenu: menu != null
    property string title: ''
    property alias titleFont: titleLabel.font
    property bool showBackButton: true

    signal clicked();
    signal titleClicked();
    signal backButtonClicked();
    state: layoutDirection == Qt.RightToLeft ? 'rtl' : 'ltr'

    property ObjectModel extraButtons: null

    onExtraButtonsChanged: console.log("extra buttons")
    RowLayout {
        id: layout
        layoutDirection: direction
        anchors.fill: parent

        Item {
            Layout.preferredWidth: dp(8)
        }
        Item {
            id: titleContainer
            Layout.fillWidth: true
            Layout.fillHeight: true

            RoundButton{
//                Rectangle{
//                    anchors.fill: parent
//                    color: 'red'
//                }
                id: backButton
                opacity: showBackButton ? 1 : 0
                onClicked: appBar.backButtonClicked()
                font.family: Icons.fontName()
                flat: true
                visible: opacity > 0
                Behavior on opacity { NumberAnimation{} }
                anchors.verticalCenter: parent.verticalCenter
            }
            Label {
                id: titleLabel
                text: appBar.title
//                x: (backButton.x + backButton.width) * backButton.opacity + 5
                font.pointSize: 14
                elide: "ElideLeft"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Repeater{
            id: pageOptions

            model: extraButtons
        }

//        Switch {
//            onClicked: appBar.state =
//                       appBar.state == 'rtl'
//                            ? 'ltr'
//                            : 'rtl'
//        }

        ToolButton{
            id: toolButtonMenu
            font.family: Icons.fontName()
            height: parent.height
            text: Icons.get(Icons.Ellipsis)
            visible: appBar.showMenu
            onClicked: showMenu();

            function showMenu() {
                if (direction == Qt.RightToLeft)
                    appBar.menu.x = 0
                else
                    appBar.menu.x = win.width - appBar.menu.width
                appBar.menu.open()
            }

            function hideMenu(){
                appBar.menu.hide()
            }

            function toggleMenu() {
                if (direction == Qt.RightToLeft)
                    appBar.menu.x = 0
                else
                    appBar.menu.x = win.width - appBar.menu.width
                appBar.menu.visible = !appBar.menu.visible
            }
        }
    }

    states: [
        State {
            name: "ltr"
            PropertyChanges {
                target: layout
                layoutDirection: Qt.LeftToRight
            }
            AnchorChanges {
                target: backButton
                anchors{
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
            }
            PropertyChanges {
                target: titleLabel
                x: (backButton.x + backButton.width) * backButton.opacity + 5
            }

            PropertyChanges {
                target: backButton
                text: Icons.get(Icons.ArrowLeft)
            }
        },
        State {
            name: "rtl"
            PropertyChanges {
                target: layout
                layoutDirection: Qt.RightToLeft
            }
            AnchorChanges {
                target: backButton
                anchors{
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }
            }
            PropertyChanges {
                target: titleLabel
                x: titleContainer.width
                   - (backButton.width) * backButton.opacity
                   - titleLabel.width
                   - 5
            }

            PropertyChanges {
                target: backButton
                text: Icons.get(Icons.ArrowRight)
            }
        }
    ]
}
