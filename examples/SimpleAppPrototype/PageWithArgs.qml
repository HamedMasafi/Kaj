import QtQuick 2.0
import QtQuick.Layouts 1.3
import Kaj.App 1.0
import QtQuick.Controls 2.2
import QtQml.Models 2.3

AppPage {
    property string param
    Label{
        anchors.centerIn: parent
        text: "مقدار " + param + " به این صفحه ارسال شده است"
    }
}
