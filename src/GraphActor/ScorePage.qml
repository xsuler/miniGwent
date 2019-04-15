import QtQuick 2.0

Item {

    anchors.fill: parent
    z:20

    Rectangle{
        color: "#000000"
        anchors.fill: parent

        Text {
            id: winnerT
            y:parent.height/2-height*3
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.width/25
            color: "#00ffff"
        }
        Text {
            id: myScoreT
            y:winnerT.y+1.5*height
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.width/25
            color: "#00ffff"
        }
        Text {
            id: enScoreT
            y:myScoreT.y+1.5*height
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.width/25
            color: "#00ffff"
        }
    }

    Connections{
        target: parent
        onMshowScore:{
            if(winner=="null")
                winnerT.text="no winner"
            else
                winnerT.text="winner is %1".arg(winner)
            myScoreT.text="my score : %1".arg(myScore)
            enScoreT.text="enemy's score : %1".arg(enScore)
        }
    }

}
