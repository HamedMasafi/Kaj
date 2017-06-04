import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import Kaj 1.0
import Qt.labs.settings 1.0

ApplicationWindow{
    visible: true
    title: stackView.currentItem == null ? "" : stackView.currentItem.title

    property string initialPage: ""
    property alias initialItem: stackView.initialItem

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

    Application{
        onApplicationStateChanged: {
            //            console.log(state)
        }
    }

    header: ToolBar{
        height: Units.dp(56)
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
            ToolButton{
                anchors.right: parent.right
                anchors.rightMargin: 0
//                font.pointSize: Units.sp(14)
                font.family: FontAwesome
                height: parent.height
                text: fa_ellipsis_v
                visible: stackView.currentItem == null ? false : (stackView.currentItem.menu !== null)
                onClicked: {
                    stackView.currentItem.menu.x = parent.width - stackView.currentItem.menu.width
                    stackView.currentItem.menu.open()
                }
            }
    }

    StackView{
        id: stackView
        anchors.fill: parent

        onCurrentItemChanged: if (currentItem !== null) currentItem.activated
        Keys.onBackPressed: {
            pages.back()
            return false;
        }

        Keys.onPressed: {
            if(event.key === Qt.Key_Backspace)
                pages.back()
        }
    }
}
