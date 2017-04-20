import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

ApplicationWindow{
    width: 100
    height: 62

    property int contentWidth: 400
    property int contentHeight: 800
    property var initialItem//: pages.initialItem

    signal loaded();

    QtObject{
        id: __private
        property variant pages: []
        property variant properties
    }

    Component.onCompleted: {
        scale();
//        loader.sourceComponent = initialItem
        console.log("Loading " + initialItem)
        loaded();
        openPage(initialItem, {})
    }

    function scale(){
        //children = o

        var scaleSize = Math.min(width / loader.width, height / loader.height);
        loader.x = (width - loader.width) / 2
        loader.y = (height - loader.height) / 2
        loader.scale = scaleSize;
//        var i
//        for(i = 0; i < contentItem.children.length; i++){
//            var child = contentItem.children[i];

//            var scaleSize = Math.min(width / child.width, height / child.height);
//            child.x = (width - child.width) / 2
//            child.y = (height - child.height) / 2
//            child.scale = scaleSize;
//        }
    }

    function replacePage(page, properties){
        __private.pages.pop();
        openPage(page, properties);
    }

    function openPage(page, properties){
        loader.sourceComponent = undefined;

        __private.pages.push({page: page, properties: properties})
        __private.properties = properties

        loader.source = Qt.resolvedUrl(page);
        return;

        var component = Qt.createComponent(Qt.resolvedUrl(page));
        var i;

        console.log("Loading " + page)

        var loadObject = function(){
            if (component.status === Component.Ready) {

                var item = component.createObject();

                pages.push({
                               item: item,
                               properties: properties,
                               replace: true,
                               destroyOnPop: true
                           });

            } else if (component.status === Component.Error) {
                console.log("Error loading item:", component.errorString());
            }
        }

        console.log("Status=" + component.status)
        if (component.status === Component.Ready)
            loadObject();
        else if(component.status === Component.Error)
            console.log("Error loading component:", component.errorString());
        else
            component.statusChanged.connect(loadObject);
    }

    function close(){
        pages.pop();
    }

    onWidthChanged: scale()
    onHeightChanged: scale()

//    Rectangle{
//        width: WIDTH
//        height: HEIGHT
//        border.color: "black"
//    }
//    Image {
//        source: "qrc:///images/GameBackground"
//        anchors.fill: parent
//    }
    style: ApplicationWindowStyle{
        background: BorderImage {
            source: ASSETS + "Images/SelectGame/Background.png"
            anchors.fill: parent
            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat
            border{
                top: 25
                right: 25
                bottom: 25
                left: 25
            }
        }
    }

    Loader{
        id: loader
        clip: true
        width: WIDTH
        height: HEIGHT
        onLoaded: {
            for(var key in __private.properties)
                item[key] = __private.properties[key];

            if(typeof item.loaded === 'function')
                item.loaded();
            else
                console.log("no loaded function")
        }
    }

//    StackView{
//        id: pages
//        clip: true
//        width: contentWidth
//        height: contentHeight
//    }
}

