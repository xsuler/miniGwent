import QtQuick 2.0

Item {

    property string myName
    property string myType
    property int myStrength
    property bool isHover: false
    property bool isInChoose
    property alias myRealName:idText.text

    z:1
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
        return "#000000"
    }


    MouseArea{
        id:idArea
        anchors.fill: parent
        onClicked: {
            if(!isInChoose)
            {
                var data={'name':myName,'type':myType,'strength':myStrength}
                idModel1.append(data)
                idModel1.sync()
            }
            else
            {

            }
        }
    }

    Component.onCompleted: {
        idText.text=GA.getRealName(myName)
    }


    Text {
        id:idText
        text: GA.getRealName(myName)
        x:0
        z:3
        font.pixelSize: parent.height/18
        anchors.bottom: idBorder.top
        anchors.margins: parent.height/20
        color: "#00aaaa"
    }

    Text {
        text: {
            if(myType=="King")
                return myType
            else
                return ""
        }
        x:idText.width*1.2
        font.pixelSize: parent.height/13
        anchors.bottom: idBorder.top
        anchors.margins: parent.height/20
        color: "#00aaaa"
    }

    Text {
        text: myStrength
        anchors.bottom: idBorder.top
        color: "#ff6600"
        font.pixelSize: parent.height/13
        anchors.margins: parent.height/20
        x:parent.width-width*3
    }
    Rectangle{
        id:idBorder
        z:2
        height:idCardBox.height*0.8
        width: idCardBox.width*0.9
        anchors.centerIn: img
        color: getColor()
    }
    Image {
        id:img
        fillMode: Image.Stretch
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height*0.7
        width: parent.width*0.8
        z:3
        source: "images/cards/%1.png".arg(myName)
    }
}
