#include "networkactor.h"
#include<QDebug>

NetworkActor::NetworkActor(QObject *parent) : QObject(parent)
{
    myPassFlag=0;
    enemyPassFlag=0;
    socket=new QTcpSocket(this);
    socket->connectToHost(hostAddr,port);
    connect(socket,SIGNAL(readyRead()),this,SLOT(messageParser()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(errorR(QAbstractSocket::SocketError)));
}

NetworkActor::~NetworkActor()
{

}

void NetworkActor::login(QString name, QString psw)
{
    sendMessage(JDG.loginInfo(name,psw));
}

void NetworkActor::getUserOnline()
{
    sendMessage(JDG.getUserOnline());
}

void NetworkActor::connectRequest(QString name)
{
    sendMessage(JDG.connectRequest(name));
}

void NetworkActor::connectConfirm(QString name)
{
    sendMessage(JDG.connectConfirm(name));
}

void NetworkActor::connectRefuse(QString name)
{
    sendMessage(JDG.connectRefuse(name));
}

void NetworkActor::signupRequest(QString name, QString psw)
{
    sendMessage(JDG.signupInfo(name,psw));
}

void NetworkActor::getCardList(int flag)
{
    sendMessage(JDG.singleton("getCardList",QString::number(flag)));
}

void NetworkActor::getDeck()
{
    sendMessage(JDG.confirm("getDeck"));
}

void NetworkActor::saveEdit(QStringList name,QStringList type,QString dname,int flag)
{
    sendMessage(JDG.warpGameCMD(JDG.editList(name,type,dname,flag)));
}

void NetworkActor::startConfirm(QString name)
{
    sendMessage(JDG.singleton("startConfirm",name));
}

void NetworkActor::recordDeck(QString deck)
{
    sendMessage(JDG.singleton("recordDeck",deck));
}

void NetworkActor::replaceOne(int index)
{
    sendMessage(JDG.warpGameCMD(JDG.cmdSingleton("replaceOne",QString::number(index))));
}

void NetworkActor::close()
{
    sendMessage(JDG.confirm("leave"));
}

void NetworkActor::handler(const QJsonObject &obj)
{

    if(JDG.isCmdAnother(obj))
    {
        if(JDG.isCmds(obj))
        {
            QList<QJsonObject> objs=JDG.deCmds(obj);
            for(auto p:objs)
            {
                handler(JDG.cmdWarpAnother(p));
            }
        }
        if(JDG.isCmdStringList(obj,"endRound"))
        {
            QStringList list=JDG.deCmdStringList(obj);
            emit endRound(list[0],list[2],list[1]);
        }
        if(JDG.isCmdStringList(obj,"GameOver"))
        {
            sendMessage(JDG.confirm("GameOver"));
            QStringList list=JDG.deCmdStringList(obj);
            emit endGame(slistToVlist(list),1);
        }
        if(JDG.isCmdConfirm(obj,"clearWeather"))
        {
            if(JDG.isCmdEnOp(obj))
                emit clearWeather(0);
            else
                emit clearWeather(1);
        }
        if(JDG.isCmdStringList(obj,"showWeather"))
        {
            QStringList list=JDG.deCmdStringList(obj);
            if(JDG.isCmdEnOp(obj))
                emit showWeather(list[0],list[1].toInt(),0);
            else
                emit showWeather(list[0],list[1].toInt(),1);
        }
        if(JDG.isCmdEffect(obj,"addShield"))
        {
            auto rows=JDG.deCmdEffect(obj);
            QVariantList list1;
            QVariantList list2;
            for(auto p:rows)
            {
                list1.append(QVariant::fromValue(p.second.first));
                list2.append(QVariant::fromValue(p.second.second));
            }
            if(JDG.isCmdMyOp(obj))
                emit showShield(list1,list2,1);
            else
                emit showShield(list1,list2,0);
        }
        if(JDG.isCmdSimpleEffect(obj,"eraseShield"))
        {
            RowInfo row=JDG.deCmdSimpleEffect(obj).second;
            if(JDG.isCmdEnOp(obj))
                emit eraseShield(row.first,row.second,0);
            else
                emit eraseShield(row.first,row.second,1);
        }
        if(JDG.isCmdSimpleEffectWithD(obj,"updateStrength"))
        {
            auto pair=JDG.deCmdSimpleEffectWithD(obj);
            RowInfo row=pair.first.second;
            int x=pair.second.toInt();
            if(JDG.isCmdEnOp(obj))
                emit updateStrength(row.first,row.second,x,0);
            else
                emit updateStrength(row.first,row.second,x,1);
        }
        if(JDG.isCmdSimpleEffectWithD(obj,"updateArmor"))
        {
            auto pair=JDG.deCmdSimpleEffectWithD(obj);
            RowInfo row=pair.first.second;
            int x=pair.second.toInt();
            if(JDG.isCmdEnOp(obj))
                emit updateArmor(row.first,row.second,x,0);
            else
                emit updateArmor(row.first,row.second,x,1);
        }
        if(JDG.isCmdEffectSingleton(obj,"dropCard"))
        {
            auto datas=JDG.deCmdEffectSingleton(obj);
            auto list=datas.first;
            QString name=datas.second;
            int r=list[0].second.first;
            int i=list[0].second.second;
            int h=list[0].first.second;
            if(JDG.isCmdEnOp(obj))
                emit enemyDrop(name,h,r,i,0);
            else
                emit enemyDrop(name,h,r,i,1);
        }
        if(JDG.isCmdEffectWithS(obj,"insertCard"))
        {
            auto infos=JDG.deCmdEffectWithS(obj);
            auto rows=infos.first;
            auto names=infos.second;
            QVariantList list1;
            QVariantList list2;
            for(auto p:rows)
            {
                list1.append(QVariant::fromValue(p.second.first));
                list2.append(QVariant::fromValue(p.second.second));
            }
            if(JDG.isCmdMyOp(obj))
                emit insertCard(names,list1,list2,1);
            else
                emit insertCard(names,list1,list2,0);
        }
        if(JDG.isCmdStringList(obj,"refreshData"))
        {
            QStringList list=JDG.deCmdStringList(obj);
            emit refreshData(list[0].toInt(),list[1].toInt(),list[2].toInt(),list[3].toInt(),list[4].toInt(),list[5].toInt(),1);
        }
        if(JDG.isCmdEffect(obj,"destroyCard"))
        {
            auto rows=JDG.deCmdEffect(obj);
            QVariantList list1;
            QVariantList list2;
            for(auto p:rows)
            {
                list1.append(QVariant::fromValue(p.second.first));
                list2.append(QVariant::fromValue(p.second.second));
            }
            if(JDG.isCmdEnOp(obj))
                emit destroyCard(list1,list2);
            else
                emit enemyDestroyCard(list1,list2);
        }
        return;
    }
    if(JDG.isCmds(obj))
    {
        QJsonObject bobj=obj;
        QList<QJsonObject> objs=JDG.deCmds(bobj);
        QList<QJsonObject> ends;
        for(int i=0;i<objs.length();i++)
        {
            if(JDG.hasTrueKey(objs[i],"end"))
            {
                ends.append(objs[i]);
                objs.removeAt(i);
                i--;
            }
        }
        if(ends.length()>1)
        {
            for(int i=0;i<ends.length()-1;i++)
            {
                QJsonObject eobj=ends[i];
                JDG.removeKeyRecursive(eobj,"end");
                objs.append(eobj);
            }
        }
        if(ends.length()>0)
            objs.append(ends.last());
        for(auto p:objs)
        {
            handler(p);
        }
    }
    if(JDG.isGameCMD(obj))
    {
        QJsonObject cmd=JDG.deGameCMD(obj);
        if(JDG.isEditConfirm(cmd))
        {
            emit editConfirm(JDG.deEditConfirm(cmd).second.second);
        }
    }

    if(JDG.isLoginRecv(obj))
    {
        emit loginRecv(JDG.deLoginRecv(obj));
    }
    if(JDG.isUserList(obj))
    {
        sendMessage(JDG.confirm("getCurDeck"));
        emit userList(JDG.deUserList(obj));
    }
    if(JDG.isConnectRequest(obj))
    {
        emit connectRequestNA(JDG.deConnectRequest(obj));
    }
    if(JDG.isConnectConfirm(obj))
    {
        emit connectConfirmNA(JDG.deConnectConfirm(obj));
    }
    if(JDG.isConnectRefuse(obj))
    {
        emit connectRefuseNA(JDG.deConnectRefuse(obj));
    }
    if(JDG.isSingleton(obj,"curDeckName"))
    {
        QString res=JDG.deSingleton(obj);
        emit curDeckName(res);
    }
    if(JDG.isSignupRecv(obj))
    {
        emit signupRecv(JDG.deSignupRecv(obj));
    }
    if(JDG.isConfirm(obj,"noDeck"))
    {
        emit noDeck();
    }
    if(JDG.isCardList(obj))
    {
        QString d=obj["flag"].toString();
        emit cardList(JDG.deCardList(obj),d.toInt());
    }
    if(JDG.isDeckData(obj))
    {
        emit deckData(JDG.deDeckData(obj));
    }
    if(JDG.isCmdStringList(obj,"endRound"))
    {
        QStringList list=JDG.deCmdStringList(obj);
        emit endRound(list[0],list[1],list[2]);
    }
    if(JDG.isCmdStringList(obj,"GameOver"))
    {
        sendMessage(JDG.confirm("GameOver"));
        QStringList list=JDG.deCmdStringList(obj);
        emit endGame(slistToVlist(list),0);
    }
    if(JDG.isCmdSingleton(obj,"startReplace"))
    {
        myPassFlag=0;
        enemyPassFlag=0;
        QStringList list=JDG.deCmdStringList(obj);
        if(list.length()<=1)
        {
            sendMessage(JDG.warpGameCMD(JDG.cmdConfirm("replaceFinish")));
        }
        else
        {
            emit showReplace(list.mid(1,list.length()-1),list[0].toInt());
        }
    }
    if(JDG.isCmdSingleton(obj,"replace"))
    {
        emit replaceTo(JDG.deCmdSingleton(obj));
    }
    if(JDG.isCmdStringList(obj,"showWeather"))
    {
        QStringList list=JDG.deCmdStringList(obj);
        if(JDG.isCmdEnOp(obj))
            emit showWeather(list[0],list[1].toInt(),1);
        else
            emit showWeather(list[0],list[1].toInt(),0);
    }
    if(JDG.isCmdStringList(obj,"showTable"))
    {
        emit showTable(JDG.deCmdStringList(obj));
    }
    if(JDG.isCmdSingleton(obj,"appendHand"))
    {
        emit appendHand(JDG.deCmdSingleton(obj));
    }
    if(JDG.isCmdEffect(obj,"addShield"))
    {
        auto rows=JDG.deCmdEffect(obj);
        QVariantList list1;
        QVariantList list2;
        for(auto p:rows)
        {
            list1.append(QVariant::fromValue(p.second.first));
            list2.append(QVariant::fromValue(p.second.second));
        }
        if(JDG.isCmdMyOp(obj))
            emit showShield(list1,list2,0);
        else
            emit showShield(list1,list2,1);
    }
    if(JDG.isCmdSimpleEffect(obj,"eraseShield"))
    {
        //flag means
        RowInfo row=JDG.deCmdSimpleEffect(obj).second;
        //enop means battle rather than operaton
        if(JDG.isCmdEnOp(obj))
            emit eraseShield(row.first,row.second,1);
        else
            emit eraseShield(row.first,row.second,0);
    }
    if(JDG.isCmdSimpleEffectWithD(obj,"updateStrength"))
    {
        auto pair=JDG.deCmdSimpleEffectWithD(obj);
        RowInfo row=pair.first.second;
        int x=pair.second.toInt();
        if(JDG.isCmdEnOp(obj))
            emit updateStrength(row.first,row.second,x,1);
        else
            emit updateStrength(row.first,row.second,x,0);
    }
    if(JDG.isCmdSimpleEffectWithD(obj,"updateArmor"))
    {
        auto pair=JDG.deCmdSimpleEffectWithD(obj);
        RowInfo row=pair.first.second;
        int x=pair.second.toInt();
        if(JDG.isCmdEnOp(obj))
            emit updateArmor(row.first,row.second,x,1);
        else
            emit updateArmor(row.first,row.second,x,0);
    }
    if(JDG.isCmdEffectWithS(obj,"insertCard"))
    {
        auto infos=JDG.deCmdEffectWithS(obj);
        auto rows=infos.first;
        auto names=infos.second;
        QVariantList list1;
        QVariantList list2;
        for(auto p:rows)
        {
            list1.append(QVariant::fromValue(p.second.first));
            list2.append(QVariant::fromValue(p.second.second));
        }
        if(JDG.isCmdMyOp(obj))
            emit insertCard(names,list1,list2,0);
        else
            emit insertCard(names,list1,list2,1);
    }
    if(JDG.isCmdEffect(obj,"destroyCard"))
    {
        auto rows=JDG.deCmdEffect(obj);
        QVariantList list1;
        QVariantList list2;
        for(auto p:rows)
        {
            list1.append(QVariant::fromValue(p.second.first));
            list2.append(QVariant::fromValue(p.second.second));
        }
        if(JDG.isCmdEnOp(obj))
            emit enemyDestroyCard(list1,list2);
        else
            emit destroyCard(list1,list2);
    }
    if(JDG.isCmdStringList(obj,"chooseSkill"))
    {
        QStringList names=JDG.deCmdStringList(obj);
        emit chooseSkill(names);
    }
    if(JDG.isCmdConfirm(obj,"clearWeather"))
    {
        if(JDG.isCmdEnOp(obj))
            emit clearWeather(1);
        else
            emit clearWeather(0);
    }
    if(JDG.isCmdSingleton(obj,"useCard"))
    {
        emit useCard(JDG.deCmdSingleton(obj));
    }
    if(JDG.isCmdEffect(obj,"ChooseOneOfEnemyRow"))
    {
        emit chooseOneOfEnemyRow();
    }
    if(JDG.isCmdConfirm(obj,"startGame"))
    {
        emit start();
    }
    if(JDG.isCmdConfirm(obj,"pass"))
    {
        emit enemyPass();
        enemyPassFlag=1;
    }
    if(JDG.isCmdConfirm(obj,"ChooseOneOfCard"))
    {
        if(JDG.isCmdMyOp(obj))
            emit chooseOneOfCard(0);
        else
            emit chooseOneOfCard(1);
    }
    if(JDG.isCmdStringList(obj,"refreshData"))
    {
        QStringList list=JDG.deCmdStringList(obj);
        emit refreshData(list[0].toInt(),list[1].toInt(),list[2].toInt(),list[3].toInt(),list[4].toInt(),list[5].toInt(),0);
    }
    if(JDG.isCmdConfirm(obj,"ChooseOneOfCard"))
    {
        if(JDG.isCmdMyOp(obj))
            emit chooseOneOfCard(0);
        else
            emit chooseOneOfCard(1);
    }
    if(JDG.isCmdEnd(obj))
    {
        sendMessage(JDG.warpGameCMD(JDG.cmdConfirm("turn")));
        if(enemyPassFlag==0)
        {
            emit turn();
        }
        else
        {
            emit fakeTurn();
        }
    }
    if(JDG.isCmdConfirm(obj,"turn"))
    {
        if(myPassFlag==0)
            emit turn();
    }
}

void NetworkActor::sendMessage(const QJsonObject &obj)
{
    QByteArray data;
    QDataStream st(&data,QIODevice::WriteOnly);
    st.setVersion(QDataStream::Qt_5_9);
    st<<(qint16)0;
    QJsonDocument doc(obj);
    st<<doc.toBinaryData();
    st.device()->seek(0);
    st<<quint16(data.size()-sizeof(quint16));
    socket->write(data);
}

void NetworkActor::messageParser()
{
    qDebug()<<"a message";
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_9);
    static qint16 size=0;
    if((size==0)&&socket->bytesAvailable()<sizeof(qint16))
    {
        return;
    }
    in>>size;
    if(socket->bytesAvailable()<size)
        return;
    QByteArray data;
    in>>data;
    QJsonDocument doc(QJsonDocument::fromBinaryData(data));
    size=0;
    handler(doc.object());
}

void NetworkActor::errorR(QAbstractSocket::SocketError)
{
    qDebug()<<socket->errorString();
}

void NetworkActor::replaceFinish()
{
    sendMessage(JDG.warpGameCMD(JDG.cmdConfirm("replaceFinish")));
}

void NetworkActor::dropCard(int handIndex, int rowIndex, int row)
{
    QList<RowPair> list;
    list.append(RowPair(RowInfo(-1,handIndex),RowInfo(row,rowIndex)));
    sendMessage(JDG.warpGameCMD(JDG.cmdEffect("dropCard",list)));
}

void NetworkActor::chosed(int index)
{
    sendMessage(JDG.warpGameCMD(JDG.cmdWarpFeedback(JDG.cmdSingleton("skillChosed",QString::number(index)))));
}

void NetworkActor::chooseEnemyRow(int index)
{
    emit finishChooseRow();
    sendMessage(JDG.warpGameCMD(JDG.cmdWarpFeedback(JDG.cmdSingleton("chooseEnemyRow",QString::number(index)))));
}

void NetworkActor::chooseOneCard(int row, int index)
{
    emit finishChooseCard();
    sendMessage(JDG.warpGameCMD(JDG.cmdWarpFeedback(JDG.cmdSimpleEffect("chooseOneCard",RowPair(RowInfo(-1,-1),RowInfo(row,index))))));
}

void NetworkActor::forceTurn()
{
    sendMessage(JDG.warpGameCMD(JDG.cmdConfirm("turn")));
    emit turn();
}

void NetworkActor::pass()
{
    sendMessage(JDG.warpGameCMD(JDG.cmdConfirm("pass")));
    myPassFlag=1;
    emit turn();
}

void NetworkActor::passE()
{
    sendMessage(JDG.warpGameCMD(JDG.cmdConfirm("pass")));
}
//remember to warp feed back if you are sending a feedback, so that GameActor will submit it to current deploy
