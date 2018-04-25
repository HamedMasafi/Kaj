import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import Kaj 1.0
import Qt.labs.settings 1.0
//import QtQuick.Controls.Material 2.0

ApplicationWindow{
    id: win
    visible: true
    title: stackView.currentItem == null ? "" : stackView.currentItem.title

    property string initialPage: ""
    property alias initialItem: stackView.initialItem
    property bool noTitlebar
    flags: noTitlebar ? Qt.FramelessWindowHint : 0

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

        property alias data: __pages.pagesData
    }

    header: ToolBar{
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

        visible: stackView.currentItem === null
                 ? false
                 : stackView.currentItem.headerVisiable
        MenuButton{
            id: backButton
            opacity: stackView.currentItem === null
                     ? 0
                     : stackView.currentItem.allowGoBack
                       ? (stackView.depth > 1 ? 1 : 0)
                       : 0
            onClicked: pages.back()
            state: "back"
            height: parent.height
            width: parent.height
            Behavior on opacity { NumberAnimation{} }
        }
        Label {
            id: name
            text: stackView.currentItem == null ? "" : stackView.currentItem.title
            font.bold: true
            x: (backButton.x + backButton.width) * backButton.opacity + 5
            anchors.verticalCenter: parent.verticalCenter
        }

        RowLayout{
            anchors.right: parent.right
            anchors.rightMargin: 0

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
                    stackView.currentItem.menu.x = parent.width - stackView.currentItem.menu.width
                    stackView.currentItem.menu.open()
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
        onActivated: pages.back()
    }
    Shortcut{
        sequence: "F10"
        onActivated: {
            if (toolButtonMenu.visible)
                toolButtonMenu.visible = false;
            else
                toolButtonMenu.showMenu();
        }
    }

    Item {
        focus: true

        Keys.onMenuPressed: if(toolButtonMenu.visible) toolButtonMenu.showMenu()
//        Keys.onBackPressed: {
//            pages.back()
//            return false;
//        }

        Keys.onPressed: {

            if(event.key === Qt.Key_Backspace)
                pages.back()
        }
    }
}
