import QtQuick 2.0
import QtQuick.Controls 2.2

Item {

    property int cardHeight: parent.height*0.35
    property int cardWidth: cardHeight*5/7
    property int curIndex
    property int lastTime

    anchors.fill: parent

    Rectangle{
        color: "#111111"
        anchors.fill: parent
    }

    Connections{
        target: GA
        onReplaceTo:{
            idModel.remove(curIndex,1)
            var data = {'name':name,'type':type,'strength':strength}
            idModel.insert(curIndex,data)
            if(lastTime==0)
            {
                NA.replaceFinish();
            }
        }
    }

    Text {
        id: timeLast
        color: "#00ffff"
        text: "%1 times last".arg(lastTime)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: idReplaceList.top
        anchors.margins: parent.height/20
        font.pixelSize: parent.width/30
    }

    SmartButton{
        id:idOk
        fontPixsize: height/1.5
        mytext: qsTr("ok")
        btnFontColorDef: "#aaaaaa"
        btnFontColorHov: "#00ffff"
        btnFontColorPrs: "#00aaaa"
        btnBackColorDef: "#111111"
        btnBackColorHov: "#333333"
        btnBackColorPrs: "#222222"
        opacity: 0.7
        x:0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: idReplaceList.bottom
        anchors.margins: idReplaceList.height/10
        width: idReplaceList.width*0.3
        height: idReplaceList.height/6
        border.color: btnFontColor
        border.width: height/20
        onClicked:  NA.replaceFinish();
    }

    Connections{
        target: parent
        onMshowHand:{
            for(var i=0;i<names.length;i++)
            {
                var data = {'name':names[i],'type':types[i],'strength':strengths[i]}
                idModel.append(data)
            }
            idModel.sync()
        }
    }


    Component {
        id: idCard
        Item{
            width: cardWidth
            height: cardHeight
            CardBox{
                z:2
                id:idCardBox
                anchors.fill: parent
                myName: name
                myType: type
                myStrength: strength
            }
        }
    }


    ListView {

        id: idReplaceList
        clip: true
        anchors.centerIn: parent
        width: parent.width*0.8
        height: cardHeight*1.1
        delegate: idCard
        model: idModel
        spacing:height/8
        cacheBuffer: 50
        orientation:ListView.Horizontal

        MouseArea{
            z:5
            anchors.fill: parent
            onClicked: {
                if(idReplaceList.indexAt(mouseX + idReplaceList.contentX, mouseY + idReplaceList.contentY)===-1)
                    return
                curIndex= idReplaceList.indexAt(mouseX + idReplaceList.contentX, mouseY + idReplaceList.contentY);
                GA.replaceOne(curIndex)
                lastTime--;
                timeLast.text="%1 times last".arg(lastTime)
            }
        }

        ScrollBar.horizontal: ScrollBar {
            policy: ScrollBar.AlwaysOn
            id:idScrollBar
            parent: idReplaceList.parent
            anchors.top: idReplaceList.bottom
            anchors.left: idReplaceList.left
            anchors.right: idReplaceList.right
        }
    }

    ListModel {
        id:idModel
    }
}
