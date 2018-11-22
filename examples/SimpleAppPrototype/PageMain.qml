import QtQuick 2.0
import QtQuick.Layouts 1.3
import Kaj.App 1.0
import QtQuick.Controls 2.2
import QtQml.Models 2.3

AppPage {
    title: "Main page"

    ListModel{
        id: samples
        ListElement {
            property string page: "/PageMenu"
            property string descript: "صفحه منو"
        }
        ListElement {
            property string page: "/PageNoBack"
            property string descript: "غیر فعال کردن دکمه بازگشت"
        }

        ListElement {
            property string page: "/PageToolbar"
            property string descript: "افزودن دکمه به تولبار"
        }
        ListElement {
            property string page: "/PageDrawer"
            property string descript: "دراور"
        }
        ListElement {
            property string page: "/PageDepth"
            property string descript: "صفحات تو در تو"
        }
    }

    Pane{
        anchors.centerIn: parent
        ColumnLayout{
            Repeater{
                model: samples

                RowLayout{
                    Button{
                        text: "..."
                        onClicked: pages.open(page)
                    }
                    Label{
                        text: descript
                    }
                }
            }

            RowLayout{
                Button{
                    text: "..."
                    onClicked: pages.open("/PageWithArgs", {param: "Hi"})
                }
                Label{
                    text: "ارسال پارامتر به صفحه دوم"
                }
            }

            RowLayout{
                Button{
                    text: "..."
                    onClicked: {
                        pages.open("/PageReturnValue", function(r) {
                            returnValue.text = "مقدار دریافت شده: " + r
                        })
                    }
                }
                Label{
                    id: returnValue
                    text: "دریافت پایامتر از صفحه فراخوانی شده"
                }
            }
        }
    }
}
