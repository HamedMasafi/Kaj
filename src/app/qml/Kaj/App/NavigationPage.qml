import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Kaj 1.0

AppPage {
    id: appPage
    property list<Item> model
    property color primaryColor: 'white'

    onModelChanged: {
        var i;
        _model.clear()
        console.log("count is" , model.length)
        for (i = 0; i < model.length; i++) {
            _model.append({
                              _text: model[i].title,
                              _icon: model[i].iconSource,
                              _source: model[i].target,
                          })
        }

        if (model.length > 0)
            loader.source = model[0].target;
    }

    onLoaded: {
        topBar.currentIndex = 0;
        bottomBarRepeater.itemAt(0).down = true;
    }

    ListModel{
        id: _model
    }

    Drawer{
        id: drawer
        width: dp(320)
        height: rootWindow.height
        edge: Qt.RightEdge
        visible: false
        dragMargin: 0

        Pane {
            id: pane
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            background: Rectangle{

                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop {
                        position: 0.00;
                        color: primaryColor
                    }
                    GradientStop {
                        position: 1.00;
                        color: Qt.lighter(primaryColor)
                    }
                }
            }

            ColumnLayout{
                width: parent.width
                layoutDirection: Qt.RightToLeft
                CircleImage {
                    height: 40
                    width: 40
                }

                Label {
                    text: "ترابری"
                    color: 'white'
                    font.pointSize: sp(26)
                }
                Label {
                    text: "ترابری"
                    color: 'white'
                }
            }
        }

        ScrollView {
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                topMargin: pane.height
                rightMargin: 0
                leftMargin: 0
                bottomMargin: 0
            }
            Pane {

                ColumnLayout {
                    layoutDirection: Qt.RightToLeft
                    width: drawer.width
                    spacing: dp(8)

                    Repeater{
                        model: _model
                        RowLayout{
                            layoutDirection: Qt.RightToLeft
                            width: parent.width
                            height: 30

                            Image {
                                source: _icon
                                width: dp(40)
//                                height: dp(40)
                                fillMode: Image.Stretch
                                Layout.alignment: Qt.AlignVCenter
                                Layout.fillHeight: true
                            }
                            Label {
                                text: _text
                                horizontalAlignment: Qt.AlignRight
                                Layout.fillWidth: true
                                Layout.alignment: Qt.AlignVCenter
                            }
                        }
                    }
                }
            }
        }
    }

    TabBar {
        id: topBar
        visible: false
        LayoutMirroring.enabled: true
        width: parent.width
        Repeater{
            model: _model
            TabButton {
                text: _text
                icon.source: _icon
                display: "TextOnly"

                onClicked: loader.setSource(_source)
            }
        }
    }

    RowLayout {
        id: bottomBar
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        layoutDirection: Qt.RightToLeft

        Repeater{
            id: bottomBarRepeater
            model: _model
            TabButton {
                Layout.fillWidth: true
                Layout.preferredWidth: 10
                text: _text
                icon.source: _icon
                display: "IconOnly"
                onClicked: loader.setSource(_source)
            }
        }
    }

    Loader {
        id: loader
        anchors{
            rightMargin: dp(8)
            leftMargin: dp(8)
            bottomMargin: dp(8) + (bottomBar.visible ? bottomBar.height : 0)
            topMargin: dp(8) + (topBar.visible ? topBar.height : 0)
            fill: parent
        }
    }
}
