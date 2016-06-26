import QtQuick 2.0

Rectangle {
    color: "gray"

    property alias delegateItem: content.data

    property alias contentWidth: flick.contentWidth
    property alias contentHeight: flick.contentHeight

    onDelegateItemChanged: {
        delegateItem.height = contentHeight
        delegateItem.width = contentWidth
    }

    Flickable {
        id: flick
        anchors.fill: parent
        contentWidth: 500
        contentHeight: 500
        boundsBehavior: Flickable.DragOverBounds
        rebound: Transition {}

        onContentHeightChanged: delegateItem.height = contentHeight
        onContentWidthChanged: delegateItem.width = contentWidth

        PinchArea {
            id: pinch
            width: Math.max(flick.contentWidth, flick.width)
            height: Math.max(flick.contentHeight, flick.height)

            property real initialWidth
            property real initialHeight
            onPinchStarted: {
                initialWidth = flick.contentWidth
                initialHeight = flick.contentHeight
            }

            onPinchUpdated: {
                // adjust content pos due to drag
                flick.contentX += pinch.previousCenter.x - pinch.center.x
                flick.contentY += pinch.previousCenter.y - pinch.center.y

                // resize content
                flick.resizeContent(initialWidth * pinch.scale, initialHeight * pinch.scale, pinch.center)
            }

            onPinchFinished: {
                // Move its content within bounds.
                flick.returnToBounds()
            }

            Rectangle {
                id: content
                anchors.centerIn: parent
                width: flick.contentWidth
                height: flick.contentHeight
                color: "red"

                Behavior on width { NumberAnimation {  } }
                Behavior on height { NumberAnimation {  } }
            }
            MouseArea {
                anchors.fill: parent
                onDoubleClicked: {
                    flick.contentWidth = 500
                    flick.contentHeight = 500
                }
                onWheel: {
                    var s =  wheel.angleDelta.y / 100
//                    flick.contentHeight += s
//                    flick.contentWidth += s
//                    console.log(s)

                    var center = Qt.point(wheel.x, wheel.y)
                    if(s < 1)
                        s = 1 / -s;

//                    console.log(flick.contentHeight)
                    flick.resizeContent(flick.contentWidth * s, flick.contentHeight * s, center)
//                    content.scale *= s
//                    console.log(content)
                    flick.returnToBounds()
//                    if(s < 0)
//                        s = -1/s
//                    content.scale *= s

                }
            }
        }
    }
}
