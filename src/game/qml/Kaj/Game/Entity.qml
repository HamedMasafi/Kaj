import QtQuick 2.0
import Kaj 1.0
Item {
    id: entity

    property string id
    property string entityType
    property string entityVariant

    property EntityManager manager

    property int speed: 10
    property int direction: 0



    signal remove(var Item)

    signal reachedNode(int x, int y)
    signal reachedGoal()

}

