import QtQuick 2.0
import QtQuick.Controls 2.2

Item {

    signal chosed(int index)

    property int cardHeight: parent.height*0.35
    property int cardWidth: cardHeight*5/7
    property int curIndex

    anchors.fill: parent

    Rectangle{
        color: "#111111"
        anchors.fill: parent
    }

    Connections{
        target: parent
        onShowSkill:{
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

        id: idSkillList
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
                if(idSkillList.indexAt(mouseX + idSkillList.contentX, mouseY + idSkillList.contentY)===-1)
                    return
                curIndex= idSkillList.indexAt(mouseX + idSkillList.contentX, mouseY + idSkillList.contentY);
                chosed(curIndex)
            }
        }

        ScrollBar.horizontal: ScrollBar {
            policy: ScrollBar.AlwaysOn
            id:idScrollBar
            parent: idSkillList.parent
            anchors.top: idSkillList.bottom
            anchors.left: idSkillList.left
            anchors.right: idSkillList.right
        }
    }

    ListModel {
        id:idModel
    }
}
