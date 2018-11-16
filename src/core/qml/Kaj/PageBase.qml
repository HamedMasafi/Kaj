import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQml.Models 2.2

Page {
    id: page
    clip: true
    title: ""

    signal loaded
    signal unloaded
    signal activated

    property var result

    property PagesStackManager pages;

    function close(result) {
        page.result = result;
    }
}
