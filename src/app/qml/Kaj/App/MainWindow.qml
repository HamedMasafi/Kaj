import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4 as QQC14
import QtQuick.Layouts 1.1

ApplicationWindow{
    visible: true

    property string initialPage: ""
    property alias initialItem: stackView.initialItem

    onInitialPageChanged: showPage(initialPage, {})


    function back(){
        if(stackView.depth >= 1)
            stackView.pop()
        else
            Qt.quit()
    }

    function gotoMainPage(){
        while(stackView.depth > 1)
            stackView.pop();
    }

    function showPage(page){
        showPageWithArgs(page, {})
    }

    function showPageWithArgs(page, properties){
        page += ".qml";

        if (properties === undefined || properties === null)
            properties = {};

        var component = Qt.createComponent(Qt.resolvedUrl(page));
        var i;

        var loadObject = function(){
            if (component.status === Component.Ready) {

                var item = component.createObject();

                stackView.push({
                                   item: item,
                                   properties: properties,
                                   destroyOnPop: true
                               });

                if(item.openPage !== undefined)
                    item.openPage.connect(showPage);
                if(item.openPageWithArgs !== undefined)
                    item.openPageWithArgs.connect(showPageWithArgs)

                if(item.back !== undefined)
                    item.back.connect(back);
            } else if (component.status === Component.Error) {
                console.log("Error loading item:", component.errorString());
            }
        }

        if (component.status === Component.Ready)
            loadObject();
        else if(component.status === Component.Error)
            console.log("Error loading component:", component.errorString());
        else
            component.statusChanged.connect(loadObject);
    }

    header: ToolBar{
        height: 40

        MenuButton{
            id: backButton
            opacity: stackView.depth > 1 ? 1 : 0
            onClicked: back()
            state: "back"
            Behavior on opacity { NumberAnimation{} }
        }
        Label {
            id: name
            text: stackView.currentItem == null ? "" : stackView.currentItem.title
            font.bold: true
            x: (backButton.x + backButton.width) * backButton.opacity + 5

            anchors.verticalCenter: parent.verticalCenter
        }
    }


    QQC14.StackView{
        id: stackView
        anchors.fill: parent

        Keys.onBackPressed: {
            back()
            return false;
        }

        Keys.onPressed: {
            if(event.key === Qt.Key_Backspace)
                back()
        }
    }
}


//import QtQuick 2.3
//import QtQuick.Controls 1.2
//import QtQuick.Layouts 1.1
//import Kaj 1.0

//ApplicationWindow {
//    id: applicationWindow1
//    width: 100
//    height: Units.dp(3)
//    color: "#fefefe"

//    property alias initialPage: stackView.initialItem
//    property alias currentPage: stackView.currentItem
//    property alias navigationDrawer: navigationDrawerContent.data

//    function showPage(page, params){
//        var component = Qt.createComponent(Qt.resolvedUrl(page));
//        var item = component.createObject();
//        var i;

//        //        currentPage = item
//        if(item.pushPage !== undefined)
//            item.pushPage.connect(showPage);

//        if(params !== undefined)
//            for(var key in properties){
//                item[key] =  properties[key];
//                //                console.log(key  + "=" +  properties[key])
//            }
//        //            if(properties.length !== undefined)
//        //                for(i = 0; i < properties.length; i++)
//        //                   for(var key in properties[i] )
//        //                       item[key] =  properties[i][key];

//        stackView.push(item);
//    }

//    function openNavigationDrawer(){
//        navigationDrawer.isOpen = true
//    }

//    function closeNavigationDrawer(){
//        navigationDrawer.isOpen = false
//    }

//    //    toolBar: ToolBar{
//    //        RowLayout {
//    //            anchors.fill: parent
//    //            layoutDirection: Qt.RightToLeft

//    //            MenuButton{
//    //                state: navigationDrawer.open ? "next" : "menu"

//    //                onClicked: navigationDrawer.open = !navigationDrawer.open
//    //            }

//    //            Text {
//    //                text: stackView.currentItem.title
//    //                font.family: "B Yekan"
//    //                font.pointSize: 14
//    //            }

//    //            Item { Layout.fillWidth: true }
//    //            IconButton {
//    //                text: fa_search
//    //            }
//    //            ToolButton{
//    //                text: fa_arrow_right
//    //                visible: stackView.depth > 1

//    //                onClicked: stackView.pop()
//    //            }
//    //        }

//    //    }

//    //    Rectangle{
//    //        id: header
//    //        height: 40
//    //        color: 'yellow'
//    //        anchors{
//    //            top: parent.top
//    //            topMargin: 0
//    //            left: parent.left
//    //            leftMargin: 0
//    //            right: parent.right
//    //            rightMargin: 0
//    //        }


//    //        RowLayout {
//    //                    anchors.fill: parent
//    //                    layoutDirection: Qt.RightToLeft

//    //                    MenuButton{
//    //                        state: navigationDrawer.open ? "next" : "menu"

//    //                        onClicked: navigationDrawer.open = !navigationDrawer.open
//    //                    }

//    //                    Text {
//    //                        text: stackView.currentItem.title
//    //                        font.family: "B Yekan"
//    //                        font.pointSize: 14
//    //                    }

//    //                    Item { Layout.fillWidth: true }
//    //                    IconButton {
//    //                        text: fa_search
//    //                    }
//    //                    ToolButton{
//    //                        text: fa_arrow_right
//    //                        visible: stackView.depth > 1

//    //                        onClicked: stackView.pop()
//    //                    }
//    //                }
//    //    }
//    Header{
//        id: header
////        color: 'yellow'
//        title: stackView.currentItem.title
//        height: Units.dp(100)

//        anchors{
//            top: parent.top
//            topMargin: 0
//            left: parent.left
//            leftMargin: 0
//            right: parent.right
//            rightMargin: 0
//        }

//    }

//    MouseArea{
//        anchors.fill: parent
//        visible: navigationDrawer.open
//        hoverEnabled: true
//    }

//    SwipeGestureManager{
//        anchors.fill: parent
//        anchors.topMargin: header.height


//        MouseArea{
//            //            color: 'green'
//            //            text: 'salam'
//            anchors.fill: parent
//        }
//        StackView{
//            id: stackView
//            anchors.fill: parent
//        }

//        property real firstX
//        property real secondX: -1
//        property bool navigationDrawerOpen
//        property int navigationDrawerStep
//        onPressed: {
//            console.log("pressed")
//            firstX = mouseX
//            navigationDrawerOpen = navigationDrawer.open
//            navigationDrawerStep = navigationDrawer.step
//            navigationDrawer._lastStep = navigationDrawer.step
//        }
//        onMouseXChanged: {

//            if(secondX == -1 || firstX === secondX)
//                secondX = mouseX;

////            console.log(firstX - secondX)
//            var sz = mouseX-firstX

//            var step = Math.abs(sz)
//            step = Math.max(0, step)
//            step = Math.min(100, step)

////            if(navigationDrawerOpen)
////                step = 100 - step

//            navigationDrawer.step = navigationDrawerStep + (firstX - mouseX)
//        }

//        onReleased: {
//            navigationDrawer.release()
//            secondX = -1
//        }
//    }

//    NavigationDrawer{
//        id: navigationDrawer
//        width: Units.dp(380)
//z:9
//        Rectangle{
//            id: navigationDrawerContent
//            anchors.fill: parent
//        }
//    }

//    StepMenuButton{
//        id: stepMenuButton
////        parent: parent.parent

//        width: Units.dp(50)
//        height: Units.dp(50)

//        anchors.top: parent.top
//        anchors.right: parent.right
//        anchors.topMargin: (header.height - stepMenuButton.height) / 2
//        anchors.rightMargin: (header.height - stepMenuButton.height) / 2
//        step: navigationDrawer.step
//        z: 10

//        onClicked: navigationDrawer.toggle()
//    }
//}

