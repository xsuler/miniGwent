import QtQuick 2.9
import QtQuick.Controls 2.2

Item{

    signal sendMyName(var sname)
    signal signup()

    function loginAct(){
        GA.loginRequest(idUserName.text,idPassWord.text)
        sendMyName(idUserName.text)
    }
    function signUpAct(){
        signup()
    }

    property color btnDef: "#aaaaaa"
    property color btnHov: "#00ffff"
    property color btnPrs: "#ff3300"
    property color btnBak: "#303030"
    property color myBak: "#555555"
    property string myName :idUserName.text
    property int errorFlag: 1

    id:idLoginPage
    width: parent.width/3
    height: parent.height/5
    anchors.centerIn: parent

    Connections{
        target: parent
        onLoginError:{
            errorFlag=flag
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
            if(errorFlag===0)
                return qsTr("user doesn't exist!")
            if(errorFlag===-1)
                return qsTr("password error!")
            if(errorFlag===-2)
                return qsTr("user is in game now!")
        }
        color: "#ff6600"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: parent.height/20
    }

    TextField{
        id:idUserName
        font.pixelSize: height/2
        y:parent.height*2.5/10
        width: parent.width/1.5
        height: parent.height/5
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("Enter your username")
    }

    TextField{
        id:idPassWord
        y:parent.height*3.2/10+height
        font.pixelSize: height/2
        width: idUserName.width
        height: idUserName.height
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("Enter your password")
        echoMode: TextInput.Password
    }

    SmartButton{
        id:idlLoginBtn
        fontPixsize: height/1.5
        mytext: qsTr("login")
        btnFontColorDef: btnDef
        btnFontColorHov: btnHov
        btnFontColorPrs: btnPrs
        y:idPassWord.y+idPassWord.height*1.3
        width: idPassWord.width/4
        height: idPassWord.height*0.8
        border.color: btnFontColor
        border.width: height/25
        x:idPassWord.x+(idPassWord.width-2*width)/3
        color: btnBak
        onClicked: loginAct()
    }

    SmartButton{
        id:idSignUpBtn
        mytext: qsTr("sign up")
        fontPixsize: height/1.5
        btnFontColorDef: btnDef
        btnFontColorHov: btnHov
        btnFontColorPrs: btnPrs
        y:idPassWord.y+idPassWord.height*1.3
        width: idPassWord.width/4
        height: idPassWord.height*0.8
        border.color: btnFontColor
        border.width: height/25
        x:idPassWord.x+(idPassWord.width-2*width)*2/3+width
        color: btnBak
        onClicked: signUpAct()
    }
}
