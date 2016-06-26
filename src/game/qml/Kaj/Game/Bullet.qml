import QtQuick 2.0

Entity {
    id: root

    entityType: 'bullet'
    entityVariant: 'gun'

    width: 20
    height: 20

    property alias color: w.color
    Rectangle{
        id: c
        width: 20
        height: 20
        color: 'black'
        opacity: .2
        radius: 10
    }

    Rectangle{
        id: w
        width: 20
        height: 20
        color: 'black'
    }

    property int h: 30
    property var pointTranslator: function(x, y){ return Qt.point(x, y) }
    property int speed: 30

    signal reachGoal()

    function shoot(targetX, targetY){
        var _s = (1 / speed) * 100
        var _pos = pointTranslator(targetX, targetY)
        var _l = Math.sqrt(Math.pow(root.x - targetX, 2) + Math.pow(root.y - targetY, 2))
        movmenterX.duration = movmenterY.duration = (_l * _s)
        movmenterYdown.duration = (_l * _s) / 2
        movmenterYup.duration = (_l * _s) / 2

        movmenterX.to = _pos.x
        movmenterY.to = _pos.y

        movmenter.start()
    }

    ParallelAnimation{
        id: movmenter
        running: false

        onStopped: {
            remove(root)
            reachGoal()
        }

        NumberAnimation{
            id: movmenterX
            target: root
            property: "x"
        }

        NumberAnimation{
            id: movmenterY
            target: root
            property: "y"
        }

        SequentialAnimation{

            NumberAnimation{
                id: movmenterYup
                target: w
                property: "y"
                to: -root.h
                easing.type: Easing.OutSine
            }

            NumberAnimation{
                id: movmenterYdown
                target: w
                to: 0
                property: "y"
                easing.type: Easing.InSine
            }
        }
    }
}

