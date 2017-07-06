import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle{
    id: button
    radius: size / 2
    color: "transparent"
    border.color: Qt.rgba(230, 230, 230, 50)
    height: size
    width: size
    clip: true

    property int size: 100
    property alias backgroundColor: background.color
    property alias backgroundOpacity: background.opacity
    property string hoverColor: Qt.rgba(230, 230, 250, 50)
    property string hoverBorderColor: Qt.rgba(70, 70, 100, 50)
    property string pressedColor: 'gray'
    property string pressedBorderColor: ''
    property string text: 'Button'
    property string icon: ''
    property bool isAwesome: false
    property bool enables: true
    signal clicked()

    Rectangle{
        id: background
        radius: size / 2
        anchors.fill: parent
        border.color: Qt.rgba(230, 230, 230, 50)
        color: Qt.rgba(250, 250, 250, 50)
        opacity: .4
    }

    ColumnLayout{
        anchors.centerIn: parent

        Text {
            id: name
            text: button.icon
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: "FontAwesome"
            font.pointSize: 16
            Layout.alignment: Qt.AlignHCenter
        }
        Text {
            font.family: "B Traffic"
            text: button.text
            visible: button.text !== ""
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            Layout.alignment: Qt.AlignHCenter
        }
    }

    Item{
        id: item1
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        height: size / 2

//        Rectangle{
//            width: 20
//            height: 20
//            color: "#000000"
//            border.color: "#129b5e"
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.horizontalCenter: parent.horizontalCenter
//        }
    }
    Item{
        id: item2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        x: size / 2
        height: size / 2


    }

    states: [
        State {
            name: "hover"
            when: mouser.isInCircle() && mouser.containsMouse && !mouser.pressed
            PropertyChanges {
                target: background
                color: hoverColor
                border.color: hoverBorderColor
            }
        },
        State {
            name: "active"
            when: mouser.isInCircle() && mouser.pressed
            PropertyChanges {
                target: background
                color: pressedColor
                border.color: pressedBorderColor
            }
        }
    ]
    MouseArea{
        id: mouser

        enabled: button.enabled
        visible: button.enabled
        anchors.fill: parent
        hoverEnabled: true

        onClicked: if(isInCircle()) button.clicked()
        function isInCircle(){
            return Math.sqrt(Math.pow(mouseX - size/2, 2)
                         + Math.pow(mouseY - size/2, 2)) < size/2
        }

    }


}
