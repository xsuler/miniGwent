import QtQuick 2.0


Rectangle
{

    property alias myTableView :idView
    property var myTableModel :idModel
    property var myTableCardItem: idCardItem
    property int ban:parent.ban

    anchors.bottom: parent.bottom
    anchors.margins: parent.height/30
    x:parent.width*0.06
    width: parent.width*0.75
    height: parent.height*0.12
    color: "#444444"

    Connections{
        target: GA
        onAppendHand:{
            if(ban==1)
                return
            var data={'name':name,'type':type,'strength':strength}
            idModel.append(data)
        }
    }

    Connections{
        target: NA
        onRefreshData:{
            if(flag===0)
            {
                if(ban===0)
                {
                    deckNum.text="%1".arg(myDeckNum)
                    graveNum.text="%1".arg(myGraveNum)
                    score.text="%1".arg(myTStrength)
                }
                if(ban===1)
                {
                    deckNum.text="%1".arg(enDeckNum)
                    graveNum.text="%1".arg(enGraveNum)
                    score.text="%1".arg(enTStrength)
                }
            }
            if(flag===1)
            {
                if(ban===1)
                {
                    deckNum.text="%1".arg(myDeckNum)
                    graveNum.text="%1".arg(myGraveNum)
                    score.text="%1".arg(myTStrength)
                }
                if(ban===0)
                {
                    deckNum.text="%1".arg(enDeckNum)
                    graveNum.text="%1".arg(enGraveNum)
                    score.text="%1".arg(enTStrength)
                }
            }
        }
    }


    Rectangle{
        id:myScore
        anchors.left: parent.left
        y:-height*1.2
        height: parent.height*1.3
        width: height*4/7
        color: "#444444"

        Text {
            text: qsTr("TotalStrength")
            anchors.bottom: score.top
            anchors.margins: height/2
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.width/7
            color: "#ffffff"
        }

        Text {
            id: score
            anchors.centerIn: parent
            font.pixelSize: parent.width/3
            color: "#ffffff"
        }
    }

    Rectangle{
        id:myGraveYard
        color: "#444444"
        x:parent.width*1.02
        anchors.bottom: parent.bottom
        width: parent.width*0.08
        height: width*1.8

        Text {
            id:graveName
            text: qsTr("Graveyard")
            font.pixelSize: parent.width/7
            anchors.centerIn:parent
            color: "#00ffff"
        }

        Text {
            id: graveNum
            anchors.top: graveName.bottom
            anchors.margins: graveName.font.pixelSize
            font.pixelSize: parent.width/5
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#ffffff"
        }
    }

    Rectangle{
        id:myDeck
        color: "#444444"
        x:myGraveYard.x+width+parent.width*0.02
        anchors.bottom: parent.bottom
        width: parent.width*0.08
        height: width*1.8
        Text {
            id:deckName
            text: qsTr("Deck")
            font.pixelSize: parent.width/7
            anchors.centerIn:parent
            color: "#00ffff"
        }

        Text {
            id: deckNum
            anchors.top: deckName.bottom
            anchors.margins: deckName.font.pixelSize
            font.pixelSize: parent.width/5
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#ffffff"
        }
    }

    ListView {

        property int curDragIndex

        id: idView
        anchors.fill: parent
        model: idModel
        delegate: idCard
        interactive: false
        orientation: ListView.Horizontal
    }

    Component
    {
        id: idCard
        Item {
            Component.onCompleted: {
                if(ban===0)
                    mouseArea.drag.target=idCardItem
            }

            id: idCardItem
            width: height*4/7
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2

            height: idView.height
            Drag.active: mouseArea.drag.active
            states: [
                State {
                    when: idCardItem.Drag.active
                    PropertyChanges {
                        target: idCardItem
                        x: x
                        y: y
                    }
                }
            ]

            Card{
                id: idCardBox
                anchors.centerIn: parent
                width: idCardItem.width
                height: idCardItem.height
                myName: name
                myType: type
                myStrength: strength
                property alias px: idCardItem.x
                property alias py: idCardItem.y

                Behavior on px {
                    NumberAnimation {
                        duration: 500;
                        easing.type: Easing.OutBack
                    }
                }
                Behavior on py {
                    NumberAnimation {
                        duration: 500;
                        easing.type: Easing.OutBack
                    }
                }

                SequentialAnimation{
                    id:cardAn
                    ParallelAnimation{
                        PropertyAnimation {
                            target: idCardBox
                            property: "width"
                            to:idCardItem.width*1.8
                            duration: 200
                        }
                        PropertyAnimation {
                            target: idCardBox
                            property: "height"
                            to:idCardItem.height*1.8
                            duration: 200
                        }
                    }
                    ParallelAnimation{
                        PropertyAnimation {
                            target: idCardBox
                            property: "width"
                            to:idCardItem.width
                            duration: 200
                        }
                        PropertyAnimation {
                            target: idCardBox
                            property: "height"
                            to:idCardItem.height
                            duration: 200
                        }
                    }
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: idCardItem
                hoverEnabled: true
                property int curIndex
                onPressed: {
                    GA.changePlaceLimit(idCardBox.myName)
                }

                onEntered: {
                    cardAn.start()
                    console.log("start")
                }

                onPositionChanged: {
                    if(ban===1)
                        return
                    GA.showCardInfo(idCardBox.myName)
                }

                drag.onActiveChanged: {
                    if (mouseArea.drag.active)
                    {
                        idView.curDragIndex = index;
                    }
                    idCardItem.Drag.drop();
                }
            }
        }
    }
    ListModel {
        id: idModel
//                ListElement{
//                    name:"dg"
//                    type:"King"
//                    strength:10
//                }
    }
}
