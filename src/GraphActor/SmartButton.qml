import QtQuick 2.0

Rectangle{
    signal clicked()
    signal entered()
    signal exited()

    property string mytext
    property int fontPixsize
    property color btnFontColorDef
    property color btnFontColorHov
    property color btnFontColorPrs
    property color btnBackColorDef
    property color btnBackColorHov
    property color btnBackColorPrs

    property bool isPress: idMouseArea.pressed
    property bool isHover: idMouseArea.containsMouse
    property int textWidth: smartText.width
    property alias btnFontColor: smartText.color

    color: isHover?(isPress?btnBackColorPrs:btnBackColorHov):btnBackColorDef

    Text {
        font.pixelSize: fontPixsize
        id:smartText
        z:1
        text: mytext
        color: isHover?(isPress?btnFontColorPrs:btnFontColorHov):btnFontColorDef
        anchors.centerIn: parent
    }
    MouseArea{
        id:idMouseArea
        anchors.fill: parent
        hoverEnabled:true
        onClicked: {
            parent.clicked()
        }
        onEntered: {
            parent.entered()
        }
        onExited: {
            parent.exited()
        }
    }
}
