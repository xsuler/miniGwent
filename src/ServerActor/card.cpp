#include "card.h"
#include"jsondatagen.h"
#include"player.h"
#include<QFile>
#include<QDebug>

QList<Card> C::cardsAvailable=Card::parseCards();
QList<Card> C::Holdable=Card::getHoldable();

QList<Card> Card::parseCards()
{
    QFile file("data/cardinfo");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        qDebug()<<"open cardinfo error";
    QTextStream in(&file);
    QList<Card> cards;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list=line.split(' ');
        if(list.length()<5)
            continue;
        Card card(list.at(0),Card::typeFromText(list.at(1)),Card::placeFromText(list.at(3)),Card::attrFromText(list.at(4)),list.at(2).toInt());
        cards.append(card);
    }
    file.close();
    return cards;
}

QList<Card> Card::getHoldable()
{
    QFile file("data/holdable");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        qDebug()<<"open cardinfo error";
    QTextStream in(&file);
    QList<Card> cards;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list=line.split(' ');
        if(list.length()<5)
            continue;
        Card card(list.at(0),Card::typeFromText(list.at(1)),Card::placeFromText(list.at(3)),Card::attrFromText(list.at(4)),list.at(2).toInt());
        cards.append(card);
    }
    file.close();
    return cards;
}

QString Card::getName()
{
    return name;
}

void Card::eraseState(State st)
{
    for(int i=0;i<states.length();i++)
    {
        if(states[i]==st)
        {
            states.removeAt(i);
        }
    }
}

bool Card::hasState(State st)
{
    return states.contains(st);
}

CardType Card::getType()
{
    return type;
}

CardPlace Card::getPlace()
{
    return place;
}

CardAttr Card::getAttr()
{
    return attr;
}

int Card::getStrength()
{
    return strength;
}

QJsonObject Card::destroyJson()
{
    QList<RowPair> rows;
    rows.append(RowPair(RowInfo(-1,-1),RowInfo(row,index)));
    return JDG->cmdEffect("destroyCard",rows);
}

QJsonObject Card::increase(Player &me, Player &en, const QJsonObject &obj)
{
    int x=JDG->deCmdSingleton(obj).toInt();
    if(JDG->isCmdSingleton(obj,"increase"))
    {
        curStrength+=x;
        return JDG->cmdSimpleEffectWithD("updateStrength",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(curStrength));
    }
    else
    {
        return JDG->cmdConfirm("Null");
    }
}


QJsonObject Card::hurts(Player &me, Player &en, const QJsonObject &obj)
{
    int x=JDG->deCmdSingleton(obj).toInt();
    //directHurt means ignorance of anmor
    if(JDG->isCmdSingleton(obj,"directHurt"))
    {
        if(curStrength<=x)
        {
            curStrength=0;
            me.moveToGraveyard(RowInfo(row,index));
            return destroyJson();
        }
        else
        {
            curStrength-=x;
            return JDG->cmdSimpleEffectWithD("updateStrength",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(curStrength));
        }
    }
    if(JDG->isCmdConfirm(obj,"destroy"))
    {
        curStrength=0;
        me.moveToGraveyard(RowInfo(row,index));
        return destroyJson();
    }
    if(JDG->isCmdSingleton(obj,"ordinaryHurt"))
    {
        if(type==CardType::Gold)
        {
            return JDG->cmdConfirm("Null");
        }
        if(hasState(State::Shield))
        {
            eraseState(State::Shield);
            return JDG->cmdSimpleEffect("eraseShield",RowPair(RowInfo(-1,-1),RowInfo(row,index)));
        }
        if(armor<=0)
        {
            if(curStrength<=x)
            {
                curStrength=0;
                me.moveToGraveyard(RowInfo(row,index));
                return destroyJson();
            }
            else
            {
                curStrength-=x;
                return JDG->cmdSimpleEffectWithD("updateStrength",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(curStrength));
            }
        }
        else
        {
            if(armor>x)
            {
                armor-=x;
                return JDG->cmdSimpleEffectWithD("updateArmor",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(armor));
            }
            else
            {
                QList<QJsonObject> objs;
                armor=0;
                x-=armor;
                objs.append(JDG->cmdSimpleEffectWithD("updateArmor",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(armor)));
                if(curStrength<=x)
                {
                    curStrength=0;
                    me.moveToGraveyard(RowInfo(row,index));
                    return destroyJson();
                }
                else
                {
                    curStrength-=x;
                    objs.append(JDG->cmdSimpleEffectWithD("updateStrength",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(curStrength)));
                }
                return JDG->cmds(objs);
            }
        }

    }
    //difinitely means ignoring Gold and Sliver
    if(JDG->isCmdSingleton(obj,"difinitelyHurt"))
    {
        if(hasState(State::Shield))
        {
            eraseState(State::Shield);
            return JDG->cmdSimpleEffect("eraseShield",RowPair(RowInfo(-1,-1),RowInfo(row,index)));
        }
        if(armor<=0)
        {
            if(curStrength<=x)
            {
                curStrength=0;
                me.moveToGraveyard(RowInfo(row,index));
                return destroyJson();
            }
            else
            {
                curStrength-=x;
                return JDG->cmdSimpleEffectWithD("updateStrength",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(curStrength));
            }
        }
        else
        {
            if(armor>x)
            {
                armor-=x;
                return JDG->cmdSimpleEffectWithD("updateArmor",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(armor));
            }
            else
            {
                QList<QJsonObject> objs;
                armor=0;
                x-=armor;
                objs.append(JDG->cmdSimpleEffectWithD("updateArmor",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(armor)));
                if(curStrength<=x)
                {
                    curStrength=0;
                    me.moveToGraveyard(RowInfo(row,index));
                    return destroyJson();
                }
                else
                {
                    curStrength-=x;
                    objs.append(JDG->cmdSimpleEffectWithD("updateStrength",RowPair(RowInfo(-1,-1),RowInfo(row,index)),QString::number(curStrength)));
                }
                return JDG->cmds(objs);
            }
        }

    }
    return JDG->cmdConfirm("Null");
}

QJsonObject Card::eat(Player &me, Player &en, const QJsonObject &obj,Card *sender,int flag)
{
    if(JDG->isCmdConfirm(obj,"eat"))
    {
        QList<QJsonObject> objs;
        if(flag==0)
        {
            me.row[sender->row]->at(sender->index)->curStrength+=curStrength;
            curStrength=0;
            me.moveToGraveyard(RowInfo(row,index));
            objs.append(JDG->cmdWarpKey(destroyJson(),"ate"));
            objs.append(JDG->cmdSimpleEffectWithD("updateStrength",RowPair(RowInfo(-1,-1),RowInfo(sender->row,sender->index)),QString::number(me.row[sender->row]->at(sender->index)->curStrength)));
            return JDG->cmds(objs);
        }
        else
        {
            en.row[sender->row]->at(sender->index)->curStrength+=curStrength;
            curStrength=0;
            en.moveToGraveyard(RowInfo(row,index));
            objs.append(JDG->cmdWarpKey(destroyJson(),"ate"));
            objs.append(JDG->cmdSimpleEffectWithD("updateStrength",RowPair(RowInfo(-1,-1),RowInfo(sender->row,sender->index)),QString::number(en.row[sender->row]->at(sender->index)->curStrength)));
            return JDG->cmds(objs);
        }
    }
    return JDG->cmdConfirm("Null");
}

QJsonObject Card::deploy(Player &me,Player &en,int row,int index)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Card::update(Player &me, Player &en, const QJsonObject &obj,const QJsonObject &info)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Card::feedback(Player &me, Player &en, const QJsonObject &obj)
{
    return JDG->cmdConfirm("Null");
}

QJsonObject Card::effect(Player &me, Player &en, const QJsonObject &obj,Card* sender,int flag)
{
    return JDG->cmdConfirm("Null");
}

QStringList Card::names(const QList<Card *> list)
{
    QStringList res;
    for(auto p:list)
    {
        res.append(p->name);
    }
    return res;
}

QJsonObject Card::rowInfoToJson(const RowInfo &info)
{
    QJsonObject obj;
    obj["row"]=info.first;
    obj["index"]=info.second;
    return obj;
}

RowInfo Card::rowInfoFromJson(const QJsonObject &obj)
{
    RowInfo info;
    info.first=obj["row"].toInt();
    info.second=obj["index"].toInt();
    return info;
}

CardType Card::typeFromText(QString s)
{
    QStringList myOptions;
    myOptions << "King" << "Gold" << "Sliver"<<"Copper";
    switch (myOptions.indexOf(s))
    {
    case 0:
        return CardType::King;
    case 1:
        return CardType::Gold;
    case 2:
        return CardType::Sliver;
    case 3:
        return CardType::Copper;
    }
    switch (s.toInt()) {
    case 0:
        return CardType::King;
    case 1:
        return CardType::Gold;
    case 2:
        return CardType::Sliver;
    case 3:
        return CardType::Copper;
    default:
        return CardType::TError;
    }

}

CardPlace Card::placeFromText(QString s)
{
    QStringList myOptions;
    myOptions << "myAnywhere" << "enAnywhere" << "my1"<<"my2"<<"my3"<<"en1"<<"en2"<<"en3";
    switch (myOptions.indexOf(s))
    {
    case 0:
        return CardPlace::myAnywhere;
    case 1:
        return CardPlace::enAnywhere;
    case 2:
        return CardPlace::my1;
    case 3:
        return CardPlace::my2;
    case 4:
        return CardPlace::my3;
    case 5:
        return CardPlace::en1;
    case 6:
        return CardPlace::en2;
    case 7:
        return CardPlace::en3;

    }
    switch (s.toInt()) {
    case -1:
        return CardPlace::myAnywhere;
    case -2:
        return CardPlace::enAnywhere;
    case 1:
        return CardPlace::my1;
    case 2:
        return CardPlace::my2;
    case 3:
        return CardPlace::my3;
    case 4:
        return CardPlace::en1;
    case 5:
        return CardPlace::en2;
    case 6:
        return CardPlace::en3;
    default:
        return CardPlace::PError;
    }

}

CardAttr Card::attrFromText(QString s)
{
    QStringList myOptions;
    myOptions << "Lost" << "Plain";
    switch (myOptions.indexOf(s))
    {
    case 0:
        return CardAttr::Lost;
    case 1:
        return CardAttr::Plain;
    }
    switch (s.toInt()) {
    case 1:
        return CardAttr::Lost;
    case 0:
        return CardAttr::Plain;
    default:
        return CardAttr::AError;
    }

}

QString Card::typeToText(CardType s)
{
    switch (s) {
    case CardType::King:
        return "King";
    case CardType::Gold:
        return "Gold";
    case CardType::Sliver:
        return "Sliver";
    case CardType::Copper:
        return "Copper";
    default:
        return "TError";
    }
}

QString Card::placeToText(CardPlace s)
{
    switch (s) {
    case CardPlace::myAnywhere:
        return "myAnywhere";
    case CardPlace::enAnywhere:
        return "enAnywhere";
    case CardPlace::my1:
        return "my1";
    case CardPlace::my2:
        return "my2";
    case CardPlace::my3:
        return "my3";
    case CardPlace::en1:
        return "en1";
    case CardPlace::en2:
        return "en2";
    case CardPlace::en3:
        return "en3";
    default:
        return "PError";
    }
}

QString Card::attrToText(CardAttr s)
{
    switch (s) {
    case CardAttr::Plain:
        return "Plain";
    case CardAttr::Lost:
        return "Lost";
    default:
        return "AError";
    }
}

