import QtQuick 2.0
import "createItem.js" as CI

Item {

    signal msendMyName(var ssname)
    signal signupRecv(int flag)
    signal loginError(int flag)
    signal mshowUserList(var list)
    signal mshowDeckList(var list,var cur)
    signal mrefreshUserList(var list)
    signal mshowConnectDialog(var name)
    signal mshowCardAvailable(var names,var types,var strengths,int flag,var curDeckName,var cnames,var ctypes,var cstrengths)
    signal mshowCardAvailable1(var names,var types,var strengths)
    signal mshowHand(var names,var types,var strengths)
    signal mshowTable(int flagG,int deck,var names,var types,var strengths)
    signal mshowScore(var winner,var myScore,var enScore)
    signal mshowOver(var list,int flag)

    property var lgitm
    property var suitm
    property var game
    property var stitm
    property var uspg
    property var edpg
    property var dkpg
    property var rppg
    property var scorePages:[]
    property var gameOverPages:[]
    property var dkifs:[]
    property int flag: 0
    property var rqdlgs:[]
    property var cfdlgs:[]
    property var rfdlgs:[]
    property var eddlgs:[]
    property var nodlgs:[]
    property var curCon
    property var cons:[]
    property var myName

    id:idFrame
    anchors.fill: parent

    function closeEd(){
        var cur=eddlgs.pop()
        cur.destroy()
    }

    function closeGO(){
        var cur=gameOverPages.pop()
        cur.destroy()
    }

    function closeRq(){
        var cur=rqdlgs.pop()
        cur.destroy()
    }

    function closeCf(){
        var cur=cfdlgs.pop()
        cur.destroy()
    }

    function closeRf(){
        var cur=rfdlgs.pop()
        cur.destroy()
    }

    function closeNo(){
        var cur=nodlgs.pop()
        cur.destroy()
    }

    Image {
        anchors.fill: parent
        fillMode: Image.Stretch
        id: idBackground
        source: "images/background.jpg"
    }


    Connections{
        target: lgitm
        onSendMyName:{
            myName=sname
        }
        onSignup:{
            if(lgitm!==null)
            {
                lgitm.destroy()
                lgitm=null
            }
            suitm=CI.createItem("SignupPage.qml",idFrame);
        }
    }

    Connections{
        target: suitm
        onLogin:{
            if(suitm!==null)
            {
                suitm.destroy()
                suitm=null
            }
            lgitm=CI.createItem("LoginPage.qml",idFrame)
        }
    }

    Connections{
        target: dkpg
        onClose:{
            if(dkifs.length>0)
            {
                var cur=dkifs.pop()
                cur.destroy()
            }
            if(dkpg!==null)
            {
                dkpg.destroy()
                dkpg=null
            }
            stitm=CI.createItem("StartPage.qml",idFrame)
        }
    }

    Connections{
        target: uspg
        onClose:{
            if(uspg!==null)
            {
                uspg.destroy()
                uspg=null
            }
            stitm=CI.createItem("StartPage.qml",idFrame)
        }
    }

    Connections{
        target: edpg
        onClose:{
            if(edpg!==null)
            {
                edpg.destroy()
                edpg=null
            }
            GA.getDeck()
        }
        onNameWarn:{
            var cur=Qt.createQmlObject('import QtQuick 2.0; MessageDialog {isNameShow:false;message:"Please Enter a Name";btnText:"ok"}',
                                       idFrame,
                                       "dynamicSnippet1");
            cur.close.connect(closeEd)
            eddlgs.push(cur)
        }
    }

    Connections{
        target: NA
        onEndRound:{
            if(game!==null)
            {
                game.destroy()
                game=null
            }
            scorePages.push(CI.createItem("ScorePage.qml",idFrame))
            mshowScore(winner,myScore,enScore)
        }
        onEndGame:{
            if(game!==null)
            {
                game.destroy()
                game=null
            }

            gameOverPages.push(CI.createItem("GameOver.qml",idFrame))
            mshowOver(list,flag)
        }
        onNoDeck:{
            var cur=Qt.createQmlObject('import QtQuick 2.0; MessageDialog {isNameShow:false;message:"please edit a deck first";btnText:"ok"}',
                                       idFrame,
                                       "dynamicSnippet1");
            cur.close.connect(closeNo)
            nodlgs.push(cur)
        }
    }

    Connections{
        target: GA
        onStart:{
            lgitm=CI.createItem("LoginPage.qml",idFrame)
        }

        onNoDeck:{
            var cur=Qt.createQmlObject('import QtQuick 2.0; MessageDialog {isNameShow:false;message:"someone is connecting you, but you should choose a deck first";btnText:"ok"}',
                                       idFrame,
                                       "dynamicSnippet1");
            cur.close.connect(closeNo)
            nodlgs.push(cur)
        }
        onShowTable:{
            while(scorePages.length>0)
            {
                var cur=scorePages.pop()
                cur.destroy()
            }
            if(rppg!==null)
            {
                rppg.destroy()
                rppg=null
            }

            game=CI.createItem("GamePage.qml",idFrame)
            mshowTable(flagG,deck,names,types,strengths)
        }

        onShowReplace:{
            while(scorePages.length>0)
            {
                var cur=scorePages.pop()
                cur.destroy()
            }
            rppg=Qt.createQmlObject('import QtQuick 2.0; ReplacePage {z:10;lastTime:%1}'.arg(limit),
                                    idFrame,
                                    "dynamicSnippet1");
            mshowHand(names,types,strengths)
        }

        onLoginRecvG:{
            if(flag==1)
            {
                if(lgitm!==null)
                {
                    lgitm.destroy()
                    lgitm=null
                }
                stitm=CI.createItem("StartPage.qml",idFrame)
            }
            else
            {
                loginError(flag)
            }
        }
        onSignupRecvG:{
            signupRecv(flag)
        }
        onShowUserList:{
            if(stitm!==null)
            {
                stitm.destroy()
                stitm=null
            }
            uspg=CI.createItem("UserList.qml",idFrame)
            msendMyName(myName)
            mshowUserList(list)
        }
        onShowDeckList:{
            if(stitm!==null)
            {
                stitm.destroy()
                stitm=null
            }

            dkpg=CI.createItem("DeckList.qml",idFrame)
            mshowDeckList(list,curDeck)
        }

        onShowDeckInfoG:{
            if(dkifs.length>0)
            {
                var cur=dkifs.pop()
                cur.destroy()
            }
            var cur1=CI.createItem("DeckInfo.qml",idFrame)
            dkifs.push(cur1)
            mshowCardAvailable1(names,types,strengths)
        }

        onRefreshUserList:{
            mshowUserList(list)
        }
        onShowConnectRequest:{
            var cur=CI.createItem("RequestDialog.qml",idFrame)
            cur.close.connect(closeRq)
            rqdlgs.push(cur)
            mshowConnectDialog(name)
        }
        onShowConnectConfirm:{
            var cur=CI.createItem("ConfirmDialog.qml",idFrame)
            cur.close.connect(closeCf)
            cfdlgs.push(cur)
            mshowConnectDialog(name)
        }
        onShowConnectRefuse:{
            var cur=Qt.createQmlObject('import QtQuick 2.0; MessageDialog {isNameShow:true;message:"refused your request";btnText:"ok"}',
                                       idFrame,
                                       "dynamicSnippet1");
            cur.close.connect(closeRf)
            rfdlgs.push(cur)
            mshowConnectDialog(name)
        }

        onShowCardAvailable:{
            if(dkpg!==null)
            {
                dkpg.destroy()
                dkpg=null
            }
            if(dkifs.length>0)
            {
                var cur=dkifs.pop()
                cur.destroy()
            }
            edpg=Qt.createQmlObject('import QtQuick 2.0; EditPage {submitFlag:0}',
                                    idFrame,
                                    "dynamicSnippet1");
            mshowCardAvailable(names,types,strengths,flag,curDeckName,cnames,ctypes,cstrengths)
        }
        onEditConfirm:{
            var str;
            if(flag==-1)
                str='"deck name has been occupied"'
            if(flag==1)
                str='"your deck has been saved"'
            if(flag==0)
                str='"number of cards is smaller than 25"'
            if(flag==2)
                str='"number of cards is larger than 40"'
            if(flag==4)
                str='"no king!"'
            if(flag==3)
                str='"too much king"'
            if(flag==5)
                str='"too much gold card"'
            if(flag==6)
                str='"too much sliver card"'
            if(flag==7)
                str='"two same gold cards"'
            if(flag==8)
                str='"two same sliver cards"'
            if(flag==9)
                str='"more than three same copper cards"'
            var cur=Qt.createQmlObject('import QtQuick 2.0; MessageDialog {isNameShow:false;message:'+str+';btnText:"ok"}',
                                       idFrame,
                                       "dynamicSnippet1");
            cur.close.connect(closeEd)
            eddlgs.push(cur)
        }
    }
}
