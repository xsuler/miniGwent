import QtQuick 2.0

Item {

    property double imgOpa: 0.7
    property var userOnline: []
    property var userELO: []
    property double myRank

    id:idStartPage
    anchors.centerIn: parent
    width: parent.width/1.5
    height: parent.height/1.8

    SmartButton{

        id:idManageDeck
        anchors.right: parent.right
        btnFontColorDef: "#bbbbbb"
        btnFontColorHov: "#ff3300"
        btnFontColorPrs: "#771100"
        btnBackColorDef: "#ffffff"
        btnBackColorHov: "#00ffff"
        btnBackColorPrs: "#007777"
        fontPixsize: width/10
        mytext: qsTr("ManageDecks")
        width: parent.width/3
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        onClicked: {
            GA.getDeck()
        }

        Image {
            anchors.fill: parent
            opacity: imgOpa
            z:0
            fillMode: Image.Stretch
            source: "/images/onlineGame.jpg"
        }
    }

    SmartButton{

        id:idOnlineGame
        x:0
        btnFontColorDef: "#bbbbbb"
        btnFontColorHov: "#ff3300"
        btnFontColorPrs: "#771100"
        btnBackColorDef: "#ffffff"
        btnBackColorHov: "#00ffff"
        btnBackColorPrs: "#007777"
        fontPixsize: width/10
        mytext: qsTr("OnlineGame")
        width: parent.width/3
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        onClicked: {
            GA.getMyRank()
            GA.getUserElO()
            GA.getUserOnline(0)
        }

        Image {
            anchors.fill: parent
            opacity: imgOpa
            z:0
            fillMode: Image.Stretch
            source: "/images/onlineGame.jpg"
        }
    }
}
