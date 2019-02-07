import QtQuick 2.10
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import Kaj 1.0
import Qt.labs.settings 1.0

ApplicationWindow{
    id: win

    property alias scaleSize: scaleContainer.xScale
    property int contentWidth: 400
    property int contentHeight: 800
    property string initialPage: ""
    property bool noTitlebar: false
    property string appName: ''
    property alias extraChilds: extraChildsContainer.children
    property alias backgroundColor: bg.color
    property rect safeZone
    property alias backgroundItem: backgroundContainer.children

    property PagesStackManager pages: PagesStackManager{
        id: __pages
        loader: loader

        onLoaded: {
            item.safeZone = win.safeZone
            console.log("safe zone is", win.safeZone)
        }

        onUnloading: {

        }
    }
    onInitialPageChanged: pages.open(initialPage)

    width: 100
    height: 62
    visible: true
    flags: noTitlebar ? Qt.FramelessWindowHint : Qt.Window

    onWidthChanged: calsSafeZone();
    onHeightChanged: calsSafeZone();
    Component.onCompleted: calsSafeZone()
//    title: stackView.currentItem === null
//           ? appName
//           : appName + " - " + stackView.currentItem.title

    function calsSafeZone(){
        var scaleX = win.width / 2
        var scaleY = win.height / 3

        if (scaleX > scaleY) {
            safeZone.width = win.width
            safeZone.height = (3 * safeZone.width) / 2
        } else {
            safeZone.height = win.height
            safeZone.width = (2 * safeZone.height) / 3
        }

        safeZone.width *= scaleContainer.scaleSize
        safeZone.height *= scaleContainer.scaleSize
        safeZone.x = (win.width - safeZone.width) / 2
        safeZone.y = (win.height - safeZone.height) / 2

        console.log("safe zone is", win.safeZone, scaleContainer.scaleSize)
    }

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

    Item {
//        id: scaleItem
        property real xScale: 1
        property real yScale: 1
        onWidthChanged: {
            xScale = win.width / win.contentWidth
            console.log("x scale", xScale)
        }
        onHeightChanged: {
            yScale = win.height / win.contentHeight
            console.log("y scale", yScale)
        }
//    }
//    ScaleContainer{
        id: scaleContainer
        anchors.fill: parent

        Item{
            id: backgroundContainer
            ScaleContainer.scaleType: "FitCrop"
            width: contentWidth
            height: contentHeight
            children: loader.item.background

            transform: Scale {
                xScale: scaleContainer.xScale
                yScale: scaleContainer.yScale
            }
        }
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

            transform: Scale {
                xScale: scaleContainer.xScale
                yScale: scaleContainer.yScale
            }
        }
        Item{
            id: extraChildsContainer
            ScaleContainer.scaleType: "FitAcceptRatio"
            width: contentWidth
            height: contentHeight

            transform: Scale {
                xScale: scaleContainer.xScale
                yScale: scaleContainer.yScale
            }
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

//    Rectangle{
//        anchors.centerIn: parent
//        height: safeZone.height
//        width: safeZone.width
//        color: 'green'
//        opacity: .4
//    }
}

