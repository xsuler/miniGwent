import QtQuick 2.0

Item {

    id:idGopg
    anchors.fill: parent
    z:20

    Rectangle{
        color: "#000000"
        anchors.fill: parent

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
            anchors.horizontalCenter: parent.horizontalCenter
            y:parent.height*0.72
            width: parent.width*0.2
            height: parent.height*0.05
            border.color: btnFontColor
            border.width: height/20
            onClicked: {
                idGopg.parent.closeGO()
            }
        }

        Text {
            id: winnerT
            text: "asdads"
            y:parent.height/2-height*3
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.width/25
            color: "#00ffff"
        }
        Text {
            id: myScoreT
//                       text: "sd\nasd"
            x:parent.width/2-width*1.2
            y:winnerT.y*1.1+winnerT.height
            font.pixelSize: parent.width/25
            color: "#00ffff"
        }
        Text {
            id: enScoreT
//                       text: "sd\n254"
            x:parent.width/2+width*0.2
            y:winnerT.y*1.1+winnerT.height
            font.pixelSize: parent.width/25
            color: "#00ffff"
        }
    }

    Connections{
        target: parent
        onMshowOver:{
            if(list[0]==="2")
            {
                winnerT.text="winner is %1".arg(list[1])
                if(flag==0)
                {
                    myScoreT.text="my score:\nRound1 : %1\nRound2 : %2\n".arg(list[2]).arg(list[3])
                    enScoreT.text="enemy's score:\nRound1 : %1\nRound2 : %2\n".arg(list[4]).arg(list[5])
                }
                else
                {
                    myScoreT.text="my score:\nRound1 : %1\nRound2 : %2\n".arg(list[4]).arg(list[5])
                    enScoreT.text="enemy's score:\nRound1 : %1\nRound2 : %2\n".arg(list[2]).arg(list[3])
                }
            }
            else
            {
                if(list[1]==="null")
                {
                    winnerT.text="no winner"
                }
                else
                {
                    winnerT.text="winner is %1".arg(list[1])
                }
                if(flag==0)
                {
                    myScoreT.text="my score:\nRound1 : %1\nRound2 : %2\nRound3 : %3\n".arg(list[2]).arg(list[3]).arg(list[4])
                    enScoreT.text="enemy's score:\nRound1 : %1\nRound2 : %2\nRound3 : %3\n".arg(list[5]).arg(list[6]).arg(list[7])
                }
                else
                {
                    myScoreT.text="my score:\nRound1 : %1\nRound2 : %2\nRound3 : %3\n".arg(list[5]).arg(list[6]).arg(list[7])
                    enScoreT.text="enemy's score:\nRound1 : %1\nRound2 : %2\nRound3 : %3\n".arg(list[2]).arg(list[3]).arg(list[4])
                }
            }
        }
    }

}
