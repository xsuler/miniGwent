#include "cards.h"
#include"player.h"
#include"jsondatagen.h"


QJsonObject Earth::deploy(Player &me, Player &en,int r,int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    states.append(State::Shield);
    QList<RowPair> list;
    list.append(RowPair(RowInfo(-1,-1),RowInfo(r,i)));
    return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmdEffect("addShield",list)));
}

QJsonObject Earth::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Earth::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    if(JDG->hasChild(JDG->cmds(list),"destroyCard"))
    {
        Card* card=new LEarth;
        int ind=me.row[row]->length();
        me.insertIntoRow(RowInfo(row,ind),card);
        me.insertIntoRow(RowInfo(row,ind),new LEarth);
        QList<RowPair> infos;
        QStringList names;
        infos.append(RowPair(RowInfo(-1,-1),RowInfo(row,ind)));
        names.append("cjtys");
        infos.append(RowPair(RowInfo(-1,-1),RowInfo(row,ind)));
        names.append("cjtys");
        list.append(JDG->cmdWarpMyOp(JDG->cmdEffectWithS("insertCard",infos,names)));
        return JDG->cmds(list);
    }
    return JDG->cmds(list);
}

Earth::Earth()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("tys"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Light::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(me.row[row]->at(index)->effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
    QStringList list;
    list.append("qk");
    list.append("cz");
    objs.append(JDG->cmdStringList("chooseSkill",list));
    return JDG->cmds(objs);
}

QJsonObject Light::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Light::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Light::feedback(Player &me, Player &en ,const QJsonObject &obj)
{
    int mindex=JDG->deCmdSingleton(obj).toInt();
    if(mindex==0)
    {
        me.weather.clear();
        return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmdConfirm("clearWeather")));
    }
    else
    {
        auto cards=Player::typeFilter(me.deck,CardType::Copper);
        if(cards.length()==0)
            return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
        int d=qrand()%cards.length();
        me.deck.removeAt(cards[d].first);
        for(int i=0;i<me.deck.length();i++)
        {
            me.deck[i]->deckIndex=i;
        }
        me.curDeploy=cards[d].second;
        return JDG->cmdSingleton("useCard",me.curDeploy->name);
    }
}

Light::Light()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("px"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Frost::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(me.row[row]->at(index)->effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
    QList<RowPair> info;
    objs.append(JDG->cmdWarpMyOp(JDG->cmdEffect("ChooseOneOfEnemyRow",info)));
    return JDG->cmds(objs);
}

QJsonObject Frost::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Frost::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Frost::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    int index=JDG->deCmdSingleton(obj).toInt();
    en.clearWeatherInRow(index);
    en.weather.append(QPair<int,Weather>(index,Weather::frost));
    QStringList list;
    list.append("frost");
    list.append(QString::number(index));
    return JDG->cmdWarpEnd(JDG->cmdWarpEnOp(JDG->cmdStringList("showWeather",list)));
}

Frost::Frost()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("cgbs"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Fog::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(me.row[row]->at(index)->effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
    QList<RowPair> info;
    objs.append(JDG->cmdWarpMyOp(JDG->cmdEffect("ChooseOneOfEnemyRow",info)));
    return JDG->cmds(objs);
}

QJsonObject Fog::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Fog::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Fog::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    int index=JDG->deCmdSingleton(obj).toInt();
    en.clearWeatherInRow(index);
    en.weather.append(QPair<int,Weather>(index,Weather::fog));
    QStringList list;
    list.append("fog");
    list.append(QString::number(index));
    return JDG->cmdWarpEnd(JDG->cmdWarpEnOp(JDG->cmdStringList("showWeather",list)));
}

Fog::Fog()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("brnw"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Rain::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(me.row[row]->at(index)->effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
    QList<RowPair> info;
    objs.append(JDG->cmdWarpMyOp(JDG->cmdEffect("ChooseOneOfEnemyRow",info)));
    return JDG->cmds(objs);
}

QJsonObject Rain::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Rain::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Rain::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    int index=JDG->deCmdSingleton(obj).toInt();
    en.clearWeatherInRow(index);
    en.weather.append(QPair<int,Weather>(index,Weather::rain));
    QStringList list;
    list.append("rain");
    list.append(QString::number(index));
    return JDG->cmdWarpEnd(JDG->cmdWarpEnOp(JDG->cmdStringList("showWeather",list)));
}

Rain::Rain()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("qpdy"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Lacerate::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(me.row[row]->at(index)->effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
    QList<RowPair> info;
    objs.append(JDG->cmdWarpMyOp(JDG->cmdEffect("ChooseOneOfEnemyRow",info)));
    return JDG->cmds(objs);
}

QJsonObject Lacerate::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Lacerate::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Lacerate::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    int index=JDG->deCmdSingleton(obj).toInt();
    QList<QJsonObject> list;
    int l=en.row.at(index)->length();
    QList<Card*> cards;
    for(int i=0;i<l;i++)
    {
        cards.append(en.row.at(index)->at(i));
    }
    for(int i=0;i<l;i++)
    {
        list.append(JDG->cmdWarpEnOp(cards[i]->effect(en,me,JDG->cmdSingleton("difinitelyHurt","3"),this,0)));
    }
    return JDG->cmdWarpEnd(JDG->cmds(list));
}

Lacerate::Lacerate()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("sl"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Horn::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(me.row[row]->at(index)->effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
    if(me.allInRow()>0)
    {
        objs.append(JDG->cmdWarpMyOp(JDG->cmdConfirm("ChooseOneOfCard")));
        return JDG->cmds(objs);
    }
    else
    {
        return JDG->cmdWarpEnd(JDG->cmds(objs));
    }
}

QJsonObject Horn::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Horn::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}
//be careful with index change in a for circle
//means that you may need to build a container forwards
QJsonObject Horn::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    RowInfo info=JDG->deCmdSimpleEffect(obj).second;
    auto cards=me.row[info.first];
    QList<QJsonObject> objs;
    if(cards->length()<=5)
    {
        for(int i=0;i<cards->length();i++)
        {
            objs.append(cards->at(i)->effect(me,en,JDG->cmdSingleton("increase","4"),this,0));
        }
        return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmds(objs)));
    }
    else if(info.second>1)
    {
        for(int i=info.second-2;i<=info.second+2;i++)
        {
            objs.append(cards->at(i)->effect(me,en,JDG->cmdSingleton("increase","4"),this,0));
        }
        return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmds(objs)));
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            objs.append(cards->at(i)->effect(me,en,JDG->cmdSingleton("increase","4"),this,0));
        }
        return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmds(objs)));
    }
}

Horn::Horn()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("zhhj"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Mirror::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    int add=0;
    int gflag;
    int sflag;
    Card *sler;
    Card *lger;
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(me.row[row]->at(index)->effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
    int sum1=me.sumStrengthInRow(0)+me.sumStrengthInRow(1)+me.sumStrengthInRow(2);
    int sum2=en.sumStrengthInRow(0)+en.sumStrengthInRow(1)+en.sumStrengthInRow(2);
    if(sum1<=0&&sum2<=0)
    {
        return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
    }
    else if(sum1<=0)
    {
        sler=en.getWeakest();
        lger=en.getStrongest();
        sflag=1;
        gflag=1;
    }
    else if(sum2<=0)
    {
        sler=me.getWeakest();
        lger=me.getStrongest();
        sflag=0;
        gflag=0;
    }
    else
    {
        if(me.getWeakest()->curStrength<en.getWeakest()->curStrength)
        {
            sler=me.getWeakest();
            sflag=0;
        }
        else if(me.getWeakest()->curStrength==en.getWeakest()->curStrength)
        {
            int d=qrand()%2;
            if(d==0)
            {
                sler=en.getWeakest();
                sflag=1;
            }
            else
            {
                sler=me.getWeakest();
                sflag=0;
            }
        }
        else
        {
            sler=en.getWeakest();
            sflag=1;
        }

        if(me.getStrongest()->curStrength>en.getStrongest()->curStrength)
        {
            lger=me.getStrongest();
            gflag=0;
        }
        else if(me.getStrongest()->curStrength==en.getStrongest()->curStrength)
        {
            int d=qrand()%2;
            if(d==0)
            {
                lger=en.getStrongest();
                gflag=1;
            }
            else
            {
                lger=me.getStrongest();
                gflag=0;
            }
        }
        else
        {
            lger=en.getStrongest();
            gflag=1;
        }
    }
    if(lger->curStrength>10)
    {
        add=10;
    }
    else
    {
        add=lger->curStrength;
    }
    if(gflag==0)
    {
        objs.append(JDG->cmdWarpMyOp(lger->effect(me,en,JDG->cmdSingleton("directHurt","10"),this,0)));
    }
    else
    {
        objs.append(JDG->cmdWarpEnOp(lger->effect(en,me,JDG->cmdSingleton("directHurt","10"),this,0)));
    }
    if(sflag==0)
    {
        objs.append(JDG->cmdWarpMyOp(sler->effect(me,en,JDG->cmdSingleton("increase",QString::number(add)),this,0)));
    }
    else
    {
        objs.append(JDG->cmdWarpEnOp(sler->effect(en,me,JDG->cmdSingleton("increase",QString::number(add)),this,0)));
    }
    return JDG->cmdWarpEnd(JDG->cmds(objs));
}

QJsonObject Mirror::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Mirror::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

Mirror::Mirror()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("bke"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Lgni::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    int sum=en.sumStrengthInRow(row);
    if(sum<25)
    {
        return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
    }
    else
    {
        QList<QJsonObject> objs;
        Card* st=en.getStrongestInRow(row);
        //careful!! should use a container
        QList<Card*> cards=en.getContainerOfRow(row);
        int temp=st->curStrength;
        for(auto p:cards)
        {
            if(p->curStrength==temp)
            {
                objs.append(p->effect(en,me,JDG->cmdConfirm("destroy"),this,0));
            }
        }
        return JDG->cmdWarpEnd(JDG->cmdWarpEnOp(JDG->cmds(objs)));
    }
}

QJsonObject Lgni::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Lgni::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

Lgni::Lgni()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("jlt"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Dagon::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    QList<QJsonObject> objs;
    QStringList list;
    list.append("cgbs");
    list.append("brnw");
    list.append("qpdy");
    objs.append(JDG->cmdStringList("chooseSkill",list));
    return JDG->cmds(objs);
}

QJsonObject Dagon::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Dagon::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Dagon::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    int mindex=JDG->deCmdSingleton(obj).toInt();
    QList<RowPair> info;
    Card* newCard;
    if(mindex==0)
    {
        newCard=new Frost;
    }
    if(mindex==1)
    {
        newCard=new Fog;
    }
    if(mindex==2)
    {
        newCard=new Rain;
    }
    me.curDeploy=newCard;
    return JDG->cmdWarpMyOp(JDG->cmdEffect("ChooseOneOfEnemyRow",info));
}

Dagon::Dagon()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("dg"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Foglet::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    me.deployFlag=0;
    row=r;
    index=i;

    return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));

}

QJsonObject Foglet::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    if(JDG->isCmdSingleton(obj,"myTurn"))
    {
        QString txt=JDG->deCmdSingleton(obj);
        if(txt==QString("inRow"))
        {
            if(!me.containsWeather(Weather::fog)&&!en.containsWeather(Weather::fog))
            {
                return JDG->cmdWarpUpdate(JDG->cmdWarpMyOp(effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
            }
        }
    }
    if(JDG->isCmdSingleton(obj,"enemyTurn"))
    {
        QString txt=JDG->deCmdSingleton(obj);
        if(txt==QString("inRow"))
        {
            if(!me.containsWeather(Weather::fog)&&!en.containsWeather(Weather::fog))
            {
                return JDG->cmdWarpUpdate(JDG->cmdWarpEnOp(effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
            }
        }
    }
    if(JDG->isCmdSingleton(obj,"myFeedback"))
    {
        QString txt=JDG->deCmdSingleton(obj);
        if(txt==QString("inDeck"))
        {
            if(JDG->hasChild(info,"showWeather"))
            {
                if(!JDG->deStringListChild(info,"showWeather").contains("fog"))
                {
                    return JDG->cmdConfirm("Null");
                }
            }
            else
            {
                return JDG->cmdConfirm("Null");
            }
            if(me.deployFlag==1)
            {
                return JDG->cmdConfirm("Null");
            }
            me.deployFlag=1;
            me.deck.removeAt(deckIndex);
            for(int i=0;i<me.deck.length();i++)
            {
                me.deck[i]->deckIndex=i;
            }
            me.curDeploy=this;
            return JDG->cmdWarpUpdate(JDG->cmdSingleton("useCard",me.curDeploy->name));
        }
        if(txt==QString("inGraveyard"))
        {
            if(JDG->hasChild(info,"showWeather"))
            {
                if(!JDG->deStringListChild(info,"showWeather").contains("fog"))
                {
                    return JDG->cmdConfirm("Null");
                }
            }
            else
            {
                return JDG->cmdConfirm("Null");
            }
            if(me.deployFlag==1)
            {
                return JDG->cmdConfirm("Null");
            }
            me.deployFlag=1;
            me.graveyard.removeAt(graveIndex);
            for(int i=0;i<me.graveyard.length();i++)
            {
                me.graveyard[i]->graveIndex=i;
            }
            me.curDeploy=this;
            return JDG->cmdWarpUpdate(JDG->cmdSingleton("useCard",me.curDeploy->name));
        }
    }
    return JDG->cmdConfirm("Null");
}

QJsonObject Foglet::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

Foglet::Foglet()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("xwy"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Geel::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    count=0;
    QList<QJsonObject> objs;
    QStringList list;
    auto gCardsP=me.typeFilter(me.deck,CardType::Gold);
    auto sCardsP=me.typeFilter(me.deck,CardType::Sliver);
    auto gCards= Player::seconds(gCardsP);
    auto sCards= Player::seconds(sCardsP);
    auto gCardsI= Player::firsts(gCardsP);
    auto sCardsI= Player::firsts(sCardsP);
    if(gCards.length()>0)
    {
        list.append(gCards.first()->name);
        cards.append(gCards.first());
        indexs.append(gCardsI.first());
        count++;
    }
    if(sCards.length()>0)
    {
        list.append(sCards.first()->name);
        cards.append(sCards.first());
        indexs.append(sCardsI.first());
        count++;
    }
    if(count>0)
    {
        objs.append(JDG->cmdStringList("chooseSkill",list));
        return JDG->cmds(objs);
    }
    else
    {
        return JDG->cmdWarpEnd(JDG->cmdSingleton("error","no Gold or Sliver Card in deck"));
    }
}

QJsonObject Geel::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Geel::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Geel::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    int mindex=JDG->deCmdSingleton(obj).toInt();
    for(auto p:indexs)
    {
        me.removeFromDeck(p);
    }
    if(count>1)
    {
        if(mindex==0)
        {
            me.curDeploy=cards[0];
            me.insertIntoDeck(0,cards[1]);
            return JDG->cmdSingleton("useCard",me.curDeploy->name);
        }
        if(mindex==1)
        {
            me.curDeploy=cards[1];
            me.insertIntoDeck(0,cards[0]);
            return JDG->cmdSingleton("useCard",me.curDeploy->name);
        }
    }
    if(count>0)
    {
        me.curDeploy=cards[0];
        return JDG->cmdSingleton("useCard",me.curDeploy->name);
    }
    count=0;
    cards.clear();
    indexs.clear();
    return JDG->cmdWarpEnd(JDG->confirm("Null"));
}

Geel::Geel()
{
    count=0;
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("ge"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject CelHarpy::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    Card *card=new CelHarpyEgg;
    me.insertIntoRow(RowInfo(row,index),card);
    me.insertIntoRow(RowInfo(row,index),new CelHarpyEgg);
    QList<RowPair> infos;
    QStringList names;
    infos.append(RowPair(RowInfo(-1,-1),RowInfo(r,i)));
    names.append("ysnyd");
    infos.append(RowPair(RowInfo(-1,-1),RowInfo(r,i)));
    names.append("ysnyd");
    return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmdEffectWithS("insertCard",infos,names)));
}

QJsonObject CelHarpy::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject CelHarpy::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

CelHarpy::CelHarpy()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("seyn"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject CelHarpyEgg::deploy(Player &me, Player &en, int r, int i)
{
    row=r;
    index=i;
    return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
}

QJsonObject CelHarpyEgg::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject CelHarpyEgg::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    if(JDG->isCmdConfirm(obj,"eat"))
    {
        curStrength+=4;
    }
    list.append(eat(me,en,obj,sender,flag));
    if(JDG->hasChild(JDG->cmds(list),"destroyCard"))
    {
        int r=qrand()%3;
        int i=qrand()%(me.row[r]->length()+1);
        me.insertIntoRow(RowInfo(r,i),new CelHarpyBaby);
        QList<RowPair> infos;
        QStringList names;
        infos.append(RowPair(RowInfo(-1,-1),RowInfo(r,i)));
        names.append("ysnyyz");
        list.append(JDG->cmdEffectWithS("insertCard",infos,names));
    }
    return JDG->cmds(list);
}

CelHarpyEgg::CelHarpyEgg()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("ysnyd"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
    curStrength=strength;
    armor=0;
}

QJsonObject CelHarpyBaby::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
}

QJsonObject CelHarpyBaby::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject CelHarpyBaby::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

CelHarpyBaby::CelHarpyBaby()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("ysnyyz"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
    curStrength=strength;
    armor=0;
}

QJsonObject WSpirit::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    me.deployPending.append(new Wolf);
    me.deployPending.append(new Wolf);
    me.deployPending.append(new Wolf);
    me.curDeploy=me.deployPending.last();
    return JDG->cmdSingleton("useCard","bndl");
}

QJsonObject WSpirit::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject WSpirit::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

WSpirit::WSpirit()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("ly"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Wolf::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    me.deployPending.removeLast();
    if(me.deployPending.length()>0)
    {
        me.curDeploy=me.deployPending.last();
        return JDG->cmdSingleton("useCard","bndl");
    }
    return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
}

QJsonObject Wolf::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Wolf::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

Wolf::Wolf()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("bndl"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
    curStrength=strength;
    armor=0;
}

QJsonObject LEarth::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
}

QJsonObject LEarth::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject LEarth::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

LEarth::LEarth()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("cjtys"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
    curStrength=strength;
    armor=0;
}

QJsonObject CroneBre::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    if(me.deployPending.length()>0)
    {
        me.deployPending.removeLast();
        if(me.deployPending.length()==0)
        {
            return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
        }
        else
        {
            me.curDeploy=me.deployPending.last();
            return JDG->cmdSingleton("useCard",me.curDeploy->name);
        }
    }
    QList<int> indexs;
    for(int i=0;i<me.deck.length();i++)
    {
        if((me.deck[i]->name=="lwyzhi")||(me.deck[i]->name=="lwynn"))
        {
            me.deployPending.append(me.deck[i]);
            indexs.append(i);
        }
    }
    for(auto p:indexs)
    {
        me.removeFromDeck(p);
    }
    if(me.deployPending.length()>0)
    {
        me.curDeploy=me.deployPending.last();
        return JDG->cmdSingleton("useCard",me.curDeploy->name);
    }
    else
    {
        return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
    }
}

QJsonObject CroneBre::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject CroneBre::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

CroneBre::CroneBre()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("lwyzhu"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject CroneWea::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    if(me.deployPending.length()>0)
    {
        me.deployPending.removeLast();
        if(me.deployPending.length()==0)
        {
            return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
        }
        else
        {
            me.curDeploy=me.deployPending.last();
            return JDG->cmdSingleton("useCard",me.curDeploy->name);
        }
    }
    QList<int> indexs;
    for(int i=0;i<me.deck.length();i++)
    {
        if((me.deck[i]->name=="lwyzhu")||(me.deck[i]->name=="lwynn"))
        {
            me.deployPending.append(me.deck[i]);
            indexs.append(i);
        }
    }
    for(auto p:indexs)
    {
        me.removeFromDeck(p);
    }
    if(me.deployPending.length()>0)
    {
        me.curDeploy=me.deployPending.last();
        return JDG->cmdSingleton("useCard",me.curDeploy->name);
    }
    else
    {
        return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
    }
}

QJsonObject CroneWea::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject CroneWea::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

CroneWea::CroneWea()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("lwyzhi"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject CroneWhi::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    if(me.deployPending.length()>0)
    {
        me.deployPending.removeLast();
        if(me.deployPending.length()==0)
        {
            return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
        }
        else
        {
            me.curDeploy=me.deployPending.last();
            return JDG->cmdSingleton("useCard",me.curDeploy->name);
        }
    }
    QList<int> indexs;
    for(int i=0;i<me.deck.length();i++)
    {
        if((me.deck[i]->name=="lwyzhu")||(me.deck[i]->name=="lwyzhi"))
        {
            me.deployPending.append(me.deck[i]);
            indexs.append(i);
        }
    }
    for(auto p:indexs)
    {
        me.removeFromDeck(p);
    }
    if(me.deployPending.length()>0)
    {
        me.curDeploy=me.deployPending.last();
        return JDG->cmdSingleton("useCard",me.curDeploy->name);
    }
    else
    {
        return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
    }
}

QJsonObject CroneWhi::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject CroneWhi::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

CroneWhi::CroneWhi()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("lwynn"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject WHRider::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    en.weather.append(QPair<int,Weather>(r,Weather::frostPlus));
    return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
}

QJsonObject WHRider::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject WHRider::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    if(JDG->hasChild(JDG->cmds(list),"destroyCard"))
    {
        en.removeWeather(row,Weather::frostPlus);
    }
    return JDG->cmds(list);
}

WHRider::WHRider()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("klqs"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Caranthir::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    QList<RowPair> info;
    if(en.allInRow()>0)
        return JDG->cmdWarpEnOp(JDG->cmdEffect("ChooseOneOfCard",info));
    else
        return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
}

QJsonObject Caranthir::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Caranthir::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Caranthir::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    RowInfo info=JDG->deCmdSimpleEffect(obj).second;
    Card* card=en.row[info.first]->at(info.second);
    QList<QJsonObject> objs;
    int d=0;
    if(info.first!=row)
    {
        objs.append(JDG->cmdWarpEnOp(card->destroyJson()));
        QList<RowPair> infos;
        QStringList names;
        d=qrand()%(en.row[row]->length()+1);
        infos.append(RowPair(RowInfo(-1,-1),RowInfo(row,d)));
        names.append(card->name);
        objs.append(JDG->cmdWarpEnOp(JDG->cmdEffectWithS("insertCard",infos,names)));
        en.removeFromRow(info);
        en.insertIntoRow(RowInfo(row,d),card);
    }

    en.clearWeatherInRow(row);
    en.weather.append(QPair<int,Weather>(row,Weather::frost));
    QStringList list;
    list.append("frost");
    list.append(QString::number(row));
    objs.append(JDG->cmdWarpEnOp(JDG->cmdStringList("showWeather",list)));

    return JDG->cmdWarpEnd(JDG->cmds(objs));
}

Caranthir::Caranthir()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("klxe"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Frightener::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    Card* card=me.deck.first();
    me.removeFromDeck(0);
    me.hand.append(card);
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(JDG->cmdSingleton("appendHand",me.hand.last()->name)));
    if(en.allInRow()>en.row[r]->length())
        objs.append(JDG->cmdWarpEnOp(JDG->cmdEffect("ChooseOneOfCard",QList<RowPair>())));
    else
        return JDG->cmdWarpEnd(JDG->cmds(objs));
    return JDG->cmds(objs);
}

QJsonObject Frightener::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Frightener::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Frightener::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    RowInfo info=JDG->deCmdSimpleEffect(obj).second;
    Card* card=en.row[info.first]->at(info.second);
    QList<QJsonObject> objs;
    if(info.first==row)
    {
        if(en.allInRow()>en.row[row]->length())
            return JDG->cmdWarpEnOp(JDG->cmdEffect("ChooseOneOfCard",QList<RowPair>()));
        else
            return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
    }
    objs.append(JDG->cmdWarpEnOp(card->destroyJson()));
    QList<RowPair> infos;
    QStringList names;
    int d=qrand()%(en.row[row]->length()+1);
    infos.append(RowPair(RowInfo(-1,-1),RowInfo(row,d)));
    names.append(card->name);
    objs.append(JDG->cmdWarpEnOp(JDG->cmdEffectWithS("insertCard",infos,names)));

    en.removeFromRow(info);
    en.insertIntoRow(RowInfo(row,d),card);

    return JDG->cmdWarpEnd(JDG->cmds(objs));
}

Frightener::Frightener()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("wjz"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Elder::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    me.skillPendingCount=2;
    QList<RowPair> info;
    if(me.allInRow()>1)
    {
        return JDG->cmdWarpMyOp(JDG->cmdEffect("ChooseOneOfCard",info));
    }
    else
    {
        me.skillPendingCount=0;
        return JDG->cmdWarpEnd(JDG->confirm("Null"));
    }
}

QJsonObject Elder::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Elder::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject Elder::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    RowInfo info=JDG->deCmdSimpleEffect(obj).second;
    if(info==RowInfo(row,index))
    {
        QList<RowPair> infot;
        if(me.allInRow()>1)
        {
            return JDG->cmdWarpMyOp(JDG->cmdEffect("ChooseOneOfCard",infot));
        }
        else
        {
            me.skillPendingCount=0;
            return JDG->cmdWarpEnd(JDG->confirm("Null"));
        }
    }
    Card* card=me.row[info.first]->at(info.second);

    QList<QJsonObject> objs;
    QJsonObject aobj=card->effect(me,en,JDG->cmdConfirm("eat"),this,0);
    objs.append(JDG->cmdWarpMyOp(aobj));

    if(me.skillPendingCount>0)
    {
        QList<RowPair> infot;
        if(me.allInRow()>1)
        {
            objs.append(JDG->cmdEffect("ChooseOneOfCard",infot));
        }
        else
        {
            me.skillPendingCount=0;
            return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmds(objs)));
        }
        me.skillPendingCount--;
        return JDG->cmdWarpMyOp(JDG->cmds(objs));
    }
    return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmds(objs)));
}

Elder::Elder()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("ayzz"))
        {
            this->name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Arachas::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    if(me.deployPending.length()>0)
    {
        me.deployPending.removeLast();
        if(me.deployPending.length()==0)
        {
            return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
        }
        else
        {
            me.curDeploy=me.deployPending.last();
            return JDG->cmdSingleton("useCard",me.curDeploy->name);
        }
    }
    QList<int> indexs;
    for(int i=0;i<me.deck.length();i++)
    {
        if((me.deck[i]->name=="xzz"))
        {
            me.deployPending.append(me.deck[i]);
            indexs.append(i);
        }
    }
    for(auto p:indexs)
    {
        me.removeFromDeck(p);
    }
    if(me.deployPending.length()>0)
    {
        me.curDeploy=me.deployPending.last();
        return JDG->cmdSingleton("useCard",me.curDeploy->name);
    }
    else
    {
        return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
    }
}

QJsonObject Arachas::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Arachas::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

Arachas::Arachas()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("xzz"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject VranWarrior::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    eatFlag=1;
    if(me.row[r]->length()-1>index)
    {
        return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(me.row[r]->at(index+1)->effect(me,en,JDG->cmdConfirm("eat"),this,0)));
    }
    return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
}

QJsonObject VranWarrior::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    if(JDG->isCmdSingleton(obj,"myTurn"))
    {
        QString txt=JDG->deCmdSingleton(obj);
        if(txt==QString("inRow"))
        {
            if(eatFlag==1)
            {
                eatFlag=0;
            }
            else
            {
                if(me.row[row]->length()-1>index)
                {
                    return JDG->cmdWarpUpdate(JDG->cmdWarpMyOp(me.row[row]->at(index+1)->effect(me,en,JDG->cmdConfirm("eat"),this,0)));
                }
                eatFlag=1;
            }
        }
    }
    return JDG->cmdConfirm("Null");
}

QJsonObject VranWarrior::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

VranWarrior::VranWarrior()
{
    eatFlag=0;
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("xyrzs"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject ArachasBe::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=2;
    row=r;
    index=i;
    return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmdSimpleEffectWithD("updateArmor",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(armor))));
}

QJsonObject ArachasBe::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    QList<QJsonObject> objs;
    if(JDG->isCmdSingleton(obj,"myFeedback")||JDG->isCmdSingleton(obj,"myTurn")||JDG->isCmdSingleton(obj,"myDrop"))
    {
        QString txt=JDG->deCmdSingleton(obj);
        if(txt==QString("inRow"))
        {
            if(JDG->hasKey(info,"ate"))
            {
                int r=qrand()%3;
                int i=qrand()%(me.row[r]->length()+1);
                QList<RowPair> infos;
                QStringList names;
                infos.append(RowPair(RowInfo(-1,-1),RowInfo(r,i)));
                names.append("xzzyc");
                me.insertIntoRow(RowInfo(r,i),new ArachasBaby);
                objs.append(JDG->cmdWarpUpdate(JDG->cmdWarpMyOp(JDG->cmdEffectWithS("insertCard",infos,names))));
                objs.append(JDG->cmdWarpUpdate(JDG->cmdWarpMyOp(effect(me,en,JDG->cmdSingleton("directHurt","1"),this,0))));
                return JDG->cmds(objs);
            }
        }
    }
    return JDG->cmdConfirm("Null");
}

QJsonObject ArachasBe::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

ArachasBe::ArachasBe()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("xzzjs"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}


QJsonObject ArachasBaby::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    return JDG->cmdConfirm("Null");
}

QJsonObject ArachasBaby::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject ArachasBaby::effect(Player &me, Player &en, const QJsonObject &obj, Card *sender, int flag)
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

ArachasBaby::ArachasBaby()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("dsj"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
    curStrength=strength;
    armor=0;
}


QJsonObject ThPotion::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(me.row[row]->at(index)->effect(me,en,JDG->cmdConfirm("destroy"),this,0)));
    if(me.allInRow()>0)
    {
        objs.append(JDG->cmdWarpMyOp(JDG->cmdConfirm("ChooseOneOfCard")));
        return JDG->cmds(objs);
    }
    else
    {
        return JDG->cmdWarpEnd(JDG->cmds(objs));
    }
}

QJsonObject ThPotion::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject ThPotion::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

QJsonObject ThPotion::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    RowInfo info=JDG->deCmdSimpleEffect(obj).second;
    auto cards=me.row[info.first];
    QList<QJsonObject> objs;
    if(cards->length()<=3)
    {
        for(int i=0;i<cards->length();i++)
        {
            objs.append(cards->at(i)->effect(me,en,JDG->cmdSingleton("increase","3"),this,0));
            cards->at(i)->armor+=2;
            objs.append(JDG->cmdSimpleEffectWithD("updateArmor",RowPair(RowInfo(-1,-1),RowInfo(cards->at(i)->row,cards->at(i)->index)),QString::number(cards->at(i)->armor)));
        }
        return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmds(objs)));
    }
    else if(info.second>0)
    {
        for(int i=info.second-1;i<=info.second+1;i++)
        {
            objs.append(cards->at(i)->effect(me,en,JDG->cmdSingleton("increase","3"),this,0));
            cards->at(i)->armor+=2;
            objs.append(JDG->cmdSimpleEffectWithD("updateArmor",RowPair(RowInfo(-1,-1),RowInfo(cards->at(i)->row,cards->at(i)->index)),QString::number(cards->at(i)->armor)));
        }
        return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmds(objs)));
    }
    else
    {
        for(int i=0;i<3;i++)
        {
            objs.append(cards->at(i)->effect(me,en,JDG->cmdSingleton("increase","3"),this,0));
            cards->at(i)->armor+=2;
            objs.append(JDG->cmdSimpleEffectWithD("updateArmor",RowPair(RowInfo(-1,-1),RowInfo(cards->at(i)->row,cards->at(i)->index)),QString::number(cards->at(i)->armor)));
        }
        return JDG->cmdWarpEnd(JDG->cmdWarpMyOp(JDG->cmds(objs)));
    }
}

ThPotion::ThPotion()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("ltys"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}

QJsonObject Roach::deploy(Player &me, Player &en, int r, int i)
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
}

QJsonObject Roach::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    if(JDG->isCmdSingleton(obj,"myDrop"))
    {
        QString txt=JDG->deCmdSingleton(obj);
        if(txt==QString("inDeck"))
        {
            if(JDG->hasKey(info,"deployType"))
            {
                QStringList list=JDG->deCmdKeyRecursive(info,"deployType");
                if(list.length()<=0)
                {
                    return JDG->cmdConfirm("Null");
                }
                int flag=0;
                for(auto p:list)
                {
                    if(p==QString("Gold"))
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    int r=qrand()%3;
                    int i=qrand()%(me.row[r]->length()+1);
                    QList<RowPair> infos;
                    QStringList names;
                    infos.append(RowPair(RowInfo(-1,-1),RowInfo(r,i)));
                    names.append("lb");
                    me.removeFromDeck(deckIndex);
                    me.insertIntoRow(RowInfo(r,i),this);
                    return JDG->cmdWarpUpdate(JDG->cmdWarpMyOp(JDG->cmdEffectWithS("insertCard",infos,names)));
                }
            }
        }
    }
    return JDG->cmdConfirm("Null");
}

QJsonObject Roach::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

Roach::Roach()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("lb"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
    curStrength=strength;
    armor=0;
}

QJsonObject Arch::deploy(Player &me, Player &en, int r, int i)//todo
{
    curStrength=strength;
    armor=0;
    row=r;
    index=i;
    me.clearWeatherInRow(row);
    QList<QJsonObject> objs;
    objs.append(JDG->cmdWarpMyOp(JDG->cmdSingleton("eraseWeather",QString::number(row))));
    return JDG->cmdWarpEnd(JDG->cmdConfirm("Null"));
}

QJsonObject Arch::update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Arch::effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag )
{
    QList<QJsonObject> list;
    list.append(hurts(me,en,obj));
    list.append(increase(me,en,obj));
    list.append(eat(me,en,obj,sender,flag));
    return JDG->cmds(list);
}

Arch::Arch()
{
    for(auto p:C::cardsAvailable)
    {
        if(p.name==QString("dsj"))
        {
            name=p.name;
            type=p.type;
            place=p.place;
            attr=p.attr;
            strength=p.strength;
            break;
        }
    }
}


