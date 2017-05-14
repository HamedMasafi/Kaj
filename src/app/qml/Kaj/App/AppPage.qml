import QtQuick 2.5
import QtQuick.Controls 2.0

Page {
    clip: true

    signal loaded
    signal unloaded

    property MainWindowPagesManager pages;
    property Menu menu: null
}

