import QtQuick 2.0
import QtQuick.Controls 2.2
import Kaj 1.0
//import QtQuick.Controls.Material 2.0

ToolButton {
//    width: 20
//    height: 20
//    border.color: foreColor
//    radius: barSize / 3
    clip: true

    property int barSize: Units.dp(8)
    property string foreColor: 'gray'

    state: 'menu'

    Item{
        id: p
        anchors.fill: parent
//        anchors.rightMargin: Units.pt(8)
//        anchors.leftMargin: Units.pt(8)
//        anchors.bottomMargin: Units.pt(8) /** 1.5*/
//        anchors.topMargin: Units.pt(8) /** 1.5*/
        anchors.margins: Units.dp(10)

        Behavior on rotation { NumberAnimation {} }

        Rectangle{
            id: bar1
            height: barSize
            color: foreColor
            radius: barSize / 3

            transform: Rotation {
                id: bar1Rotation
                origin.y: barSize / 2
                origin.x: 0
                Behavior on angle { NumberAnimation { } }
            }

            Behavior on y { NumberAnimation {} }
            Behavior on width { NumberAnimation {} }
        }
        Rectangle{
            id: bar2
            height: barSize
            color: foreColor
            radius: barSize / 3

            Behavior on opacity { NumberAnimation {} }
        }
        Rectangle{
            id: bar3
            height: barSize
            color: foreColor
            radius: barSize / 3

            transform: Rotation {
                id: bar3Rotation
                origin.y: barSize / 2
                origin.x: 0
                //            angle: -45
                Behavior on angle { NumberAnimation { } }
            }


            Behavior on y { NumberAnimation {} }
            Behavior on width { NumberAnimation {} }
        }
    }
    states: [
        State {
            name: "menu"
            PropertyChanges {
                target: p
                rotation: 0
            }
            PropertyChanges {
                target: bar1
                width: p.width
                x: 0
                y: (p.height * .2) - (barSize / 2)
            }

            PropertyChanges {
                target: bar1Rotation
                angle: 0
            }

            PropertyChanges {
                target: bar3
                width: p.width
                x: 0
                y: (p.height * .8) - (barSize / 2)
            }

            PropertyChanges {
                target: bar3Rotation
                angle: 0
            }

            PropertyChanges {
                target: bar2
                opacity: 1
                width: p.width
                x: 0
                y: (p.height / 2) - (barSize / 2)
            }
        },
        State {
            name: "close"
            PropertyChanges {
                target: p
                rotation: 180
            }

            PropertyChanges {
                target: bar1
                width: p.width * Math.sqrt(2)
                y: -barSize / 2
            }

            PropertyChanges {
                target: bar1Rotation
                angle: 45
            }
            PropertyChanges {
                target: bar3
                width: p.width * Math.sqrt(2)
                y: parent.height - (barSize / 2)
            }

            PropertyChanges {
                target: bar3Rotation
                angle: -45
            }

            PropertyChanges {
                target: bar2
                opacity: 0
            }
        },
        State {
            name: "next"

            PropertyChanges {
                target: p
                rotation: 180
            }

            PropertyChanges {
                target: bar1
                width: (p.width / 2) * Math.sqrt(2)
                y: (p.height / 2) - (barSize / 2)
            }

            PropertyChanges {
                target: bar1Rotation
                angle: -45
                origin.y: 0
            }
            PropertyChanges {
                target: bar3
                width: (p.width / 2) * Math.sqrt(2)
                y: (p.height / 2) - (barSize / 2)
            }

            PropertyChanges {
                target: bar3Rotation
                angle: 45
                origin.y: barSize
            }

            PropertyChanges {
                target: bar2
                opacity: 1
                width: p.width
                x: 0
                y: (p.height / 2) - (barSize / 2)
            }

        },
        State {
            name: "back"

            PropertyChanges {
                target: p
                rotation: 180
            }

            PropertyChanges {
                target: bar1
                width: (p.width / 2) * Math.sqrt(2)
                x: p.width / 2
                y: -barSize / 2
            }

            PropertyChanges {
                target: bar1Rotation
                angle: 45
                origin.y: 0
            }
            PropertyChanges {
                target: bar3
                width: (p.width / 2) * Math.sqrt(2)
                x: p.width / 2
                y: p.height - (barSize / 2)
            }

            PropertyChanges {
                target: bar3Rotation
                angle: -45
                origin.y: barSize
            }

            PropertyChanges {
                target: bar2
                opacity: 1
                width: p.width
                x: 0
                y: (p.height / 2) - (barSize / 2)
            }

        }

    ]
}

