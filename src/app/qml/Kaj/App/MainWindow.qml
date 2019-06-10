import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import Kaj 1.0
import Qt.labs.settings 1.0
//import QtQuick.Controls.Material 2.0

ApplicationWindow{
    id: win
    visible: true
    title: stackView.currentItem === null
           ? appName
           : appName + " - " + stackView.currentItem.title

    property string initialPage: ""
    property alias initialItem: stackView.initialItem
    property bool noTitlebar: false
    property string appName: ''
    property variant direction: Qt.LeftToRight

    flags: noTitlebar ? Qt.FramelessWindowHint : Qt.Window

    function dp(n){
        return Units.dp(n)
    }

    function sp(n){
        return Units.sp(n)
    }

    onInitialPageChanged: pages.showPage(initialPage, {})

    property MainWindowPagesManager pages: MainWindowPagesManager{
        id: __pages
        stackView: stackView
    }

    Settings {
        id: __settings

//        property alias data: __pages.pagesData
    }

    header: ToolBar{
        visible: stackView.currentItem === null
                 ? false
                 : stackView.currentItem.headerVisiable

        MouseArea{
            enabled: noTitlebar
            property int lastX
            property int lastY
            anchors.fill: parent
            onPressed: {
                lastX = mouse.x
                lastY = mouse.y
            }
            onPositionChanged: {
                console.log( mouse.x - lastX)
                win.x += mouse.x - lastX
                win.y += mouse.y - lastY
            }
        }
        RowLayout{
            layoutDirection: direction
            anchors.fill: parent
            anchors.rightMargin: dp(8)
            anchors.leftMargin: dp(8)

            ToolButton{
                id: backButton
                opacity: stackView.currentItem === null
                         ? 0
                         : stackView.currentItem.allowGoBack
                           ? (stackView.depth > 1 ? 1 : 0)
                           : 0
                onClicked: pages.back()
                //            state: "back"
                //            height: parent.height
                //            width: parent.height
                font.family: FontAwesome
                text: direction == Qt.RightToLeft ? fa_arrow_right : fa_arrow_left
                visible: opacity > 0
                Behavior on opacity { NumberAnimation{} }
            }
            Label {
                id: name
                text: stackView.currentItem == null ? "" : stackView.currentItem.title
                //            font.bold: true
                x: (backButton.x + backButton.width) * backButton.opacity + 5
//                anchors.verticalCenter: parent.verticalCenter
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            RowLayout{
//                anchors.right: parent.right
//                anchors.rightMargin: 0
                layoutDirection: direction

                Repeater{
                    id: pageOptions

                    model: stackView.currentItem == null ? null : stackView.currentItem.extraButtons
                }

                ToolButton{
                    id: toolButtonMenu
                    //                font.pointSize: Units.sp(14)
                    font.family: FontAwesome
                    height: parent.height
                    text: fa_ellipsis_v
                    visible: stackView.currentItem == null ? false : (stackView.currentItem.menu !== null)
                    onClicked: showMenu();

                    function showMenu() {
                        if (direction == Qt.RightToLeft)
                            stackView.currentItem.menu.x = 0
                        else
                            stackView.currentItem.menu.x = win.width - stackView.currentItem.menu.width
                        stackView.currentItem.menu.open()
                    }

                    function hideMenu(){
                        stackView.currentItem.menu.hide()
                    }

                    function toggleMenu() {
                        if (direction == Qt.RightToLeft)
                            stackView.currentItem.menu.x = 0
                        else
                            stackView.currentItem.menu.x = win.width - stackView.currentItem.menu.width
                        stackView.currentItem.menu.visible = !stackView.currentItem.menu.visible
                    }
                }
            }
        }
    }

    StackView{
        id: stackView
        anchors.fill: parent
        //        anchors.margins: Units.dp(10)

        onCurrentItemChanged: if (currentItem !== null ) currentItem.activated()
    }

    Shortcut{
        sequence: StandardKey.Back
        onActivated: {
            if (stackView.depth > 1)
                pages.back()
        }
    }
    Shortcut{
        sequence: "F10"
        context: Shortcut.ApplicationShortcut
        onActivated: {
            if (toolButtonMenu.visible)
                toolButtonMenu.toggleMenu();
        }
    }

    Shortcut{
        sequence: "Backspace"
        context: Shortcut.ApplicationShortcut
        onActivated: {
            if (stackView.depth > 1)
                pages.back()
        }
    }
}
