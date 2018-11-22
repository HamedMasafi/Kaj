import QtQuick 2.9
import QtQuick.Controls 2.2

QtObject {
    id: me
    property Loader loader
    property var __pages: []
    property var __currentPage: null
    property Item currentIrem: null

    onLoaderChanged: {
        loader.loaded.connect(function(item) {
            if (item === undefined)
                return;

            console.log("item changed: "  + typeof(item))
            if(typeof(item.loaded) === 'function')
                item.loaded()

            if(typeof(item.activated) === 'function')
                item.activated()

            currentIrem = item;
            properties.pages =  me;
        })
    }

    /*
      Open a page.
      Parameteres:
        page: address of page
        argsX: replace? properties and result callback
    */
    function open(page, arg2, arg3, arg4) {
        var properties, callback, replace;
        for (var i = 1; i < arguments.length; i++) {
            var type = typeof(arguments[i])
            if (type === 'function') callback = arguments[i]
            if (type === 'boolean') replace = arguments[i]
            if (type === 'object') properties = arguments[i]
        }

        __open(page, properties || {}, callback, replace)
    }

    function replace(p, props) {
        __open(p, props || {}, true, null);
    }
    function close() {
        if (__pages.length > 0) {
            if(typeof(loader.item.unloaded) === 'function')
                loader.item.unloaded()

            var cp = __pages.pop();
            __currentPage = cp;
            if(typeof(cp.callback) === 'function')
                cp.callback(loader.item.result);
            loader.source = cp.page;
            console.log("new page is" + cp.page)
            return cp;
        }
    }
    function clear() {
        __pages = [];
        loader.source = "";
    }

    function __open(p, properties, replace, callback) {
        p = Qt.resolvedUrl(p + ".qml")
        if(loader.item !== null && typeof(loader.item.unloaded) === 'function')
            loader.item.unloaded()

        if (!replace && __currentPage !== null)
            __pages.push(__currentPage)

        __currentPage = {
            page: p,
            props: properties,
            callback: callback
        }
        properties.pages =  me;
        loader.setSource(p, properties)
    }

    function gotoMainPage(){
        while(__pages.length > 1)
            __closePage()
    }

    function backTo(page) {
        while(__pages.length > 1)
            if (__closePage().page === page)
                break;
    }
}
