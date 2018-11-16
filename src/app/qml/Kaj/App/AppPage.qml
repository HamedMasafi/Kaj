import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQml.Models 2.2
import Kaj 1.0

PageBase {
    property bool headerVisiable: true
    property bool allowGoBack: true
    property ObjectModel extraButtons: null

    property MainWindowPagesManager pages;
    property Menu menu: null
}

