import QtQuick 2.0


//depreacted
Loader {

    QtObject{
        id: __private
        property variant pages : []
        property bool pushGuard: false
    }

    onSourceChanged: {
        if(!__private.pushGuard)
            __private.pages.push(source);
    }

    function load(page){
        __private.pushGuard = false;
        source = page
    }
    function back(){
        __private.pushGuard = true;
        __private.pages.pop();
        source = __private.pages[__private.pages.length - 1];
    }

    onLoaded: {

    }
}
