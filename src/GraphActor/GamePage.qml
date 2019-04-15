import QtQuick 2.7
import QtQuick.Controls 2.2
import "createItem.js" as CI


Rectangle {

    signal showSkill(var names,var types,var strengths)

    property bool blockP
    property bool block:true
    property var skillPage
    property int passFlag: 0

    id:idGamePage
    anchors.fill: parent
    width: 800
    height: 600

    Connections{
        target: skillPage
        onChosed:{
            skillPage.destroy()
            NA.chosed(index)
        }
    }

    Connections{
        target: GA
        onChooseSkill:{
            skillPage=Qt.createQmlObject('import QtQuick 2.0; SkillPage {z:10}',
                                         idGamePage,
                                         "dynamicSnippet1");
            showSkill(names,types,strengths)
        }
        onShowInfo:{
            detailN.text=name
            details.text=cardDetail
        }
    }
    Rectangle{
        anchors.right: parent.right
        y:parent.height/2-height*0.7
        anchors.margins: parent.width*0.02
        width: parent.width/5
        z:10
        height: parent.height/5

        color: "#000000"
        Text {
            id: detailN
            color: "#ff6600"
            anchors.top: parent.top
            x:parent.width/10
            anchors.margins: parent.height/10
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.width/16
        }
        Text {
            id: details
            color: "#ff6600"
            anchors.top: detailN.bottom
            anchors.margins: parent.height/10
            x:parent.width/10
            font.pixelSize: parent.width/16
        }
    }


    Text {
        id: tip
        color: "#ffffff"
        z:10
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        font.pixelSize: parent.width/40
    }

    Connections{
        target: NA
        onStart:{
            passFlag=0
            timer.start()
            block=blockP
        }

        onEnemyPass:{
            timer.clear()
            isEnPass.text="passed"
            enTurn.opacity=1
            enTurn.color="#555555"
        }

        onFakeTurn:{
            if(idMe.myTableModel.count<=0)
            {
                if(passFlag==1)
                    return
                NA.passE()
                isPass.text="passed"
                timer.clear()
                passFlag=1
                return
            }
        }

        onTurn:{
            if(idMe.myTableModel.count<=0)
            {

                NA.passE()
                isPass.text="passed"
                timer.clear()
                return
            }
            if(block==true)
            {
                block=false
                myTurn.opacity=1
                enTurn.opacity=0
                timer.clear()
                timer.start()
                bar0.opacity=0
            }
            else
            {
                block=true
                myTurn.opacity=0
                enTurn.opacity=1
                timer.clear()
                timer.start()
                bar0.opacity=0
            }
        }
        onChooseOneOfEnemyRow:{
            tip.text="please choose One Of Enemy's Row"
            block=true
        }
        onFinishChooseRow:{
             tip.text=""
            block=false
        }
        onFinishChooseCard:{
             tip.text=""
            block=false
        }
        onChooseOneOfCard:{
            block=true
            if(flag==0)
            {
                tip.text="please choose One Of your card"
            }
            else
            {
                tip.text="please choose One Of Enemy's card"
            }
        }
    }

    Connections{
        target: parent
        onMshowTable:{
            var i,data
            for(i=0;i<names.length;i++)
            {
                data = {'name':"back",'type':'','strength':-1}
                idAnotherPlayer.myTableModel.append(data)
            }
            idMe.myTableModel.sync()
            for(i=0;i<names.length;i++)
            {
                data = {'name':names[i],'type':types[i],'strength':strengths[i]}
                idMe.myTableModel.append(data)
            }
            idMe.myTableModel.sync()
            idMe.actice=flagG
            idMe.deckNum=deck
            if(flagG==0)
            {
                blockP=true
                myTurn.opacity=0
                enTurn.opacity=1
            }
            else
            {
                blockP=false
                myTurn.opacity=1
                enTurn.opacity=0
            }
        }
    }


    MouseArea{
        id:mouseArea
        z:10
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height*0.18
        onPressed: {mouse.accepted = block}
        onClicked:{mouse.accepted = block}
    }

    Timer{
        id:timer
        interval: 100
        repeat: true
        property int count: 0
        function clear()
        {
            showBar.width=parent.width*0.5
            stop()
            count=0
        }
        onTriggered: {
            count++
            showBar.width=parent.width*0.5*(300-count)*1.0/300
            if(count>300)
            {
                showBar.width=parent.width*0.5
                if(block==false)
                    NA.forceTurn()
                count=0
            }
        }

    }

    Rectangle{
        z:10
        id:showBar
        anchors.centerIn: parent
        width: parent.width*0.5
        height: parent.height*0.01
        color:"#00ffff"
    }


    Image {
        fillMode: Image.Stretch
        anchors.fill: parent
        source: "images/GameBack.jpg"
    }



    PlayerScene{
        id:idMe
        enTable: idAnotherPlayer.table
        ban:0
        z:2
        friend: idAnotherPlayer

        Rectangle{
            id:myTurn
            anchors.right: parent.right
            anchors.margins: parent.width/10
            y:parent.height*1.2/2
            width: parent.width/13
            height: width
            Text {
                id: isPass
                anchors.centerIn: parent
                color: "#ffffff"
                font.pixelSize: parent.width/5
            }
            color: "#00ffff"
            Timer{
                id:myTimer
                interval: 100
                repeat: true
                property int count: 0
                function clear()
                {
                    stop()
                    count=0
                }
                onTriggered: {
                    count++
                    if(count>25)
                    {
                        NA.pass()
                        isPass.text="passed"
                        myTurn.opacity=1
                        myTurn.color="#555555"
                        timer.clear()
                        stop()
                        count=0
                    }
                }
            }

            Rectangle{
                id:bar0
                opacity: 0
                anchors.top: parent.bottom
                color: "#ffffff"
                height: parent.height/8
                width: parent.width*(25-myTimer.count)*0.04
            }

            MouseArea{
                anchors.fill: parent
                onPressed:{
                    if(block==true)
                        return
                    myTimer.start()
                    bar0.opacity=1
                }
                onReleased: {
                    if(block==true)
                        return
                    myTimer.clear()
                    bar0.opacity=0
                }
            }
        }
    }
    PlayerScene{
        id:idAnotherPlayer
        enTable: idMe.table
        ban:1
        z:1
        friend:idMe
        transform: Rotation { origin.x: parent.width/2; origin.y:parent.height/2; angle: 180}

        Rectangle{
            id:enTurn
            anchors.right: parent.right
            anchors.margins: parent.width/10
            y:parent.height*1.2/2
            width: parent.width/13
            height: width
            color: "#00ffff"

            Text {
                id: isEnPass
                anchors.centerIn: parent
                color: "#ffffff"
                font.pixelSize: parent.width/5
            }
        }
    }
}
