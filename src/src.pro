TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
    core \
    app \
    game \
    animations \
    rest

# android: SUBDIRS += android

core.depends += core
rest.depends += core network qml
app.depends += core qml quick
game.depends += core qml quick
animations.depends += core qml quick
