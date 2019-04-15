import QtQuick 2.0

Item {

    signal close()

    property string myName:"placeHolder"
    property color fontColor:"#ff6600"

    width: parent.width/5
    height: parent.height/5
    anchors.centerIn: parent

    Rectangle{
        anchors.fill: parent
        color: "#111111"
        opacity: 0.6
        radius: parent.width/8
    }

    Connections{
        target: parent
        onMshowConnectDialog:{
            myName=name
        }
    }

    Text {
        text: myName
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: parent.height/5
        font.pixelSize: parent.width/15
        color: fontColor
    }

    Text {
        text: "Accepted your Request"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: parent.height/5.3+2*font.pixelSize
        font.pixelSize: parent.width/15
        color: fontColor
    }

    SmartButton{
        id:idStart
        anchors.horizontalCenter: parent.horizontalCenter
        y:parent.height*0.72
        btnFontColorDef: "#bbbbbb"
        btnFontColorHov: "#00ffff"
        btnFontColorPrs: "#00aaaa"
        btnBackColorDef: "#444444"
        btnBackColorHov: "#444444"
        btnBackColorPrs: "#444444"
        border.color: btnFontColor
        border.width: height/20
        fontPixsize: height>width?height/1.5:width/4
        mytext: qsTr("Start")
        width: parent.width/5
        height: parent.height/5
        onClicked: {
            GA.startConfirm(myName)
            close()
        }
    }
}
