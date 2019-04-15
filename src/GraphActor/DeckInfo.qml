import QtQuick 2.0
import QtQuick.Controls 2.2

Item {

    property int cardWidth:width/7
    property int cardHeight:height/3.3
    property color backGroundColor: "#555555"

    id:idDeckInfo
    width: parent.width*3/7
    height: parent.height*0.5
    anchors.verticalCenter: parent.verticalCenter
    x:parent.width/8

    Connections{
        target: parent
        onMshowCardAvailable1:{
            for(var i=0;i<names.length;i++)
            {
                var data = {'name':names[i],'type':types[i],'strength':strengths[i]}
                idModel.append(data)
            }
            idModel.sync()
        }
    }

    GridView {

        width: parent.width
        height: parent.height
        y:0
        id: idCardList
        clip: true
        delegate: idCard
        model: idModel
        contentWidth: width
        cellHeight: cardHeight
        cellWidth: cardWidth

        Rectangle{
            anchors.fill: parent
            color: backGroundColor
            opacity: 0.3
        }

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
            id:idScrollBar
            parent: idCardList.parent
            anchors.top: idCardList.top
            anchors.left: idCardList.right
            anchors.bottom: idCardList.bottom

        }
    }

    Component {
        id: idCard
        Rectangle{
            CardBox{
                id:idCardBox

                width: cardWidth
                height: cardHeight
                myName: name
                myType: type
                myStrength: strength
                isInChoose: false
            }
        }
    }

    ListModel {
        id:idModel
    }
}
