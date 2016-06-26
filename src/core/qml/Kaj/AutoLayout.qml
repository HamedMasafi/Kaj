import QtQuick 2.3
import QtQuick.Layouts 1.1

/*!
 * This grid will automaticly be horizontal or vertical depend on width and height
 * 
 */ 
GridLayout {
    flow:  width > height ? GridLayout.LeftToRight : GridLayout.TopToBottom


}
