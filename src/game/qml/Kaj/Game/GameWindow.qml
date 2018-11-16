import QtQuick 2.7
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

    property PagesStackManager pages: PagesStackManager{
        id: __pages
        loader: loader
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

//    overlay.scale: loader.scale
    overlay.modal: Rectangle {
        color: "#8f28282a"
//        scale: loader.scale
    }

    overlay.modeless: Rectangle {
        color: "#2f28282a"
//        scale: loader.scale
    }

    ScaleContainer{
        id: scaleContainer
        anchors.fill: parent
        Loader{
            id: loader
            clip: true
            width: contentWidth
            height: contentHeight

            onLoaded: {
                if(typeof(item.loaded) === 'function')
                    item.loaded()

                if(typeof(item.activated) === 'function')
                    item.activated()
            }
        }
        Loader{
            id: extraChildsContainer
            width: contentWidth
            height: contentHeight
        }
    }
}

