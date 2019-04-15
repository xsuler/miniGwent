#include "gameactor.h"
#include<QtGlobal>
#include<QTime>
#include"cards.h"

void GameActor::recvCMD(const QJsonObject &cmd)
{
    QString name=JDG.deCMDName(cmd);
    if(JDG.isEditList(cmd))
    {
        QPair<QPair<QString,int>,QPair<QStringList,QStringList>> listA=JDG.deEditList(cmd);
        QPair<QStringList,QStringList> list=listA.second;
        emit sendCMD(JDG.warpGameCMD(JDG.editConfirm(listA.first,list.first,editCheck(list.first,list.second))));
    }
    if(JDG.isCmdSingleton(cmd,"init"))
    {
        QString deck=JDG.deCmdSingleton(cmd);
        initPlayer(name,deck);
    }
    if(JDG.isCmdSingleton(cmd,"replaceOne"))
    {
        QString d=JDG.deCmdSingleton(cmd);
        int i=d.toInt();
        playerByName(name).replaceOneHand(i);
        emit sendCMD(warp(JDG.cmdSingleton("replace",playerByName(name).hand[i]->name),name));
    }
    if(JDG.isCmdConfirm(cmd,"replaceFinish"))
    {
        QStringList list;
        list.append(QString::number(playerByName(name).deck.length()));
        if(winner.length()>0)
        {
            if(winner.last()!=QString("null"))
            {
                if(name==winner.last())
                {
                    list.append(QString::number(1));
                }
                else
                {
                    list.append(QString::number(0));
                }
            }
            else
            {
                if(name==player[0].name)
                {
                    list.append(QString::number(1));
                }
                else
                {
                    list.append(QString::number(0));
                }
            }
        }
        else if(name==player[0].name)
        {
            list.append(QString::number(1));
        }
        else
        {
            list.append(QString::number(0));
        }
        list.append(Card::names(playerByName(name).hand));
        replaceCount++;
        if(replaceCount>=2)
        {
            replaceCount=0;
            QList<QJsonObject> objs;
            objs.append(JDG.cmdStringList("showTable",list));
            objs.append(JDG.cmdConfirm("startGame"));
            sendCMD(warp(JDG.cmds(objs),name));
            sendCMD(warp(JDG.cmdConfirm("startGame"),anotherName(name)));
        }
        else
        {
            sendCMD(warp(JDG.cmdStringList("showTable",list),name));
        }
    }
    if(JDG.isCmdConfirm(cmd,"pass"))
    {
        Player &p=playerByName(name);
        QList<QJsonObject> objs;
        QList<QJsonObject> aobjs;
        passed.append(name);
        if(passed.length()>=2)
        {
            curRound++;
            p.scores.append(p.sumStrength());
            another(p).scores.append(another(p).sumStrength());
            passed.clear();
            if(p.scores.last()==another(p).scores.last())
            {
                winner.append("null");
            }
            else
            {
                winner.append(p.scores.last()>another(p).scores.last()?name:anotherName(name));
            }
            if(winner.length()==2)
            {
                if((winner[0]==winner[1])&&winner[0]!=QString("null"))
                {
                    QStringList list;
                    list.append("2");
                    list.append(winner[0]);
                    list.append(QString::number(p.scores[0]));
                    list.append(QString::number(p.scores[1]));
                    list.append(QString::number(another(p).scores[0]));
                    list.append(QString::number(another(p).scores[1]));
                    sendCMD(warp(JDG.cmdStringList("GameOver",list),name));
                    sendCMD(warp(JDG.cmdWarpAnother(JDG.cmdStringList("GameOver",list)),anotherName(name)));
                    clear();
                    return;
                }
            }
            if(winner.length()==3)
            {
                if(winner.count(name)>winner.count(anotherName(name)))
                {
                    QStringList list;
                    list.append("3");
                    list.append(name);
                    list.append(QString::number(p.scores[0]));
                    list.append(QString::number(p.scores[1]));
                    list.append(QString::number(p.scores[2]));
                    list.append(QString::number(another(p).scores[0]));
                    list.append(QString::number(another(p).scores[1]));
                    list.append(QString::number(another(p).scores[2]));
                    sendCMD(warp(JDG.cmdStringList("GameOver",list),name));
                    sendCMD(warp(JDG.cmdWarpAnother(JDG.cmdStringList("GameOver",list)),anotherName(name)));
                    clear();
                    return;
                }
                else if(winner.count(name)<winner.count(anotherName(name)))
                {
                    QStringList list;
                    list.append("3");
                    list.append(anotherName(name));
                    list.append(QString::number(p.scores[0]));
                    list.append(QString::number(p.scores[1]));
                    list.append(QString::number(p.scores[2]));
                    list.append(QString::number(another(p).scores[0]));
                    list.append(QString::number(another(p).scores[1]));
                    list.append(QString::number(another(p).scores[2]));
                    sendCMD(warp(JDG.cmdStringList("GameOver",list),name));
                    sendCMD(warp(JDG.cmdWarpAnother(JDG.cmdStringList("GameOver",list)),anotherName(name)));
                    clear();
                    return;
                }
                else
                {
                    QStringList list;
                    list.append("3");
                    list.append("null");
                    list.append(QString::number(p.scores[0]));
                    list.append(QString::number(p.scores[1]));
                    list.append(QString::number(p.scores[2]));
                    list.append(QString::number(another(p).scores[0]));
                    list.append(QString::number(another(p).scores[1]));
                    list.append(QString::number(another(p).scores[2]));
                    sendCMD(warp(JDG.cmdStringList("GameOver",list),name));
                    sendCMD(warp(JDG.cmdWarpAnother(JDG.cmdStringList("GameOver",list)),anotherName(name)));
                    clear();
                    return;
                }
            }
            QStringList list;
            list.append(winner.last());
            list.append(QString::number(p.scores.last()));
            list.append(QString::number(another(p).scores.last()));
            QJsonObject obj3=JDG.cmdStringList("endRound",list);
            objs.append(obj3);
            aobjs.append(obj3);
            REtimer->start(3000);
            sendCMD(warp(JDG.cmds(objs),name));
            sendCMD(warp(JDG.cmdWarpAnother(JDG.cmds(aobjs)),anotherName(name)));
        }
        else
        {
            QJsonObject obj=playerUpdate(anotherName(name));
            QJsonObject obj1=cardsStartUpdate(anotherName(name));
            objs.append(JDG.cmdConfirm("turn"));
            QStringList datas;
            datas.append(QString::number(another(p).deck.length()));
            datas.append(QString::number(another(p).graveyard.length()));
            datas.append(QString::number(p.deck.length()));
            datas.append(QString::number(p.graveyard.length()));
            datas.append(QString::number(another(p).sumStrength()));
            datas.append(QString::number(p.sumStrength()));

            QJsonObject obj2=JDG.cmdStringList("refreshData",datas);
            objs.append(obj);
            objs.append(obj1);
            objs.append(obj2);
            objs.append(JDG.cmdConfirm("pass"));
            sendCMD(warp(JDG.cmds(objs),anotherName(name)));
            aobjs.append(obj);
            aobjs.append(obj1);
            aobjs.append(obj2);
            sendCMD(warp(JDG.cmdWarpAnother(JDG.cmds(aobjs)),name));
        }

    }
    if(JDG.isCmdFeedback(cmd))
    {
        Player &p=playerByName(name);
        QList<QJsonObject> objs;
        QJsonObject obj=p.curDeploy->feedback(p,another(p),cmd);
        QJsonObject obj1=cardsFeedbackUpdate(name,obj);
        if(JDG.hasKey(obj1,"update"))
        {
            if(JDG.hasKey(obj,"end"))
            {
                JDG.removeKeyRecursive(obj,"end");
                JDG.cmdWarpKey(obj1,"end");
            }
        }
        objs.append(obj);
        objs.append(obj1);
        QStringList datas;
        datas.append(QString::number(p.deck.length()));
        datas.append(QString::number(p.graveyard.length()));
        datas.append(QString::number(another(p).deck.length()));
        datas.append(QString::number(another(p).graveyard.length()));
        datas.append(QString::number(p.sumStrength()));
        datas.append(QString::number(another(p).sumStrength()));
        QJsonObject obj2=JDG.cmdStringList("refreshData",datas);
        objs.append(obj2);
        sendCMD(warp(JDG.cmds(objs),name));
        sendCMD(warp(JDG.cmdWarpAnother(JDG.cmds(objs)),anotherName(name)));
    }
    if(JDG.isCmdEffect(cmd,"dropCard"))
    {
        QList<RowPair> list=JDG.deCmdEffect(cmd);
        Player &p=playerByName(name);
        int r=list[0].second.first;
        int i=list[0].second.second;
        int h=list[0].first.second;
        if(h!=-1)
        {
            p.hand[h]->row=r;
            p.curDeploy=p.hand[h];
            if(p.curDeploy->place==CardPlace::enAnywhere||p.curDeploy->place==CardPlace::en1||p.curDeploy->place==CardPlace::en2||p.curDeploy->place==CardPlace::en3)
            {
                another(p).row[r]->insert(i,p.hand[h]);
            }
            else
            {
                p.row[r]->insert(i,p.hand[h]);
            }
            p.hand.removeAt(h);
        }
        else
        {
            p.curDeploy->row=r;
            p.curDeploy->index=i;
            if(p.curDeploy->place==CardPlace::enAnywhere||p.curDeploy->place==CardPlace::en1||p.curDeploy->place==CardPlace::en2||p.curDeploy->place==CardPlace::en3)
            {
                another(p).row[r]->insert(i,p.curDeploy);
            }
            else
            {
                p.row[r]->insert(i,p.curDeploy);
            }
        }
        QString cardName=p.curDeploy->name;
        for(int j=0;j<p.row[r]->length();j++)
        {
            p.row[r]->at(j)->index=j;
        }
        for(int j=0;j<another(p).row[r]->length();j++)
        {
            another(p).row[r]->at(j)->index=j;
        }
        QList<QJsonObject> objs;
        QJsonObject obj=p.curDeploy->deploy(p,another(p),r,i);
        QJsonObject obj1=cardsDropUpdate(name,obj,p.curDeploy);
        objs.append(obj);
        objs.append(obj1);
        QStringList datas;
        datas.append(QString::number(p.deck.length()));
        datas.append(QString::number(p.graveyard.length()));
        datas.append(QString::number(another(p).deck.length()));
        datas.append(QString::number(another(p).graveyard.length()));
        datas.append(QString::number(p.sumStrength()));
        datas.append(QString::number(another(p).sumStrength()));
        QJsonObject obj2=JDG.cmdStringList("refreshData",datas);
        objs.append(obj2);
        sendCMD(warp(JDG.cmds(objs),name));
        QList<QJsonObject> objs1;
        if(p.curDeploy->place==CardPlace::enAnywhere||p.curDeploy->place==CardPlace::en1||p.curDeploy->place==CardPlace::en2||p.curDeploy->place==CardPlace::en3)
        {
            objs1.append(JDG.cmdWarpAnother(JDG.cmdWarpEnOp(JDG.cmdEffectSingleton("dropCard",list,cardName))));
        }
        else
        {
            objs1.append(JDG.cmdWarpAnother(JDG.cmdWarpMyOp(JDG.cmdEffectSingleton("dropCard",list,cardName))));
        }
        objs1.append(JDG.cmdWarpAnother(obj));
        objs1.append(JDG.cmdWarpAnother(obj1));
        objs1.append(JDG.cmdWarpAnother(obj2));
        sendCMD(warp(JDG.cmds(objs1),anotherName(name)));
    }
    if(JDG.isCmdConfirm(cmd,"turn"))
    {
        Player &p=playerByName(name);
        QList<QJsonObject> objs;
        QJsonObject obj=playerUpdate(anotherName(name));
        QJsonObject obj1=cardsStartUpdate(anotherName(name));
        if(passed.length()<=0)
        {
            objs.append(JDG.cmdConfirm("turn"));
        }
        QStringList datas;
        datas.append(QString::number(another(p).deck.length()));
        datas.append(QString::number(another(p).graveyard.length()));
        datas.append(QString::number(p.deck.length()));
        datas.append(QString::number(p.graveyard.length()));
        datas.append(QString::number(another(p).sumStrength()));
        datas.append(QString::number(p.sumStrength()));
        JDG.removeKeyRecursive(obj,"end");
        JDG.removeKeyRecursive(obj1,"end");
        QJsonObject obj2=JDG.cmdStringList("refreshData",datas);
        objs.append(obj);
        objs.append(obj1);
        objs.append(obj2);
        sendCMD(warp(JDG.cmds(objs),anotherName(name)));
        QList<QJsonObject> aobjs;
        aobjs.append(obj);
        aobjs.append(obj1);
        aobjs.append(obj2);
        sendCMD(warp(JDG.cmdWarpAnother(JDG.cmds(aobjs)),name));
    }
}
//need to filter the same row
QJsonObject GameActor::playerUpdate(QString name)
{
    Player &plr=playerByName(name);
    QList<QJsonObject> objs;
    plr.fixInfo();
    another(plr).fixInfo();
    for(auto p:plr.weather)
    {
        if(p.second==Weather::frost)
        {

            QList<Card*> cards=seconds(plr.exTypeFilter(*plr.row[p.first],CardType::Gold));
            if(cards.length()>0)
            {
                Card* card=plr.getWeakestInList(cards);
                int extra=0;
                for(auto r:plr.weather)
                {
                    if(r.first==p.first&&r.second==Weather::frostPlus)
                    {
                        extra++;
                    }
                }
                objs.append(JDG.cmdWarpMyOp(card->effect(plr,another(plr),JDG.cmdSingleton("ordinaryHurt",QString::number(2+extra)),nullptr,0)));
            }

        }

        if(p.second==Weather::fog)
        {
            QList<Card*> cards=seconds(plr.exTypeFilter(*plr.row[p.first],CardType::Gold));
            if(cards.length()>0)
            {
                Card* card=plr.getStrongestInList(cards);
                objs.append(JDG.cmdWarpMyOp(card->effect(plr,another(plr),JDG.cmdSingleton("ordinaryHurt","2"),nullptr,0)));
            }
        }
        if(p.second==Weather::rain)
        {
            if(plr.row[p.first]->length()>=2)
            {
                QList<Card*> cards=plr.getRandomInList(*plr.row[p.first],2);
                objs.append(JDG.cmdWarpMyOp(cards[0]->effect(plr,another(plr),JDG.cmdSingleton("ordinaryHurt","1"),nullptr,0)));
                objs.append(JDG.cmdWarpMyOp(cards[1]->effect(plr,another(plr),JDG.cmdSingleton("ordinaryHurt","1"),nullptr,0)));
            }
            else
            {
                if(plr.row[p.first]->length()>0)
                {
                    Card* card=plr.row[p.first]->first();
                    objs.append(JDG.cmdWarpMyOp(card->effect(plr,another(plr),JDG.cmdSingleton("ordinaryHurt","1"),nullptr,0)));
                }
            }
        }
    }
    //remember to warp!!!
    return JDG.cmds(objs);
}

void GameActor::clear()
{
    player[0].clear();
    player[1].clear();
    passed.clear();
    winner.clear();
    replaceCount=0;
    curRound=0;
}

//means that this is my turn begining
QJsonObject GameActor::cardsStartUpdate(QString name)
{
    Player &me=playerByName(name);
    Player &en=another(me);
    me.fixInfo();
    en.fixInfo();
    QList<QJsonObject> objs;
    QList<Card*> mrow0=*me.row[0];
    QList<Card*> mrow1=*me.row[1];
    QList<Card*> mrow2=*me.row[2];
    QList<Card*> mhand=me.hand;
    QList<Card*> mdeck=me.deck;
    QList<Card*> mGrave=me.graveyard;
    for(auto p:mrow0)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myTurn","inRow"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:mrow1)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myTurn","inRow"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:mrow2)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myTurn","inRow"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:mhand)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myTurn","inHand"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:mdeck)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myTurn","inDeck"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:mGrave)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myTurn","inGraveyard"),JDG.cmdConfirm(("startUpdate"))));
    }

    QList<Card*> erow0=*en.row[0];
    QList<Card*> erow1=*en.row[1];
    QList<Card*> erow2=*en.row[2];
    QList<Card*> ehand=en.hand;
    QList<Card*> edeck=en.deck;
    QList<Card*> eGrave=en.graveyard;
    for(auto p:erow0)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyTurn","inRow"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:erow1)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyTurn","inRow"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:erow2)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyTurn","inRow"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:ehand)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyTurn","inHand"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:edeck)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyTurn","inDeck"),JDG.cmdConfirm(("startUpdate"))));
    }
    for(auto p:eGrave)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyTurn","inGraveyard"),JDG.cmdConfirm(("startUpdate"))));
    }
    return JDG.cmds(objs);
}

QJsonObject GameActor::cardsDropUpdate(QString name, const QJsonObject &feedback0,Card *curDeploy)
{
    Player &me=playerByName(name);
    QJsonObject feedback=JDG.cmdWarpPair(feedback0,"deployType",Card::typeToText(curDeploy->type));
    Player &en=another(me);
    me.fixInfo();
    en.fixInfo();
    QList<QJsonObject> objs;
    QList<Card*> mrow0=*me.row[0];
    QList<Card*> mrow1=*me.row[1];
    QList<Card*> mrow2=*me.row[2];
    QList<Card*> mhand=me.hand;
    QList<Card*> mdeck=me.deck;
    QList<Card*> mGrave=me.graveyard;
    for(auto p:mrow0)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myDrop","inRow"), feedback));
    }
    for(auto p:mrow1)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myDrop","inRow"),feedback));
    }
    for(auto p:mrow2)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myDrop","inRow"),feedback));
    }
    for(auto p:mhand)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myDrop","inHand"),feedback));
    }
    for(auto p:mdeck)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myDrop","inDeck"),feedback));
    }
    for(auto p:mGrave)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myDrop","inGraveyard"),feedback));
    }

    QList<Card*> erow0=*en.row[0];
    QList<Card*> erow1=*en.row[1];
    QList<Card*> erow2=*en.row[2];
    QList<Card*> ehand=en.hand;
    QList<Card*> edeck=en.deck;
    QList<Card*> eGrave=en.graveyard;
    for(auto p:erow0)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyDrop","inRow"),feedback));
    }
    for(auto p:erow1)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyDrop","inRow"),feedback));
    }
    for(auto p:erow2)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyDrop","inRow"),feedback));
    }
    for(auto p:ehand)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyDrop","inHand"),feedback));
    }
    for(auto p:edeck)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyDrop","inDeck"),feedback));
    }
    for(auto p:eGrave)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyDrop","inGraveyard"),feedback));
    }
    return JDG.cmds(objs);
}

//this is my feedback
QJsonObject GameActor::cardsFeedbackUpdate(QString name,const QJsonObject &feedback)
{
    Player &me=playerByName(name);
    Player &en=another(me);
    me.fixInfo();
    en.fixInfo();
    QList<QJsonObject> objs;
    QList<Card*> mrow0=*me.row[0];
    QList<Card*> mrow1=*me.row[1];
    QList<Card*> mrow2=*me.row[2];
    QList<Card*> mhand=me.hand;
    QList<Card*> mdeck=me.deck;
    QList<Card*> mGrave=me.graveyard;
    for(auto p:mrow0)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myFeedback","inRow"),feedback));
    }
    for(auto p:mrow1)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myFeedback","inRow"),feedback));
    }
    for(auto p:mrow2)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myFeedback","inRow"),feedback));
    }
    for(auto p:mhand)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myFeedback","inHand"),feedback));
    }
    for(auto p:mdeck)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myFeedback","inDeck"),feedback));
    }
    for(auto p:mGrave)
    {
        objs.append(p->update(me,en,JDG.cmdSingleton("myFeedback","inGraveyard"),feedback));
    }

    QList<Card*> erow0=*en.row[0];
    QList<Card*> erow1=*en.row[1];
    QList<Card*> erow2=*en.row[2];
    QList<Card*> ehand=en.hand;
    QList<Card*> edeck=en.deck;
    QList<Card*> eGrave=en.graveyard;
    for(auto p:erow0)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyFeedback","inRow"),feedback));
    }
    for(auto p:erow1)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyFeedback","inRow"),feedback));
    }
    for(auto p:erow2)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyFeedback","inRow"),feedback));
    }
    for(auto p:ehand)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyFeedback","inHand"),feedback));
    }
    for(auto p:edeck)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyFeedback","inDeck"),feedback));
    }
    for(auto p:eGrave)
    {
        objs.append(p->update(en,me,JDG.cmdSingleton("enemyFeedback","inGraveyard"),feedback));
    }
    return JDG.cmds(objs);
}
QString GameActor::anotherName(QString name)
{
    if(player[0].name==name)
        return player[1].name;
    else
        return player[0].name;
}

void GameActor::startRound()
{
    REtimer->stop();
    int limit=0;
    if(curRound==2)
    {
        limit=2;
    }
    if(curRound==3)
    {
        limit=1;
    }
    player[0].refresh();
    player[1].refresh();
    player[0].getToHand(limit);
    player[1].getToHand(limit);
    QStringList list0,list1;
    if(player[0].hand.length()<limit)
    {
        list0=Card::names(player[0].hand);
        list1=Card::names(player[1].hand);
    }
    else
    {
        list0=Card::names(player[0].hand.mid(player[0].hand.length()-limit,limit));
        list1=Card::names(player[1].hand.mid(player[1].hand.length()-limit,limit));
    }
    if(curRound==2)
    {
        list0.insert(0,"2");
        list1.insert(0,"2");
    }
    if(curRound==3)
    {
        list0.insert(0,"1");
        list1.insert(0,"1");
    }
    sendCMD(JDG.warpGameCMD(JDG.warpCMDbyName(JDG.GA(JDG.cmdStringList("startReplace",list0)),player[0].name)));
    sendCMD(JDG.warpGameCMD(JDG.warpCMDbyName(JDG.GA(JDG.cmdStringList("startReplace",list1)),player[1].name)));
}

Player &GameActor::another(const Player &p)
{
    if(player[0].name==p.name)
        return player[1];
    return player[0];
}

QJsonObject GameActor::warp(const QJsonObject &obj,QString name)
{
    return JDG.warpGameCMD(JDG.warpCMDbyName(JDG.GA(obj),name));
}

Player &GameActor::playerByName(QString name)
{
    if(player[0].name==name)
        return player[0];
    else
        return player[1];
}

QList<Card*> GameActor::stringToCards(QString str)
{
    QList<Card*> decks;
    QStringList list=decodeDeck(str);
    QStringList myOptions;
    myOptions << "tys" << "px" << "cgbs"<<"brnw"<<"qpdy"<<"sl"<<"zhhj"<<"bke"<<"jlt"<<"dg"
              <<"xwy"<<"ge"<<"seyn"<<"ly"<<"lwyzhu"<<"lwyzhi"<<"lwynn"<<"dsj"
             <<"klqs"<<"klxe"<<"wjz"<<"ayzz"<<"xzz"<<"xyrzs"<<"xzzjs"<<"ltys"<<"lb";
    for(auto p:list)
    {
        for(int i=0;i<C::cardsAvailable.length();i++)
        {
            if(C::cardsAvailable[i].getName()==p)
            {
                Card* card;
                switch (myOptions.indexOf(p)) {
                case 0:
                    card=new Earth();
                    break;
                case 1:
                    card=new Light();
                    break;
                case 2:
                    card=new Frost();
                    break;
                case 3:
                    card=new Fog();
                    break;
                case 4:
                    card=new Rain();
                    break;
                case 5:
                    card=new Lacerate();
                    break;
                case 6:
                    card=new Horn();
                    break;
                case 7:
                    card=new Mirror();
                    break;
                case 8:
                    card=new Lgni();
                    break;
                case 9:
                    card=new Dagon();
                    break;
                case 10:
                    card=new Foglet();
                    break;
                case 11:
                    card=new Geel();
                    break;
                case 12:
                    card=new CelHarpy();
                    break;
                case 13:
                    card=new WSpirit();
                    break;
                case 14:
                    card=new CroneBre();
                    break;
                case 15:
                    card=new CroneWea();
                    break;
                case 16:
                    card=new CroneWhi();
                    break;
                case 17:
                    card=new Arch();
                    break;
                case 18:
                    card=new WHRider();
                    break;
                case 19:
                    card=new Caranthir();
                    break;
                case 20:
                    card=new Frightener();
                    break;
                case 21:
                    card=new Elder();
                    break;
                case 22:
                    card=new Arachas();
                    break;
                case 23:
                    card=new VranWarrior();
                    break;
                case 24:
                    card=new ArachasBe();
                    break;
                case 25:
                    card=new ThPotion();
                    break;
                case 26:
                    card=new Roach();
                    break;
                default:
                    break;
                }
                decks.append(card);
                break;
            }
        }
    }
    return decks;
}

QString GameActor::stringFromCards(const QList<Card*> &cards)
{
    QStringList list;
    for(auto p:cards)
    {
        list.append(p->getName());
    }
    return encodeDeck(list);
}

void GameActor::initPlayer(QString name, QString deck)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int f=qrand()%2;

    if(player[f].name=="")
    {
        player[f].name=name;
        player[f].deck=stringToCards(deck);
        player[f].washCards();
        player[f].getToHand(10);
    }
    else
    {
        player[1-f].name=name;
        player[1-f].deck=stringToCards(deck);
        player[1-f].washCards();
        player[1-f].getToHand(10);
    }
    if(!(player[0].name=="")&&!(player[1].name==""))
    {
        QStringList list0=Card::names(player[0].hand);
        QStringList list1=Card::names(player[1].hand);
        if(curRound==1)
        {
            list0.insert(0,"3");
            list1.insert(0,"3");
        }
        sendCMD(JDG.warpGameCMD(JDG.warpCMDbyName(JDG.GA(JDG.cmdStringList("startReplace",list0)),player[0].name)));
        sendCMD(JDG.warpGameCMD(JDG.warpCMDbyName(JDG.GA(JDG.cmdStringList("startReplace",list1)),player[1].name)));
    }

}

QStringList GameActor::decodeDeck(QString deck)
{
    QStringList list;
    int d;
    for(int i=0;i<C::Holdable.length();i++)
    {
        d=deck.mid(i,1).toInt();
        while(d>=1)
        {
            d--;
            list.append(C::Holdable[i].getName());
        }
    }
    return list;
}

QString GameActor::encodeDeck(QStringList deck)
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

int GameActor::editCheck(QStringList names,QStringList types)
{
    if(names.length()<25)
        return 0;
    if(names.length()>40)
        return 2;
    int kc=0,gc=0,sc=0,cc=0;
    QList<int> count;
    for(int i=0;i<names.length();i++)
    {
        count.append(1);
        for(int j=0;j<i;j++)
        {
            if(names[j]==names[i])
                count[i]++;
        }
        if(types[i]=="King")
            kc++;
        if(types[i]=="Gold")
            gc++;
        if(types[i]=="Sliver")
            sc++;
        if(types[i]=="Copper")
            cc++;
    }
    if(kc>1)
        return 3;
    if(kc<1)
        return 4;
    if(gc>4)
        return 5;
    if(sc>6)
        return 6;
    for(int i=0;i<names.length();i++)
    {
        if(types[i]=="Gold"&&count[i]>1)
            return 7;
        if(types[i]=="Sliver"&&count[i]>1)
            return 8;
        if(types[i]=="Copper"&&count[i]>3)
            return 9;
    }
    return 1;
}

GameActor::GameActor(QObject *parent):QObject(parent)
{
    curRound=1;
    REtimer=new QTimer;
    connect(REtimer,SIGNAL(timeout()),this,SLOT(startRound()));
    replaceCount=0;
    curPlayer=0;
    Player p1,p2;
    p1.name="";
    p2.name="";
    player.append(p1);
    player.append(p2);
}

GameActor::~GameActor()
{

}


