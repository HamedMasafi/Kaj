import QtQuick 2.10
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import Kaj 1.0
import Qt.labs.settings 1.0

ApplicationWindow{
    id: win

    property alias scaleSize: safeZoneElement.contentScale
    property int contentWidth: 400
    property int contentHeight: 800
    property string initialPage: ""
    property bool noTitlebar: false
    property string appName: ''
    property alias extraChilds: extraChildsContainer.children
    property alias backgroundColor: bg.color
    property alias backgroundItem: backgroundContainer.children


    property PagesStackManager pages: PagesStackManager{
        id: __pages
        loader: loader

        onLoaded: {
//            item.safeZone = win.safeZone
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

    SafeZone {
        id: safeZoneElement
        onContentScaleChanged: console.log(contentScale)
        contentSize.width: contentWidth
        contentSize.height: contentHeight
        windowSize.width: width
        windowSize.height: height
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

        transform: Scale{
            xScale: scaleContainer.xScale
            yScale: scaleContainer.yScale
        }
    }

    overlay.modeless: Rectangle {
        color: "#2f28282a"
//        scale: loader.scale

        transform: Scale{
            xScale: scaleContainer.xScale
            yScale: scaleContainer.yScale
        }
    }

    Rectangle{
        id: bg
        anchors.fill: parent
    }

    Item {
        id: scaleItem
        anchors.fill: parent

        Item{
            id: backgroundContainer

            width: contentWidth
            height: contentHeight
            children: loader.item.background

            scale: safeZoneElement.backgroundScale
            anchors.centerIn: parent
        }
        Loader{
            id: loader
            clip: true

            Keys.onBackPressed: pages.back()
            Keys.onEscapePressed: console.log("pages.back()")

            width: contentWidth
            height: contentHeight
            anchors.centerIn: parent
            scale: safeZoneElement.contentScale

            onLoaded: {
                console.log("Loaded")
                if(typeof(item.loaded) === 'function')
                    item.loaded()

                if(typeof(item.activated) === 'function')
                    item.activated()
            }
        }
        Item{
            id: extraChildsContainer

            width: contentWidth
            height: contentHeight
            scale: safeZoneElement.contentScale
            anchors.centerIn: parent
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

