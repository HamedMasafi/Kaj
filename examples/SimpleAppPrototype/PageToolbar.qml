import QtQuick 2.0
import QtQuick.Layouts 1.3
import Kaj.App 1.0
import QtQuick.Controls 2.2
import QtQml.Models 2.3

AppPage {
    title: "Toolbar"

    extraButtons: ObjectModel {
        ToolButton{
            font.family: FontAwesome
            text: fa_file
        }
        ToolButton{
            font.family: FontAwesome
            text: fa_folder_open
        }
        ToolButton{
            font.family: FontAwesome
            text: fa_save
        }
    }

}
