import QtQuick 2.0
import QtQuick.Controls 2.2

Item{

    signal close()
    signal nameWarn()

    property int cardWidth:width/7
    property int cardHeight:height/3.3
    property color backGroundColor: "#555555"
    property var msgBoxs
    property int submitFlag

    id:idListFrame
    width: parent.width*0.8
    height: parent.height*0.8
    anchors.centerIn: parent

    function submitAct(){
        if(idName.text.length<=0)
        {
            nameWarn()
            return
        }

        var list1=[];
        var list2=[];
        for(var i=0;i<idModel1.count;i++)
        {
            list1.push(idModel1.get(i).name)
            list2.push(idModel1.get(i).type)
        }
        GA.saveEdit(list1,list2,idName.text,submitFlag)
    }

    function returnAct(){
        close()
    }

    TextField{
        id:idName
        anchors.bottom: parent.top
        anchors.margins: parent.height/40
        font.pixelSize: height/2
        x:(parent.width-3*width)/4
        width: parent.width/3.5
        height: parent.height/15
        placeholderText: qsTr("Enter a name")
        echoMode: TextInput.text
    }

    SmartButton{
        id:idSubmit
        fontPixsize: height/1.5
        mytext: qsTr("Submit")
        btnFontColorDef: "#aaaaaa"
        btnFontColorHov: "#00ffff"
        btnFontColorPrs: "#00aaaa"
        btnBackColorDef: "#111111"
        btnBackColorHov: "#333333"
        btnBackColorPrs: "#222222"
        opacity: 0.7
        anchors.bottom: parent.top
        anchors.margins: parent.height/40
        x:(parent.width-3*width)*2/4+width
        width: parent.width/3.5
        height: parent.height/15
        border.color: btnFontColor
        border.width: height/20
        onClicked: submitAct()
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
        anchors.bottom: parent.top
        anchors.margins: parent.height/40
        x:(parent.width-3*width)*3/4+2*width
        width: parent.width/3.5
        height: parent.height/15
        border.color: btnFontColor
        border.width: height/20
        onClicked: returnAct()
    }



    Connections{
        target: parent
        onMshowCardAvailable:{
            var data
            var i
            if(flag==1)
            {
                idName.opacity=0
                idName.text=curDeckName
                for(i=0;i<cnames.length;i++)
                {
                    data = {'name':cnames[i],'type':ctypes[i],'strength':cstrengths[i]}
                    idModel1.append(data)
                }
            }

            for(i=0;i<names.length;i++)
            {
                data = {'name':names[i],'type':types[i],'strength':strengths[i]}
                idModel.append(data)
            }
            idModel.sync()
        }
    }

    ListView {

        id: idChosedList
        clip: true
        y:idCardList.height+ parent.height/20
        width: idCardList.width
        height: (parent.height-y)*0.8
        delegate: idChosed
        model: idModel1
        contentHeight: height*0.9
        contentWidth: (idChosedList.count+2)*spacing
        orientation:ListView.Horizontal

        MouseArea{
            z:5
            anchors.fill: parent

            onClicked: {
                if(idChosedList.indexAt(mouseX + idChosedList.contentX, mouseY + idChosedList.contentY)===-1)
                    return
                idModel1.remove(idChosedList.indexAt(mouseX + idChosedList.contentX, mouseY + idChosedList.contentY))
            }
        }

        Rectangle{
            anchors.fill: parent
            color: backGroundColor
            opacity: 0.3
        }

        ScrollBar.horizontal: ScrollBar {
            policy: ScrollBar.AlwaysOn
            id:idScrollBar1
            parent: idChosedList.parent
            anchors.top: idChosedList.bottom
            anchors.left: idChosedList.left
            anchors.right: idChosedList.right
        }
    }

    Component {
        id: idChosed
        Item{
            width: height*cardWidth/cardHeight
            height: idChosedList.height*0.9
            CardBox{
                z:2
                id:idCardBox
                anchors.fill: parent
                myName: name
                myType: type
                myStrength: strength
                isInChoose: true
            }
        }
    }

    ListModel {
        id:idModel1
    }

    GridView {

        width: parent.width
        height: parent.height*0.7
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
