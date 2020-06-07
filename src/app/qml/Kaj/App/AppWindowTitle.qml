import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    signal clicked();
    signal titleClicked();
    signal buttonClicked();

    property alias titleText: titleLabel.text
    property alias titleFont: titleLabel.font
    property bool showBackButton: true
    property variant direction: Qt.LeftToRight
Rectangle{
    anchors.fill: parent
    color: 'red'
}
    ToolButton{
        id: backButton
        opacity: showBackButton ? 0 : 1
        onClicked: pages.back()
        font.family: FontAwesome
        text: direction == Qt.RightToLeft ? fa_arrow_right : fa_arrow_left
        anchors.verticalCenter: parent.verticalCenter
        visible: opacity > 0
        Behavior on opacity { NumberAnimation{} }
    }
    Label {
        id: titleLabel
        x: (backButton.x + backButton.width) * backButton.opacity + 5
        font.pointSize: 14
        elide: "ElideLeft"
        anchors.verticalCenter: parent.verticalCenter
    }
}
