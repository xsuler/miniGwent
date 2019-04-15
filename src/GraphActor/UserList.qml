import QtQuick 2.0
import QtQuick.Controls 2.2

Item{

    signal close()

    property int userCount:100
    property int userHeight:50
    property color backGroundColor: "#555555"
    property var myName

    id:idListFrame
    width: parent.width/7
    height: parent.height*0.5
    x:parent.width/6
    anchors.verticalCenter: parent.verticalCenter

    function refreshAct(){
        GA.getUserOnline(1)
    }

    function returnAct(){
        close()
    }

    Connections{
        target: parent
        onMsendMyName:{
            myName=ssname
            idModel.sync()
        }
        onMshowUserList:{
            var s=idModel.count-1;
            for(var i=0;i<list.length;i++)
            {
                var flag=0;
                for(var j=0;j<idModel.count;j++)
                {
                    if(idModel.get(j).name===list[i])
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0&&list[i]!==myName)
                {
                    s++;
                    var data = {'name':list[i],'count':s}
                    idModel.append(data)
                    idModel.sync()
                }
            }
        }
    }

    Rectangle{
        id:adsasd
        anchors.fill: parent
        color: backGroundColor
        opacity: 0.3
    }

    ListView {

        anchors.fill: parent
        id: idUserList
        clip: true
        delegate: idUser
        model: idModel
        contentWidth: width
        contentHeight: userCount*userHeight
        spacing: idListFrame.height/48

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
            id:idScrollBar
            parent: idUserList.parent
            anchors.top: idUserList.top
            anchors.left: idUserList.right
            anchors.bottom: idUserList.bottom
        }
    }

    Component {
        id: idUser
        Rectangle{
            width: idUserBox.width
            height: idUserBox.height
            UserBox{
                id:idUserBox
                nameColor: "#666666"
                btnColor: "#999999"
                myName: name
                prt:idListFrame
            }
        }
    }

    SmartButton{
        id:idRefresh
        fontPixsize: height/1.5
        mytext: qsTr("Refresh List")
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
        onClicked: refreshAct()
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
        anchors.top: parent.bottom
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
