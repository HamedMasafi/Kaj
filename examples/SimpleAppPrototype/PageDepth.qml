import QtQuick 2.0
import QtQuick.Layouts 1.3
import Kaj.App 1.0
import QtQuick.Controls 2.2
import QtQml.Models 2.3

AppPage {
    title: "Depth"
    property int depth: 1

    Pane{
        anchors.centerIn: parent
        ColumnLayout{
            Label{
                text: "عمق صفحه: " + depth
            }

            Button{
                text: "Open another"
                onClicked: pages.open("/PageDepth", {depth: depth + 1})
            }
        }
    }
}
