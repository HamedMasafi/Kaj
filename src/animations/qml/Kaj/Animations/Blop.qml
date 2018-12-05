import QtQuick 2.11

SequentialAnimation{
    loops: Animation.Infinite

    PropertyAnimation{
        target: enterButton
        to: 1.1
        property: "scale"
        duration: 500
    }
    PropertyAnimation{
        target: enterButton
        to: .9
        property: "scale"
        duration: 500
    }
}
