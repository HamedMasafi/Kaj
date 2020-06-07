import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

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

    RowLayout{
        id: layout
        layoutDirection: direction
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ToolButton{
//                Rectangle{
//                    anchors.fill: parent
//                    color: 'red'
//                }
                id: backButton
                opacity: showBackButton ? 0 : 1
                onClicked: appBar.backButtonClicked()
                font.family: FontAwesome
                text: direction == Qt.RightToLeft ? fa_arrow_right : fa_arrow_left
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

            model: stackView.currentItem == null
                   ? null
                   : stackView.currentItem.extraButtons
        }

        Switch {
            onClicked: appBar.state =
                       appBar.state == 'rtl'
                            ? 'ltr'
                            : 'rtl'
        }

        ToolButton{
            id: toolButtonMenu
            font.family: FontAwesome
            height: parent.height
            text: fa_ellipsis_v
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
                text: fa_arrow_left
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
                x: (backButton.x - titleLabel.width) * backButton.opacity + 5
            }

            PropertyChanges {
                target: backButton
                text: fa_arrow_right
            }
        }
    ]
}
