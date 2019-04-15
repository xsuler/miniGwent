#include "graphactor.h"
#include<QDebug>

void GraphActor::startGA()
{
    emit start();
}

QString GraphActor::typeByName(QString name)
{
    return Card::typeToText(cardByName(name).type);
}

int GraphActor::strengthByName(QString name)
{
    return cardByName(name).strength;
}

QList<Card> GraphActor::cardsByNames(const QStringList &names)
{
    QList<Card> cards;
    for(auto r:names)
    {
        for(auto p:C::cardsAvailable)
        {
            if(p.name==r)
            {
                cards.append(p);
                break;
            }
        }
    }
    return cards;
}

QStringList GraphActor::getNamesFromCards(const QList<Card> &cards)
{
    QStringList types;
    for(auto p:cards)
    {
        types.append(p.name);
    }
    return types;
}

QStringList GraphActor::getTypesFromCards(const QList<Card> &cards)
{
    QStringList types;
    for(auto p:cards)
    {
        types.append(Card::typeToText(p.type));
    }
    return types;
}

QList<int> GraphActor::getStrengthsFromCards(const QList<Card> &cards)
{
    QList<int> types;
    for(auto p:cards)
    {
        types.append(p.strength);
    }
    return types;
}

Card GraphActor::cardByName(QString name)
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==name)
            return p;
    }
}

QString GraphActor::encodeDeck(const QStringList &deck)
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

QStringList GraphActor::decodeDeck(QString deck)
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

GraphActor::GraphActor(QObject *parent) : QObject(parent)
{
    {
        QFile file("data/cards");
        int i=0;
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            qDebug()<<"open cards error";
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if(line.length()>0)
            {
                realNames.insert(C::cardsAvailable[i].name,line);
                i++;
            }
        }
        file.close();
    }
    {
        QFile file("data/cardsDetail");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            qDebug()<<"open cardsDetail error";
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if(line.length()>0)
            {
                QList<QString> p=line.split('$');
                for(int i=0;i<p[1].length();i++)
                {
                    if(i%10==0)
                    {
                        p[1].insert(i,'\n');
                        i++;
                    }
                }
                Cardinfo.insert(p[0],p[1]);
            }
        }
        file.close();
    }
    names=slistToVlist(getNamesFromCards(C::cardsAvailable));
    types=slistToVlist(getTypesFromCards(C::cardsAvailable));
    strengths=slistToVlist(getStrengthsFromCards(C::cardsAvailable));
    connect(&NA,SIGNAL(loginRecv(int)),this,SLOT(loginRecv(int)));
    connect(&NA,SIGNAL(signupRecv(int)),this,SLOT(signupRecv(int)));
    connect(&NA,SIGNAL(userList(QMap<QString,QString>)),this,SLOT(userList(QMap<QString,QString>)));
    connect(&NA,SIGNAL(connectRequestNA(QString)),this,SLOT(connectRequestNA(QString)));
    connect(&NA,SIGNAL(connectConfirmNA(QString)),this,SLOT(connectConfirmNA(QString)));
    connect(&NA,SIGNAL(connectRefuseNA(QString)),this,SLOT(connectRefuseNA(QString)));
    connect(&NA,SIGNAL(cardList(QList<Card>,int)),this,SLOT(cardList(QList<Card>,int)));
    connect(&NA,SIGNAL(editConfirm(int)),this,SLOT(editConfirmNA(int)));
    connect(&NA,SIGNAL(deckData(QPair<QPair<QStringList,QStringList>,QString>)),this,SLOT(deckData(QPair<QPair<QStringList,QStringList>,QString>)));
    connect(&NA,SIGNAL(showReplace(QStringList,int)),this,SLOT(showReplaceNA(QStringList,int)));
    connect(&NA,SIGNAL(replaceTo(QString)),this,SLOT(replaceToNA(QString)));
    connect(&NA,SIGNAL(showTable(QStringList)),this,SLOT(showTableNA(QStringList)));
    connect(&NA,SIGNAL(useCard(QString)),this,SLOT(useCardNA(QString)));
    connect(&NA,SIGNAL(enemyDrop(QString,int,int,int,int)),this,SLOT(enemyDropNA(QString,int,int,int,int)));
    connect(&NA,SIGNAL(chooseSkill(QStringList)),this,SLOT(chooseSkillNA(QStringList)));
    connect(&NA,SIGNAL(appendHand(QString)),this,SLOT(appendHandNA(QString)));
    connect(&NA,SIGNAL(curDeckName(QString)),this,SLOT(curDeckNameNA(QString)));
    connect(&NA,SIGNAL(insertCard(QStringList,QVariantList,QVariantList,int)),this,SLOT(insertCardNA(QStringList,QVariantList,QVariantList,int)));
}

void GraphActor::loginRequest(QString name, QString psw)
{
    NA.login(name,psw);
}

void GraphActor::getMyRank()
{

}

void GraphActor::getUserOnline(int i)
{
    userListCMD=i;
    NA.getUserOnline();
}

QList<Card> GraphActor::stringToCards(QString str)
{
    QList<Card> decks;
    QStringList list=decodeDeck(str);
    for(auto p:list)
    {
        for(int i=0;i<C::cardsAvailable.length();i++)
        {
            if(C::cardsAvailable[i].getName()==p)
            {
                decks.append(C::cardsAvailable[i]);
                break;
            }
        }
    }
    return decks;
}

QString GraphActor::stringFromCards(const QList<Card> &cards)
{
    QStringList list;
    for(auto p:cards)
    {
        list.append(p.getName());
    }
    return encodeDeck(list);
}

void GraphActor::getUserElO()
{

}

void GraphActor::getDeck()
{
    NA.getDeck();
}

void GraphActor::loginRecv(int flag)
{
    emit loginRecvG(flag);
}

void GraphActor::signupRecv(int flag)
{
    emit signupRecvG(flag);
}

void GraphActor::userList(QMap<QString, QString> data)
{
    QList<QString> temp=data.keys();
    QVariantList list;
    for(auto p:temp)
    {
        list.append(QVariant::fromValue(p));
    }
    if(userListCMD==0)
        emit showUserList(list);
    else
        emit refreshUserList(list);
}

void GraphActor::connectRequestNA(QString name)
{
    if(curDeck.isEmpty())
        emit noDeck();
    else
        emit showConnectRequest(name);
}

void GraphActor::connectConfirmNA(QString name)
{
    emit showConnectConfirm(name);
}

void GraphActor::connectRefuseNA(QString name)
{
    emit showConnectRefuse(name);
}

void GraphActor::cardList(QList<Card> cards,int flag)
{
    names.clear();
    types.clear();
    strengths.clear();
    for(auto p:cards)
    {

        names.append(QVariant::fromValue(p.getName()));
        types.append(QVariant::fromValue(p.typeToText(p.getType())));
        strengths.append(QVariant::fromValue(p.getStrength()));
    }
    QStringList cnames;
    QList<Card> mcards;
    if(flag==1)
    {
        cnames=decodeDeck(*(curDeckList.find(curDeckName)));
        mcards=cardsByNames(cnames);
    }
    if(flag==0)
        emit showCardAvailable(names,types,strengths,flag,curDeckName,QVariantList(),QVariantList(),QVariantList());
    else
        emit showCardAvailable(names,types,strengths,flag,curDeckName,slistToVlist(cnames),slistToVlist(getTypesFromCards(mcards)),slistToVlist(getStrengthsFromCards(mcards)));
}

void GraphActor::editConfirmNA(int flag)
{
    emit editConfirm(flag);
}

void GraphActor::curDeckNameNA(QString name)
{
    curDeck=name;
}

void GraphActor::deckData(QPair<QPair<QStringList,QStringList>,QString> info)
{
    auto list=info.first;
    curDeck=info.second;
    curDeckList.clear();
    QVariantList vlist;
    for(int i=0;i<list.first.length();i++)
    {
        curDeckList.insert(list.first[i],list.second[i]);
        vlist.append(QVariant::fromValue(list.first[i]));
    }
    emit showDeckList(vlist,curDeck);
}

void GraphActor::showReplaceNA(QStringList hand,int limit)
{
    QList<Card> cards=cardsByNames(hand);
    emit showReplace(slistToVlist(hand),slistToVlist(getTypesFromCards(cards)),slistToVlist(getStrengthsFromCards(cards)),limit);
}

void GraphActor::replaceToNA(QString name)
{
    Card c=cardByName(name);
    emit replaceTo(name,Card::typeToText(c.type),c.strength);
}

void GraphActor::showTableNA(QStringList list)
{
    QStringList names=list.mid(2,list.length()-2);
    QList<Card> cards=cardsByNames(names);
    emit showTable(list[1].toInt(),list[0].toInt(),slistToVlist(names),slistToVlist(getTypesFromCards(cards)),slistToVlist(getStrengthsFromCards(cards)));
}

void GraphActor::useCardNA(QString name)
{
    Card card=cardByName(name);
    emit useCard(name,Card::typeToText(card.type),card.strength);
}

void GraphActor::enemyDropNA(QString name, int hand, int row, int index, int flag)
{
    emit enemyDrop(name,typeByName(name),strengthByName(name),hand,row,index,flag);
}

void GraphActor::chooseSkillNA(QStringList names)
{
    auto cards=cardsByNames(names);
    emit chooseSkill(slistToVlist(names),slistToVlist(getTypesFromCards(cards)),slistToVlist(getStrengthsFromCards(cards)));
}

void GraphActor::appendHandNA(QString name)
{
    emit appendHand(name,typeByName(name),strengthByName(name));
}

void GraphActor::insertCardNA(QStringList names, QVariantList rows, QVariantList indexs, int flag)
{
    auto cards=cardsByNames(names);
    emit insertCard(slistToVlist(names),slistToVlist(getTypesFromCards(cards)),slistToVlist(getStrengthsFromCards(cards)),rows,indexs,flag);
}

void GraphActor::connectRequest(QString name)
{
    NA.connectRequest(name);
}

void GraphActor::connectConfirm(QString name)
{
    NA.connectConfirm(name);
}

void GraphActor::connectRefuse(QString name)
{
    NA.connectRefuse(name);
}

void GraphActor::signupRequest(QString name, QString psw)
{
    NA.signupRequest(name,psw);
}

void GraphActor::showEditMode(int flag,QString name)
{
    curDeckName=name;
    NA.getCardList(flag);
}

QString GraphActor::getRealName(QString str)
{
    return *realNames.find(str);
}


void GraphActor::saveEdit(QVariantList name,QVariantList type,QString dname,int flag)
{
    QStringList strl;
    QStringList strl1;
    for(QVariant p:name)
    {
        strl.append(p.value<QString>());
    }
    for(QVariant p:type)
    {
        strl1.append(p.value<QString>());
    }
    NA.saveEdit(strl,strl1,dname,flag);
}

void GraphActor::showDeckInfo(QString name)
{
    QStringList deck=decodeDeck(*(curDeckList.find(name)));
    QVariantList vname;
    QVariantList vtype;
    QVariantList vstrength;
    for(auto p:deck)
    {
        vname.append(QVariant::fromValue(p));
        for(auto q:C::cardsAvailable)
        {
            if(q.getName()==p)
            {
                vtype.append(QVariant::fromValue(Card::typeToText(q.getType())));
                vstrength.append(QVariant::fromValue(q.getStrength()));
                break;
            }
        }
    }
    emit showDeckInfoG(vname,vtype,vstrength);
}

void GraphActor::recordDeck(QString str)
{
    curDeck=str;
    NA.recordDeck(curDeck);
}

QString GraphActor::getCurDeck()
{
    return curDeck;
}

void GraphActor::startConfirm(QString name)
{
    NA.startConfirm(name);
}

void GraphActor::replaceOne(int index)
{
    NA.replaceOne(index);
}

void GraphActor::changePlaceLimit(QString name)
{
    QList<int> me;
    QList<int> en;
    me.append(0);
    me.append(0);
    me.append(0);
    en.append(1);
    en.append(1);
    en.append(1);
    if(name==QString("tys"))
    {
        me[1]=1;
        me[2]=1;
    }
    if((name==QString("lwyzhi"))||(name==QString("lwyzhu"))||(name==QString("lwynn"))||(name==QString("xzzjs")))
    {
        me[1]=1;
        me[0]=1;
    }
    if(name==QString("xzz"))
    {
        me[0]=1;
        me[2]=1;
    }
    if(name==QString("wjz"))
    {
        me[0]=1;
        me[1]=1;
        me[2]=1;
        en[0]=0;
        en[1]=0;
        en[2]=0;
    }
    emit placeLimit(slistToVlist(me),slistToVlist(en));
}

void GraphActor::showCardInfo(QString name)
{
    QString det=*Cardinfo.find(name);
    emit showInfo(getRealName(name),det);
}

void GraphActor::close()
{
    NA.close();
}
