import QtQuick 2.0

Item {

    property string myName
    property string myType
    property int myStrength

    id: idCardBox

    function getColor(){
        if(myType==="King")
            return "#ffff00"
        if(myType==="Gold")
            return "#ffff00"
        if(myType==="Sliver")
            return "#eed2ee"
        if(myType==="Copper")
            return "#cd6600"
        if(myName==="null")
            return "#333333"
        return "#000000"
    }

    Rectangle{
        id:idBorder
        z:2
        height:idCardBox.height*0.96
        width: idCardBox.width*0.96
        anchors.centerIn: img
        color: getColor()
    }
    Image {
        id:img
        fillMode: Image.Stretch
        anchors.centerIn: parent
        height: parent.height*0.90
        width: parent.width*0.90
        z:6
        source: "images/cards/%1.png".arg(myName)
        Text {
            text: myStrength<=0?"":myStrength
            anchors.top: parent.top
            color: "#ffffff"
            x:0
            font.pixelSize: parent.height/4
        }
    }
}
