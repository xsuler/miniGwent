#include "tsproc.h"
#include<QtConcurrent>


void TSproc::handler(const QJsonObject &obj)
{
    qDebug()<<"handler";
    if(gameflag==0)
    {
        if(JDG.isSingleton(obj,"recordDeck"))
        {
            curDeck=JDG.deSingleton(obj);
            DA.recordDeck(userData->getName(),curDeck);
        }
        if(initflag==0)
        {
            timer=new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(spyOnConnect()));
            timer->start(100);
            initflag=1;
        }
        if(JDG.isSingleton(obj,"startConfirm"))
        {
            QString name=JDG.deSingleton(obj);
            toName=name;
            gameflag=1;
            TSChan *chan=getChanBy(name);
            TSChan::connectChan(chan,&toChan);
            writeToAnother(JDG.singleton("startGame",userData->getName()));
            GA.recvCMD(JDG.warpCMDbyName(JDG.cmdSingleton("init",*(deckMap.find(curDeck))),userData->getName()));
        }
        if(JDG.isLoginInfo(obj))
        {
            QPair<QString,QString> res=JDG.deLoginInfo(obj);
            if(DA.isUserExist(res.first)&&DA.isPasswordRight(res.first,res.second))
            {
                QList<QVariant> list=userList->peekAll();
                for(auto p:list)
                {
                    if(p.value<UserMeta>().getName()==res.first)
                    {
                        sendMessage(JDG.loginRecv(-2));
                        return;
                    }
                }
                myChan=new TSChan;
                TSChan::connectChan(myChan,&spyChan);
                userData=new UserMeta(res.first,myChan);
                userList->addData(QVariant::fromValue<UserMeta>(*userData));
                sendMessage(JDG.loginRecv(1));
                loginflag=1;
                deckMap=DA.getAllDeck(userData->getName());
                if(deckMap.size()>0)
                    curDeck=DA.getCurDeckName(userData->getName());
            }
            else if(DA.isUserExist(res.first))
            {
                sendMessage(JDG.loginRecv(-1));
            }
            else
            {
                sendMessage(JDG.loginRecv(0));
            }
        }
        if(JDG.isSignupInfo(obj))
        {
            QPair<QString,QString> res=JDG.deSignupInfo(obj);
            if(DA.isUserExist(res.first))
            {
                sendMessage(JDG.signupRecv(0));
            }
            else
            {
                DA.insertUser(res.first,res.second);
                sendMessage(JDG.signupRecv(1));
            }
        }
        if(JDG.isGetUserOnline(obj))
        {
            sendMessage(JDG.userList(userList->peekAll()));
        }
        if(JDG.isConnectRequest(obj))
        {
            if(curDeck.isEmpty())
            {
                sendMessage(JDG.confirm("noDeck"));
            }
            else
            {
                QString name=JDG.deConnectRequest(obj);
                writeChanTo(name,JDG.connectRequest(userData->getName()));
            }
        }
        if(JDG.isConnectConfirm(obj))
        {
            gameflag=2;
            QString name=JDG.deConnectConfirm(obj);
            writeChanTo(name,JDG.connectConfirm(userData->getName()));
        }
        if(JDG.isConnectRefuse(obj))
        {
            QString name=JDG.deConnectRefuse(obj);
            writeChanTo(name,JDG.connectRefuse(userData->getName()));
        }
        if(JDG.isSingleton(obj,"getCardList"))
        {
            int flag=JDG.deSingleton(obj).toInt();
            editMode=flag;
            sendMessage(JDG.cmdWarpPair(JDG.cardList(C::Holdable),"flag",QString::number(flag)));
        }
        if(JDG.isConfirm(obj,"getDeck"))
        {
            deckMap=DA.getAllDeck(userData->getName());
            if(deckMap.size()>0)
            {
                curDeck=DA.getCurDeckName(userData->getName());
            }
            sendMessage(JDG.deckData(deckMap.keys(),deckMap.values(),curDeck));
        }
    }
    if(JDG.isConfirm(obj,"getCurDeck"))
    {
        QString name=DA.getCurDeckName(userData->getName());
        curDeck=name;
        sendMessage(JDG.singleton("curDeckName",name));
    }
    if(JDG.isSingleton(obj,"startGame"))
    {
        TSChan *chan=getChanBy(JDG.deSingleton(obj));
        TSChan::connectChan(chan,&toChan);

        writeToAnother(JDG.warpGameCMD(JDG.warpCMDbyName(JDG.cmdSingleton("init",*(deckMap.find(curDeck))),userData->getName())));
    }
    if(JDG.isConfirm(obj,"leave")&&loginflag==1)
    {
        QList<QVariant> temp=userList->peekAll();
        for(int i=0;i<temp.length();i++)
        {
            if(temp[i].value<UserMeta>().getName()==userData->getName())
            {
                temp.removeAt(i);
            }
        }
        while(!userList->peekData().isNull())
        {
            userList->getData();
        }
        userList->addDataList(temp);
        emit quitThread();
    }
    if(JDG.isCmdConfirm(obj,"GameOver"))
    {
        gameflag=0;
    }
    if(JDG.isGameCMD(obj))
    {
        QJsonObject cmd=JDG.deGameCMD(obj);
        if(JDG.isFromGA(cmd))
        {
            if(JDG.isEditConfirm(cmd))
            {
                QPair<QPair<QString,int>,QPair<QStringList,int>> res=JDG.deEditConfirm(cmd);
                if(res.first.second==0)
                {
                    if(DA.isdeckExist(userData->getName(),res.first.first)&&editMode==0)
                    {
                        sendMessage(JDG.warpGameCMD(JDG.editConfirm(QPair<QString,int>(QString(),0),QStringList(),-1)));
                    }
                    else if(res.second.second==1)
                    {
                        if(editMode==0)
                        {
                            DA.insertDeck(userData->getName(),res.first.first,encodeHandDeck(res.second.first));
                        }
                        else
                        {
                            DA.updateDeck(userData->getName(),res.first.first,encodeHandDeck(res.second.first));
                        }
                        sendMessage(JDG.warpGameCMD(JDG.editConfirm(QPair<QString,int>(QString(),0),QStringList(),1)));
                    }
                    else
                    {
                        sendMessage(JDG.warpGameCMD(JDG.editConfirm(QPair<QString,int>(QString(),0),QStringList(),res.second.second)));
                    }
                }
                if(res.first.second==1);//todo
            }
            QString name=JDG.deCMDName(cmd);
            if(name==userData->getName())
            {
                sendMessage(cmd);//take care!!
            }
            else
            {
                writeToAnother(obj);
            }
        }
        else
        {
            if(gameflag==2)
            {
                writeToAnother(JDG.warpGameCMD(JDG.warpCMDbyName(cmd,userData->getName())));
            }
            else
            {
                if(JDG.isCMDbyName(cmd,toName))
                {
                    GA.recvCMD(cmd);
                }
                else
                {
                    GA.recvCMD(JDG.warpCMDbyName(cmd,userData->getName()));
                }
            }
        }
    }
}


void TSproc::sendMessage(const QJsonObject &obj)
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

void TSproc::init()
{
    
}

void TSproc::writeToAnother(const QJsonObject &obj)
{
    if(gameflag==0)
        return;
    toChan.addData(obj);
}

TSChan *TSproc::getChanBy(QString name)
{
    QList<QVariant> tmp=userList->peekAll();
    QMap<QString,TSChan*> map;
    for(auto p:tmp)
    {
        UserMeta mt=p.value<UserMeta>();
        map.insert(mt.getName(),mt.getChan());
    }
    TSChan* chan=map.find(name).value();
    return chan;
}

void TSproc::writeChanTo(QString name, const QJsonObject &obj)
{
    QList<QVariant> tmp=userList->peekAll();
    QMap<QString,TSChan*> map;
    for(auto p:tmp)
    {
        UserMeta mt=p.value<UserMeta>();
        map.insert(mt.getName(),mt.getChan());
    }
    TSChan* chan=map.find(name).value();
    TSChan newChan;
    TSChan::connectChan(chan,&newChan);
    newChan.addData(obj);
}

void TSproc::conChan(TSChan *chan,const QList<QVariant> &datas)
{
    userList=new TSChan;
    userList->addDataList(datas);
    TSChan::connectChan(chan,userList);
    init();
}

QString TSproc::encodeDeck(QStringList deck)
{
    QString str;
    int d;
    for(int i=0;i<C::cardsAvailable.length();i++)
    {
        d=deck.count(C::cardsAvailable[i].getName());
        str.append(QString::number(d));
    }
    return str;
}

QString TSproc::encodeHandDeck(QStringList deck)
{
    QString str;
    int d;
    for(int i=0;i<C::Holdable.length();i++)
    {
        d=deck.count(C::Holdable[i].getName());
        str.append(QString::number(d));
    }
    return str;
}


void TSproc::spyOnConnect()
{
    if(!(spyChan.peekData().isNull()))
    {
        if(gameflag==0)
        {
            sendMessage(spyChan.getData().value<QJsonObject>());
        }
        else
        {
            handler(spyChan.getData().value<QJsonObject>());
        }
    }
}

void TSproc::messageParser()
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

TSproc::TSproc(QTcpSocket *sock)
{
    qDebug()<<"come in";
    loginflag=0;
    editMode=0;
    socket=sock;
    initflag=0;
    gameflag=0;
    connect(sock,SIGNAL(readyRead()),this,SLOT(messageParser()));
    connect(&GA,SIGNAL(sendCMD(QJsonObject)),this,SLOT(handler(QJsonObject)));
}


