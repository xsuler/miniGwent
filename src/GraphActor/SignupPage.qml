import QtQuick 2.9
import QtQuick.Controls 2.2

Item{

    signal login()

    function signupAct(){
        if(idUserName.text.length===0)
        {
            errorFlag=2
            return
        }
        if(idPassWord.text.length===0)
        {
            errorFlag=3
            return
        }
        if(idPassWord.text!==idPassWord2.text)
        {
            errorFlag=4
            return
        }
        GA.signupRequest(idUserName.text,idPassWord.text)
    }

    function returnAct(){
        login()
    }

    property color btnDef: "#aaaaaa"
    property color btnHov: "#00ffff"
    property color btnPrs: "#ff3300"
    property color btnBak: "#303030"
    property color myBak: "#555555"
    property string myName :idUserName.text
    property int errorFlag: 0

    id:idSignupPage
    width: parent.width/3
    height: parent.height/4
    anchors.centerIn: parent

    Connections{
        target: parent
        onSignupRecv:{
            if(flag==0)
                errorFlag=1
            else
                errorFlag=5
        }
    }

    Rectangle {
        anchors.fill: parent
        opacity: 0.5
        radius: width/8
        color: myBak
    }

    Text {
        text: {
            if(errorFlag===1)
                return qsTr("username has been occupied!")
            if(errorFlag===2)
                return qsTr("username is empty!")
            if(errorFlag===3)
                return qsTr("password is empty!")
            if(errorFlag===4)
                return qsTr("two password is different!")
            if(errorFlag===5)
                return qsTr("sign up successfully!")
        }
        color: "#ff6600"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: parent.height/20
    }

    TextField{
        id:idUserName
        font.pixelSize: height/2
        y:parent.height*2.0/10
        width: parent.width/1.5
        height: parent.height/7
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("Enter your username")
    }

    TextField{
        id:idPassWord
        y:parent.height*2.7/10+height
        font.pixelSize: height/2
        width: idUserName.width
        height: idUserName.height
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("Enter your password")
        echoMode: TextInput.Password
    }

    TextField{
        id:idPassWord2
        y:parent.height*3.4/10+2*height
        font.pixelSize: height/2
        width: idUserName.width
        height: idUserName.height
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("Enter your password")
        echoMode: TextInput.Password
    }

    SmartButton{
        id:idSignup
        fontPixsize: height/1.5
        mytext: qsTr("sign up")
        btnFontColorDef: btnDef
        btnFontColorHov: btnHov
        btnFontColorPrs: btnPrs
        y:idPassWord2.y+idPassWord2.height*1.5
        width: idPassWord.width/4
        height: idPassWord.height*0.8
        border.color: btnFontColor
        border.width: height/25
        x:idPassWord.x+(idPassWord.width-2*width)/3
        color: btnBak
        onClicked: signupAct()
    }

    SmartButton{
        id:idReturn
        mytext: qsTr("return")
        fontPixsize: height/1.5
        btnFontColorDef: btnDef
        btnFontColorHov: btnHov
        btnFontColorPrs: btnPrs
        y:idPassWord2.y+idPassWord2.height*1.5
        width: idPassWord.width/4
        height: idPassWord.height*0.8
        border.color: btnFontColor
        border.width: height/25
        x:idPassWord.x+(idPassWord.width-2*width)*2/3+width
        color: btnBak
        onClicked: returnAct()
    }
}
