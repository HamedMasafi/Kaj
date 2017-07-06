import QtQuick 2.0
import QtQuick.Controls 2.0

QtObject {
    id: me
    property StackView stackView
    property var pagesData: []

    function back(){
        if(stackView.depth >= 1)
            __closePage()
        else
            Qt.quit()
    }

    function clear(){
        stackView.clear();
    }

    function gotoMainPage(){
        while(stackView.depth > 1)
            __closePage()
    }

    function replacePage(page, properties){
        __pushPage(page, properties, true);
    }

    function showPage(page, properties){
        __pushPage(page, properties, false);
    }

    function __pushPage(page, properties, replace){
        page += ".qml";

        if (properties === undefined || properties === null)
            properties = {};

        var component = Qt.createComponent(Qt.resolvedUrl(page));
        var i;

        var loadObject = function(){
            if (component.status === Component.Ready) {

                var item = component.createObject();

                properties.pages =  me;

                if (replace) {
                    stackView.replace(item, properties);
                    pagesData.pop()
                } else {
                    stackView.push(item, properties)
                }

                pagesData.push({page: item, props: properties});
                if(typeof(item.loaded) === 'function')
                    item.loaded()

                if(typeof(item.activated) === 'function')
                    item.activated()

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

    function __closePage() {
        if(stackView.depth === 0)
            return;

        var item = stackView.get(stackView.depth - 1)
        if(typeof(item.unloaded) === 'function')
            item.unloaded()
        stackView.pop()
    }
}
