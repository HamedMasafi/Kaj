import QtQuick 2.0
import QtQuick.Layouts 1.3
import Kaj.App 1.0
import QtQuick.Controls 2.2
import QtQml.Models 2.3

AppPage {

    Pane{
        anchors.centerIn: parent
        ColumnLayout{
            Label{
                text: "مقدار دلخواهی را در کادر زیر تایپ کنید"
            }

            TextField{
                /*
    را مقداردهی کنید result برای تنظیم مقدار برگشتی در هر صفحه فقط باید متغیر
                */
                onTextChanged: result = text
            }
        }
    }
}
