/*
    Copyright (c) 2014 Cutehacks A/S

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


    About:

    This is a Qt Quick implementation of the Android Navigation drawer
    Questions, suggestions or requests can be directed to jens@cutehacks.com

    www.cutehacks.com
*/


import QtQuick 2.3
import Tooj 1.0

Item {
    id: panel
    default property alias data: contentItem.data

    property int step: 0
    property int _lastStep: -1

    property bool open: step === 100

    property int position: Qt.RightEdge

    function _findRootItem() {
        var p = panel;
        while (p.parent != null){
            p = p.parent;
            console.log("p=" + p)
        }
        return p;
    }

    property Item _rootItem: _findRootItem()

    function toggle(){
        releaseAnimation.to = (navigationDrawer.step === 100) ? 0 : 100
        releaseAnimation.start()
    }

    function release(){
        if(step === 0 || step === 100)
            return;

        if(_lastStep === -1){
            if(step > 50)
                releaseAnimation.to = 100
            else
                releaseAnimation.to = 0
        }else{
            if(step - _lastStep < 0)
                releaseAnimation.to = 0
            else
                releaseAnimation.to = 100
        }

        releaseAnimation.start()
    }

z:10
    onStepChanged: {
        var s = step;///Math.abs(step)

        s = Math.max(s, 0);
        s = Math.min(s, 100);

//        _lastStep = panel.step
        if(s !== step){
            panel.step = s;
        }
    }

    NumberAnimation {
        id: releaseAnimation
        target: panel
        property: "step"
        duration: 200
        easing.type: Easing.InOutQuad
        to: 0
    }


    Rectangle{
        parent: panel.parent;// _rootItem
        anchors.fill: parent
        color: 'black'
        opacity:  .3 * (step / 100)
        z: 1
    }

    height: _rootItem.height
    x: _rootItem.width - (step/100) * width
    y: panel.y
    clip: true

    Rectangle {
        id: contentItem
//        parent: _rootItem
        anchors{
            fill: parent
            leftMargin: shadow.width
        }

//        z: 5//open ? 5 : 0
        clip: true
    }

    Item {
        id: shadow
//        parent: _rootItem
        anchors
        {
            left: parent.left
            bottom: parent.bottom
            top: parent.top
            leftMargin: 0
            bottomMargin: 0
            topMargin: 0
        }
       width: Units.dp(5)
//z: 6
        Rectangle {
            height: parent.width
            width: parent.height
            anchors.centerIn: parent
            rotation: -90
            opacity: Math.min(1, step / 100)
            transformOrigin: Item.Center
            gradient: Gradient{
                GradientStop { position: false ? 1 : 0 ; color: "transparent"}
                GradientStop { position: false ? 0 : 1 ; color: "#2c000000"}
            }
//            color: 'green'
        }
    }
}
