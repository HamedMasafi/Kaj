import QtQuick 2.0
import Kaj 1.0

PageBase {

    Keys.onBackPressed: console.log("back")
    Keys.onEscapePressed: console.log("Esc")

    property rect safeZone

    background: null
}
