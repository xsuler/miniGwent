import QtQuick 2.0
import QtQuick.Controls 2.2

Item{

    signal close()

    property int deckCount:100
    property int deckHeight:50
    property int showFlag : 0
    property color backGroundColor: "#555555"
    property string curDeck

    id:idDeckFrame
    width: parent.width/7
    height: parent.height*0.5
    x:parent.width*5.0/6-width
    anchors.verticalCenter: parent.verticalCenter

    function addAct(){
        GA.showEditMode(0,curDeck)
    }

    function curAct(){
        GA.recordDeck(curDeck)
        idShowCur.text=qsTr("your current deck is : %1".arg(curDeck))
    }

    function returnAct(){
        close()
    }

    Connections{
        target: parent
        onMshowDeckList:{
            if(list.length>0)
            {
                curDeck=cur
                idShowCur.text=qsTr("your current deck is : %1".arg(curDeck))
            }
            else
            {
                curDeck="no deck at all!"
                idShowCur.text=qsTr("your current deck is : %1".arg(curDeck))
            }
            for(var i=0;i<list.length;i++)
            {
                var data = {'name':list[i]}
                idModel.append(data)
                idModel.sync()
            }
        }
    }

    Rectangle{
        anchors.fill: parent
        color: backGroundColor
        opacity: 0.3
    }

    Text {
        id:idShowCur
        anchors.bottom: idAdd.top
        anchors.margins: idAdd.height/10
        font.pixelSize: idAdd.height
        color: "#ffffff"
        anchors.horizontalCenter: idAdd.horizontalCenter
    }

    ListView {

        anchors.fill: parent
        id: idDeckList
        clip: true
        delegate: idDeck
        model: idModel
        contentWidth: width
        contentHeight: deckCount*deckHeight
        spacing: idDeckFrame.height/48

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
            id:idScrollBar
            parent: idDeckList.parent
            anchors.top: idDeckList.top
            anchors.left: idDeckList.right
            anchors.bottom: idDeckList.bottom
        }

        MouseArea{
            anchors.fill: parent
            z:5
            onClicked: {
                GA.showDeckInfo(idDeckList.itemAt(mouseX,mouseY).myName)
                curDeck=idDeckList.itemAt(mouseX,mouseY).myName
                idEdit.opacity=0.7
                showFlag=1
            }
        }
    }

    Component {
        id: idDeck
        Rectangle{
            z:6
            width: idDeckBox.width
            height: idDeckBox.height
            property string myName: name
            DeckBox{
                id:idDeckBox
                nameColor: "#222222"
                btnColor: "#999999"
                myName: name
                prt:idDeckFrame
            }
        }
    }

    SmartButton{
        id:idEdit
        fontPixsize: height/1.5
        mytext: qsTr("Edit this deck")
        btnFontColorDef: "#aaaaaa"
        btnFontColorHov: "#00ffff"
        btnFontColorPrs: "#00aaaa"
        btnBackColorDef: "#111111"
        btnBackColorHov: "#333333"
        btnBackColorPrs: "#222222"
        opacity: 0
        x:0
        anchors.bottom: idShowCur.top
        width: parent.width
        height: parent.height/15
        border.color: btnFontColor
        border.width: height/20
        onClicked:{
            if(showFlag==0)
                return
            GA.showEditMode(1,curDeck)
        }
    }
    SmartButton{
        id:idAdd
        fontPixsize: height/1.5
        mytext: qsTr("Add new deck")
        btnFontColorDef: "#aaaaaa"
        btnFontColorHov: "#00ffff"
        btnFontColorPrs: "#00aaaa"
        btnBackColorDef: "#111111"
        btnBackColorHov: "#333333"
        btnBackColorPrs: "#222222"
        opacity: 0.7
        x:0
        anchors.bottom: parent.top
        width: parent.width
        height: parent.height/15
        border.color: btnFontColor
        border.width: height/20
        onClicked: addAct()
    }

    SmartButton{
        id:idCur
        fontPixsize: height/1.5
        mytext: qsTr("Choose this deck")
        btnFontColorDef: "#aaaaaa"
        btnFontColorHov: "#00ffff"
        btnFontColorPrs: "#00aaaa"
        btnBackColorDef: "#111111"
        btnBackColorHov: "#333333"
        btnBackColorPrs: "#222222"
        opacity: 0.7
        x:0
        anchors.top: parent.bottom
        width: parent.width
        height: parent.height/15
        border.color: btnFontColor
        border.width: height/20
        onClicked: curAct()
    }


    SmartButton{
        id:idReturn
        fontPixsize: height/1.5
        mytext: qsTr("Return")
        btnFontColorDef: "#aaaaaa"
        btnFontColorHov: "#00ffff"
        btnFontColorPrs: "#00aaaa"
        btnBackColorDef: "#111111"
        btnBackColorHov: "#333333"
        btnBackColorPrs: "#222222"
        opacity: 0.7
        x:0
        anchors.top: idCur.bottom
        width: parent.width
        anchors.margins: height/2
        height: parent.height/15
        border.color: btnFontColor
        border.width: height/20
        onClicked: returnAct()
    }

    ListModel {
        id:idModel
    }
}
