import QtQuick 2.0


Rectangle
{

    property var myTable
    property int rowNum
    property var friend
    property var myView:idRow
    property var myModel: idSoldiers
    property int oneCardWidth
    property int isOk: 0
    property int limit: 0
    property int ban:parent.ban
    property int curIndex:0
    property int fakeCurIndex:0
    property int hasShadow:0
    property int chooseRow:0
    property int chooseCard:0
    property int insertFlag: 0
    property alias cardCount: idSoldiers.count
    property color bgColor: "#000000"

    id:idRowFrame
    height: parent.height*0.1
    color: bgColor
    width: parent.width*0.25+oneCardWidth
    anchors.margins: parent.width*0.25
    y:parent.height/2+parent.height*0.01+Math.floor(rowNum/2)*(height+parent.height*0.01)
    Component.onCompleted: {
        if(rowNum%2==1)
            anchors.right=parent.right
        else
            anchors.left=parent.left
    }

    function realIndexAt(index){
        if(rowNum%2==1)
        {
            return index+friend.cardCount
        }
        else
            return cardCount-1-index
    }

    function myIndexAt(index){
        if(rowNum%2==1)
            return index-friend.cardCount
        else
            return cardCount-1-index
    }

    function adjust(){
        idRow.parent.width=idRow.parent.parent.width*0.25+(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
        friend.width=idRow.parent.parent.width*0.25-(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
    }

    // connection with NAt
    Rectangle{
        id:weather
        anchors.fill: parent
        color: bgColor
        opacity: 0.3
    }

    Connections{
        target: GA
        onPlaceLimit:{
            if(ban===0)
            {
                limit=me[Math.floor(rowNum/2)]
            }
            else
            {
                limit=en[Math.floor(rowNum/2)]
            }
        }

        onInsertCard:{
            if(flag===0)
                if(ban===1)
                    return
            if(flag===1)
                if(ban===0)
                    return
            if(insertFlag==1)
            {
                insertFlag=0
                return
            }
            if(insertFlag==0||insertFlag==2)
            {
                for(var i=0;i<rows.length;i++)
                {
                    if(rows[i]===Math.floor(rowNum/2))
                    {
                        if(myIndexAt(indexs[i])<0)
                        {
                            friend.insertFlag=2
                            return
                        }

                        var data={'name':names[i],'type':types[i],'strength':strengths[i]}
                        if(parent.chooseCard===1)
                            chooseCard=1
                        if(rowNum%2==1)
                            idSoldiers.insert(myIndexAt(indexs[i]),data)
                        else
                            idSoldiers.insert(myIndexAt(indexs[i])+1,data)
                        adjust()
                    }
                }
                if(insertFlag!=2)
                    friend.insertFlag=1
                insertFlag=0
            }
        }
    }

    //remember to close block if you are handling finish obj
    Connections{
        target: NA
        onFinishChooseRow:{
            idRowFrame.chooseRow=0
        }
        onFinishChooseCard:{
            idRowFrame.chooseCard=0
            parent.chooseCard=0
        }
        onClearWeather:{
            if(flag===0)
            {
                if(ban===0)
                {
                    weather.color=bgColor
                }
            }
            if(flag===1)
            {
                if(ban===1)
                {
                    weather.color=bgColor
                }
            }
        }
        onShowWeather:{
            chooseRow=0
            if(flag===0)
                if(ban===1)
                    return
            if(flag===1)
                if(ban===0)
                    return
            if(index!=Math.floor(rowNum/2))
                return
            if(name==="frost")
                weather.color="#00ffff"
            if(name==="fog")
                weather.color="#008800"
            if(name==="rain")
                weather.color="#ffff00"
        }
        onShowShield:{
            if(flag===0)
                if(ban===1)
                    return
            if(flag===1)
                if(ban===0)
                    return
            for(var i=0;i<rows.length;i++)
            {
                if(rows[i]===Math.floor(rowNum/2))
                {
                    idRow.currentIndex=myIndexAt(indexs[i])
                    idRow.currentItem.shield()
                    idRow.currentIndex=myIndexAt(index)
                    idRow.currentItem.start()
                }
            }
       }


        onUpdateStrength:{
            if(flag===0)
                if(ban===1)
                    return
            if(flag===1)
                if(ban===0)
                    return
            if(row===Math.floor(rowNum/2))
            {
                idSoldiers.setProperty(myIndexAt(index),"strength",strength)
                idSoldiers.sync()
                idRow.currentIndex=myIndexAt(index)
                idRow.currentItem.start()
            }
        }
        onUpdateArmor:{
            if(flag===0)
                if(ban===1)
                    return
            if(flag===1)
                if(ban===0)
                    return
            if(row===Math.floor(rowNum/2))
            {
                idRow.currentIndex=myIndexAt(index)
                idRow.currentItem.showArmor(armor)
                idRow.currentItem.start()
            }
        }
        onEraseShield:{
            if(flag===0)
                if(ban===1)
                    return
            if(flag===1)
                if(ban===0)
                    return
            if(row===Math.floor(rowNum/2))
            {
                idRow.currentIndex=myIndexAt(index)
                idRow.currentItem.unShield()
                idRow.currentIndex=myIndexAt(index)
                idRow.currentItem.start()
            }
        }


        onDestroyCard:{
            if(ban===1)
                return
            for(var i=0;i<rows.length;i++)
            {
                if(rows[i]===Math.floor(rowNum/2))
                {
                    idSoldiers.remove(myIndexAt(indexs[i]))
                    adjust()
                }
            }
        }
        onEnemyDestroyCard:{
            if(ban===0)
                return
            for(var i=0;i<rows.length;i++)
            {
                if(rows[i]===Math.floor(rowNum/2))
                {
                    idSoldiers.remove(myIndexAt(indexs[i]))
                    adjust()
                }
            }
        }

        onChooseOneOfEnemyRow:{
            if(ban===0)
                return
            idRowFrame.chooseRow=1
        }
        onChooseOneOfCard:{
            if(flag==0&&ban==1)
                return
            if(flag==1&&ban==0)
                return
            idRowFrame.chooseCard=1
            friend.chooseCard=1
            parent.chooseCard=1
        }
    }
    //remember to add block in GamePage



    ListView {

        id: idRow
        anchors.fill: parent
        model: idSoldiers
        delegate: idSoldier
        interactive: false
        orientation: ListView.Horizontal
        layoutDirection: parent.rowNum%2===1?Qt.LeftToRight:Qt.RightToLeft

        MouseArea{
            id:rowMouseArea
            anchors.fill: parent
            hoverEnabled: true
            property int ccflag: 0
            property alias chooseRow : idRowFrame.chooseRow
            onClicked: {
                console.log("click")
                if(chooseCard==1)
                {   
                    if(ccflag==1)
                    {
                        NA.chooseOneCard(Math.floor(rowNum/2),realIndexAt(fakeCurIndex))
                        idRow.currentItem.unHovered()
                        ccflag=0
                    }
                }

                if(chooseRow==1)
                {
                    console.log("true")
                    idRowFrame.chooseRow=0
                    idRowFrame.color=bgColor
                    friend.color=bgColor
                    NA.chooseEnemyRow(Math.floor(rowNum/2))
                }
                if(!idRowFrame.parent.fakeDrag)
                    return
                if(limit===1)
                    return
                var data = {'name':idRow.parent.parent.fkName,'type':idRow.parent.parent.fkType,'strength':idRow.parent.parent.fkStrength}
                if(hasShadow==0)
                    return
                if(hasShadow==1)
                {
                    idSoldiers.remove(fakeCurIndex)
                    hasShadow=0
                }
                idSoldiers.insert(fakeCurIndex,data)
                idRow.parent.parent.fakeDrag=false
                NA.dropCard(-1,realIndexAt(fakeCurIndex),Math.floor(rowNum/2))
                idRow.parent.width=idRow.parent.parent.width*0.25+(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                friend.width=idRow.parent.parent.width*0.25-(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                fakeCurIndex=-1
                idRowFrame.parent.fkCard.opacity=0
                idRowFrame.parent.fkCard.z=0
                idRowFrame.parent.fakeDrag=false
                idRowFrame.parent.parent.block=false
                if(isOk==0)
                {
                    friend.width=friend.parent.width*0.25-friend.oneCardWidth
                    friend.isOk=1
                    isOk=1
                }
            }
            onEntered: {
                if(chooseRow==1)
                {
                    idRowFrame.color="#004444"
                    friend.color="#004444"
                }
                if(limit===1)
                    return
                if(!idRow.parent.parent.fakeDrag)
                    return
                if(idSoldiers.count>=1)
                {
                    if(idRow.indexAt(mouseX+idRow.contentX,mouseY+idRow.contentY)===-1)
                        fakeCurIndex=idSoldiers.count
                    else
                        fakeCurIndex=idRow.indexAt(mouseX+idRow.contentX,mouseY+idRow.contentY)
                }
                else
                    fakeCurIndex=0
                var data={'name':'null','type':'null','strength':0}
                if(hasShadow==0)
                {
                    idSoldiers.insert(fakeCurIndex,data)
                    hasShadow=1
                }
                idRow.parent.width=idRow.parent.parent.width*0.25+(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                friend.width=idRow.parent.parent.width*0.25-(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
            }
            onExited: {
                if(chooseCard==1)
                {
                    idRow.currentItem.unHovered()
                    ccflag=0
                }
                if(chooseRow==1)
                {
                    idRowFrame.color=bgColor
                    friend.color=bgColor
                }
                if(limit===1)
                    return
                if(!idRow.parent.parent.fakeDrag)
                    return
                if(hasShadow==1)
                {
                    idSoldiers.remove(fakeCurIndex)
                    hasShadow=0
                }
                idRow.parent.width=idRow.parent.parent.width*0.25+(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                friend.width=idRow.parent.parent.width*0.25-(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                fakeCurIndex=idSoldiers.count
            }
            onPositionChanged: {
                if(chooseCard==1)
                {
                    if(idRow.indexAt(mouseX+idRow.contentX,mouseY+idRow.contentY)!==-1)
                    {
                        idRow.currentItem.unHovered()
                        fakeCurIndex=idRow.indexAt(mouseX+idRow.contentX,mouseY+idRow.contentY)
                        idRow.currentIndex=fakeCurIndex
                        idRow.currentItem.hovered()
                        ccflag=1
                    }
                    else
                    {
                        idRow.currentItem.unHovered()
                        ccflag=0
                    }
                }
                if(ban===0)
                {
                    idRowFrame.parent.fkCard.x=idRowFrame.x+mouseX-idRowFrame.parent.fkCard.width/2
                    idRowFrame.parent.fkCard.y=idRowFrame.y+mouseY-idRowFrame.parent.fkCard.height/2
                }
                else
                {
                    idRowFrame.parent.friend.fkCard.x=idRowFrame.x+mouseX-idRowFrame.parent.friend.fkCard.width/2
                    idRowFrame.parent.friend.fkCard.y=idRowFrame.y+mouseY-idRowFrame.parent.friend.fkCard.height/2
                }
                if(limit===1)
                {
                    return
                }
                if(!idRow.parent.parent.fakeDrag)
                    return
                if(idSoldiers.count>1&&fakeCurIndex!==idRow.indexAt(mouseX+idRow.contentX,mouseY+idRow.contentY))
                {
                    if(hasShadow==1)
                    {
                        idSoldiers.remove(fakeCurIndex)
                        hasShadow=0
                    }
                    if(idRow.indexAt(mouseX+idRow.contentX,mouseY+idRow.contentY)===-1)
                        fakeCurIndex=idSoldiers.count
                    else
                        fakeCurIndex=idRow.indexAt(mouseX+idRow.contentX,mouseY+idRow.contentY)
                    var data={'name':'null','type':'null','strength':0}
                    if(hasShadow==0)
                    {
                        idSoldiers.insert(fakeCurIndex,data)
                        hasShadow=1
                    }
                    idRow.parent.width=idRow.parent.parent.width*0.25+(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                    friend.width=idRow.parent.parent.width*0.25-(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                }
            }
        }

        DropArea
        {
            id: dropArea
            anchors.fill: parent
            onDropped:
            {
                 console.log("0")
                if(limit===1)
                    return
                 console.log("1")
                var idx
                if(rowNum%2==1)
                    idx=curIndex+friend.cardCount
                else
                    idx=cardCount-1-curIndex
                var data
                if(ban==0)
                {
                     console.log("2")
                    NA.dropCard(myTable.myTableView.curDragIndex,idx,Math.floor(rowNum/2))
                    data = {'name':myTable.myTableModel.get(myTable.myTableView.curDragIndex).name,'type':myTable.myTableModel.get(myTable.myTableView.curDragIndex).type,'strength':myTable.myTableModel.get(myTable.myTableView.curDragIndex).strength}
                }
                else
                {
                    console.log("en")
                    NA.dropCard(idRowFrame.parent.enTable.myTableView.curDragIndex,idx,Math.floor(rowNum/2))
                    data = {'name':idRowFrame.parent.enTable.myTableModel.get(idRowFrame.parent.enTable.myTableView.curDragIndex).name,'type':idRowFrame.parent.enTable.myTableModel.get(idRowFrame.parent.enTable.myTableView.curDragIndex).type,'strength':idRowFrame.parent.enTable.myTableModel.get(idRowFrame.parent.enTable.myTableView.curDragIndex).strength}
                }

                console.log("3")
                if(hasShadow==1)
                {
                    idSoldiers.remove(curIndex)
                    hasShadow=0
                }
                 console.log("4")
                idSoldiers.insert(curIndex,data)
                idRow.parent.width=idRow.parent.parent.width*0.25+(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                friend.width=idRow.parent.parent.width*0.25-(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                curIndex=-1
                if(ban===0)
                {
                    myTable.myTableModel.remove(myTable.myTableView.curDragIndex)
                }
                else
                {
                    console.log("en")
                    idRowFrame.parent.enTable.myTableModel.remove(idRowFrame.parent.enTable.myTableView.curDragIndex)
                }
                if(isOk==0)
                {
                    friend.width=friend.parent.width*0.25-friend.oneCardWidth
                    friend.isOk=1
                    isOk=1
                }
            }
            onPositionChanged:{
                if(limit===1)
                    return
                if(idSoldiers.count>1&&curIndex!==idRow.indexAt(drag.x+idRow.contentX,drag.y+idRow.contentY))
                {
                    if(hasShadow==1)
                    {
                        idSoldiers.remove(curIndex)
                        hasShadow=0
                    }
                    if(idRow.indexAt(drag.x+idRow.contentX,drag.y+idRow.contentY)===-1)
                        curIndex=idSoldiers.count
                    else
                        curIndex=idRow.indexAt(drag.x+idRow.contentX,drag.y+idRow.contentY)
                    var data={'name':'null','type':'null','strength':0}
                    if(hasShadow==0)
                    {
                        idSoldiers.insert(curIndex,data)
                        hasShadow=1
                    }
                    idRow.parent.width=idRow.parent.parent.width*0.25+(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                    friend.width=idRow.parent.parent.width*0.25-(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                }
            }
            onEntered: {
                if(limit===1)
                    return
                if(idSoldiers.count>=1)
                {
                    if(idRow.indexAt(drag.x+idRow.contentX,drag.y+idRow.contentY)===-1)
                        curIndex=idSoldiers.count
                    else
                        curIndex=idRow.indexAt(drag.x+idRow.contentX,drag.y+idRow.contentY)
                }
                else
                    curIndex=0
                var data={'name':'null','type':'null','strength':0}
                if(hasShadow==0)
                {
                    idSoldiers.insert(curIndex,data)
                    hasShadow=1
                }
                idRow.parent.width=idRow.parent.parent.width*0.25+(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                friend.width=idRow.parent.parent.width*0.25-(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
            }

            onExited: {
                if(limit===1)
                    return
                if(hasShadow==1)
                {
                    idSoldiers.remove(curIndex)
                    hasShadow=0
                }
                idRow.parent.width=idRow.parent.parent.width*0.25+(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                friend.width=idRow.parent.parent.width*0.25-(idSoldiers.count*oneCardWidth-friend.cardCount*oneCardWidth)
                curIndex=idSoldiers.count
            }


        }
    }

    Component
    {
        id: idSoldier
        Item {

            function shield(){
                idSoldierBox.opacity=0.6
            }

            function start(){
                cardAn.start()
            }

            function unShield(){
                idSoldierBox.opacity=1
            }

            function showArmor(armor){
                if(armor<=0)
                    armorText.text=""
                else
                    armorText.text="%1".arg(armor)
            }

            function hovered(){
                idShowRect.opacity=0.6
            }

            function unHovered(){
                idShowRect.opacity=0
            }

            id: idSoldierItem
            width: height*4/7
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2
            height: idRow.height
            states: [
                State {
                    // when
                    PropertyChanges {
                        target: idSoldierItem
                        x: x
                        y: y
                    }
                }
            ]

            Card{

                id: idSoldierBox
                parent: idRow
                x: idRow.parent.rowNum%2==1?idSoldierItem.x:idSoldierItem.x+idRow.width
                y: idSoldierItem.y
                width: idSoldierItem.width
                height: idSoldierItem.height
                myName: {
                    return name}
                myType: type
                myStrength: strength
                //transform: Rotation { origin.x: parent.width/2; origin.y:parent.height/2; angle: ban===1?180:0}

                Text {
                    z:10
                    id: armorText
                    anchors.right: parent.right
                    anchors.margins: parent.width/10
                    anchors.top: parent.top
                    font.pixelSize: parent.width/3
                    color: "#ff6600"
                }

                SequentialAnimation{
                    id:cardAn
                    ParallelAnimation{
                        PropertyAnimation {
                            target: idSoldierBox
                            property: "width"
                            to:idSoldierItem.width*1.8
                            duration: 200
                        }
                        PropertyAnimation {
                            target: idSoldierBox
                            property: "height"
                            to:idSoldierItem.height*1.8
                            duration: 200
                        }
                    }
                    ParallelAnimation{
                        PropertyAnimation {
                            target: idSoldierBox
                            property: "width"
                            to:idSoldierItem.width
                            duration: 200
                        }
                        PropertyAnimation {
                            target: idSoldierBox
                            property: "height"
                            to:idSoldierItem.height
                            duration: 200
                        }
                    }
                }

                Rectangle{
                    id:idShowRect
                    anchors.fill: parent
                    color: "#aaaaaa"
                    opacity: 0
                    z:10
                }

            }
        }

    }
    ListModel {
        id: idSoldiers
//                ListElement{
//                    name:"dg"
//                    type:"King"
//                    strength:10
//                }
    }
}
