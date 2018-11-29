import QtQuick 2.10
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import Kaj 1.0
import Qt.labs.settings 1.0

ApplicationWindow{
    id: win

    property alias scaleSize: scaleContainer.scaleSize
    property int contentWidth: 400
    property int contentHeight: 800
    property string initialPage: ""
    property bool noTitlebar: false
    property string appName: ''
    property alias extraChilds: extraChildsContainer.children
    property alias backgroundColor: bg.color

    property PagesStackManager pages: PagesStackManager{
        id: __pages
        loader: loader

        onLoaded: {

        }

        onUnloading: {

        }
    }
    onInitialPageChanged: pages.open(initialPage)

    width: 100
    height: 62
    visible: true
    flags: noTitlebar ? Qt.FramelessWindowHint : Qt.Window

//    title: stackView.currentItem === null
//           ? appName
//           : appName + " - " + stackView.currentItem.title



    function open(p, props) {
        pages.open(p, props)
    }
    function close() {
        pages.close()
    }

    function dp(n){
        return Units.dp(n)
    }

    function sp(n){
        return Units.sp(n)
    }

    function em(n) {
        return n * font.pointSize;
    }

//    overlay.scale: loader.scale
    overlay.modal: Rectangle {
        color: "#8f28282a"
//        scale: loader.scale
    }

    overlay.modeless: Rectangle {
        color: "#2f28282a"
//        scale: loader.scale
    }

    Rectangle{
        id: bg
        anchors.fill: parent
    }

    ScaleContainer{
        id: scaleContainer
        anchors.fill: parent
        Loader{
            id: loader
            ScaleContainer.scaleType: "FitAcceptRatio"
            clip: true
            width: contentWidth
            height: contentHeight

            Keys.onBackPressed: pages.back()
            Keys.onEscapePressed: console.log("pages.back()")

            onLoaded: {
                if(typeof(item.loaded) === 'function')
                    item.loaded()

                if(typeof(item.activated) === 'function')
                    item.activated()
            }
        }
        Item{
            id: extraChildsContainer
            ScaleContainer.scaleType: "FitAcceptRatio"
            width: contentWidth
            height: contentHeight
        }
    }

    Shortcut{
        sequences: ["Esc", StandardKey.Back]
        onActivated: pages.back()
        context: Qt.ApplicationShortcut
    }

    onClosing: {
        if (Qt.platform.os === "android" && pages.back() !== null)
            close.accepted = false
    }
}

