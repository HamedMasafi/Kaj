import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Kaj 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    function calc(){
        var n = value.value// parseInt(value.text);
        var t = type.currentText;
        var r;
        if (t === "dp") r = Units.fromDp(n)
        if (t === "sp") r = Units.sp(n)
        if (t === "mm") r = Units.mm(n)
        if (t === "in") r = Units.in(n)
        if (t === "pt") r = Units.pt(n)
        if (t === "px") r = (n)

        function p(nm, v){
            Units.virtualDpi = v;
            var t = nm + " ";
            t += "@" + Units.fromDp(r) + "dp  "
            t += "@" + (r) + "px  "
            t += "@" + Units.sp(r) + "sp  "
            t += "@" + Units.mm(r) + "mm  "
            t += "@" + Units.in(r) + "in  "
            t += "@" + Units.pt(r) + "pt  "
            output.text += t + "<br />";
        }

        output.text = "";

        p("ldpi", "120");
        p("mdpi", "160");
        p("tvdpi", "213");
        p("hdpi", "240");
        p("xhdpi", "320");
        p("xxhdpi", "480");
        p("xxxhdpi", "640");
    }

    ColumnLayout{
        Text {
            text: Units.virtualDpi
        }


        RowLayout{
            SpinBox{
                id: value
                value: 56
                onValueChanged: calc()
            }
            ComboBox{
                id: type
                model: ["px", "dp", "sp", "mm", "in", "pt"]
                currentIndex: 1
                onCurrentIndexChanged: calc()
            }
        }

        TextArea{
            id: output
            textFormat: Text.RichText

        }
    }
}
