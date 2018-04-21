import QtQuick 2.9
import QtQuick.Controls 2.2

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

    function backTo(page) {
        while(stackView.depth > 1)
            if (__closePage().page === page)
                break;
    }

    function replacePage(page, properties){
        __pushPage(page, properties, true);
    }

    function open(page, arg2, arg3, arg4) {
        var properties, callback, replace;
        for (var i = 1; i < arguments.length; i++) {
            var type = typeof(arguments[i])
            if (type === 'function') callback = arguments[i]
            if (type === 'boolean') replace = arguments[i]
            if (type === 'object') properties = arguments[i]
        }

        __pushPage(page, properties, callback, replace)
    }

    function showPage(page, properties, callback){
        __pushPage(page, properties, callback, false);
    }

    function __pushPage(page, properties, callback, replace){
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
                    stackView.push(item, properties, StackView.Immediate)
                }

                pagesData.push({
                                   item: item,
                                   page: page,
                                   props: properties,
                                   callback: callback
                               });
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
            item.unloaded();

        stackView.pop();

        var item2 = stackView.get(stackView.depth - 1)
        if(typeof(item2.activated) === 'function')
            item2.activated();

        var r = pagesData.pop();

        if(typeof(r.callback) === 'function')
            r.callback(item.result);

        return r;
    }
}
