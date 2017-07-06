import QtQuick 2.5
import QtQuick.Controls 2.0

Page {
    clip: true

    signal loaded
    signal unloaded
    signal activated

    property bool allowGoBack: true

    property MainWindowPagesManager pages;
    property Menu menu: null

    property bool allowGoBack: true
}

