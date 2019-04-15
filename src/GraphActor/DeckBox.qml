import QtQuick 2.0

Rectangle {

    property string myName
    property color nameColor
    property color btnColor
    property var prt

    width: prt.width
    height: prt.height/12
    anchors.horizontalCenter: prt.horizontalCenter
    opacity: 0.8
    color: "#111111"

    Text {
        text: myName
        font.pixelSize: parent.height/2
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.margins: parent.width/20
        color: nameColor
    }
}

