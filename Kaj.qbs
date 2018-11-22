import qbs
import "src/core/core.qbs" as Core
import "src/app/app.qbs" as App
import "src/game/game.qbs" as Game

Module {
    name: "Kaj"

    Depends { name: 'cpp' }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.gui" }
    Depends { name: "Qt.sql" }
    Depends { name: "Qt.quick" }
    Depends { name: "Qt.widgets" }

    cpp.includePaths: [
        "include",
        "src/core/src",
        "src/app/src",
        "src/game/src"
    ]

    property stringList qmlImportPaths: [
        "src/core/qml",
        "src/app/qml",
        "src/game/qml"
    ]

//    Export{
//        Depends { name: 'cpp' }
//        cpp.includePaths: [
//            "include",
//            "src/core/src",
//            "src/app/src",
//            "src/game/src"
//        ]
//    }

    Group {
        name: "Core"
        condition: true
        files: [
            "src/core/src/*.cpp",
            "src/core/src/*.h",
            "src/core/*.qrc"
        ]
    }

    Group {
        name: "App"
        condition: true
        files: [
            "src/app/src/*.cpp",
            "src/app/src/*.h",
            "src/app/*.qrc"
        ]
    }

    Group {
        name: "Game"
        condition: true
        files: [
            "src/game/src/*.cpp",
            "src/game/src/*.h",
            "src/game/*.qrc"
        ]
    }
}
