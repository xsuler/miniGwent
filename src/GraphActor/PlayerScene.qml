import QtQuick 2.9

Item{

    property int ban
    property int actice
    property int deckNum
    property alias myTableModel: myTable.myTableModel
    property int oneCardW: idRow0.height*2/7*1.01
    property bool fakeDrag:false
    property alias fkCard: idCardBox
    property var friend
    property string fkName
    property string fkType
    property int fkStrength
    property var enTable
    property int chooseCard: 0
    property var table:myTable

    id: idGameScene
    anchors.fill: parent

    Connections{
        target: GA
        onUseCard:{
            if(ban==1)
                return
            idCardBox.myName=name
            idCardBox.myType=type
            idCardBox.myStrength=strength
            fkName=name
            fkType=type
            GA.changePlaceLimit(name)
            fkStrength=strength
            idCardBox.opacity=1
            idCardBox.z=10
            fakeDrag=true
            idGameScene.parent.block=true
        }
        onEnemyDrop:{
            if(ban==1)
                if(flag==0)
                    return
            if(ban==0)
                if(flag==1)
                    return
            if(hand!==-1)
            {
                if(flag==1)
                    myTable.myTableModel.remove(hand,1)
                else
                    enTable.myTableModel.remove(hand,1)
            }
            var data
            if(row===0)
            {
                data={'name':name,'type':type,'strength':strength}
                idRow1.myModel.insert(index,data)
                idRow1.adjust()
                idRow0.adjust()
            }
            if(row===1)
            {
                data={'name':name,'type':type,'strength':strength}
                idRow3.myModel.insert(index,data)
                idRow3.adjust()
                idRow2.adjust()
            }
            if(row===2)
            {
                data={'name':name,'type':type,'strength':strength}
                idRow5.myModel.insert(index,data)
                idRow5.adjust()
                idRow4.adjust()
            }
        }
    }

    Card{
        id: idCardBox
        width: oneCardW*2
        height: idRow0.height
        y:parent.height
        x:parent.width
        opacity: 0
        z:10

        Behavior on x {
            NumberAnimation {
                duration: 200;
                easing.type: Easing.OutBack
            }
        }
        Behavior on y {
            NumberAnimation {
                duration: 200;
                easing.type: Easing.OutBack
            }
        }
    }
    MouseArea{
        id:area
        anchors.bottom: parent.bottom
        height: parent.height/2
        hoverEnabled: true
        propagateComposedEvents :true
        onPositionChanged: {
            idCardBox.x=mouseX-idCardBox.width/2
            idCardBox.y=mouseY-idCardBox.height/2
        }
    }

    PlayerTable{
        id:myTable
        z:2
    }

    PlayerRow{
        id:idRow0
        myTable:myTable
        rowNum:0
        friend:idRow1
        oneCardWidth:oneCardW
    }

    PlayerRow{
        id:idRow1
        myTable:myTable
        rowNum:1
        friend:idRow0
        oneCardWidth:oneCardW
    }
    PlayerRow{
        id:idRow2
        myTable:myTable
        rowNum:2
        friend:idRow3
        oneCardWidth:oneCardW
    }
    PlayerRow{
        id:idRow3
        myTable:myTable
        rowNum:3
        friend:idRow2
        oneCardWidth:oneCardW
    }
    PlayerRow{
        id:idRow4
        myTable:myTable
        rowNum:4
        friend:idRow5
        oneCardWidth:oneCardW
    }
    PlayerRow{
        id:idRow5
        myTable:myTable
        rowNum:5
        friend:idRow4
        oneCardWidth:oneCardW
    }
}
