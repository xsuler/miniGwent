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

    SmartButton{
        mytext: qsTr("Request")
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width/3
        height: parent.height/2
        anchors.right: parent.right
        anchors.margins: parent.width/20
        onClicked: GA.connectRequest(myName)
        color: btnColor
        btnFontColorDef: "#666666"
        btnFontColorHov: "#00ffff"
        btnFontColorPrs: "#006666"
        btnBackColorDef: "#555555"
        btnBackColorHov: "#666666"
        btnBackColorPrs: "#444444"
        fontPixsize: height/1.5
    }
}

