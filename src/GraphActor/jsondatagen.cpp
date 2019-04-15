#include "jsondatagen.h"

QJsonObject JsonDataGen::loginRecv(int flag)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="loginRecv";
    obj["info"]=flag;
    return obj;
}

bool JsonDataGen::isLoginRecv(const QJsonObject &obj)
{
    return obj["type"]=="command"&&obj["content"]=="loginRecv";
}

int JsonDataGen::deLoginRecv(const QJsonObject &obj)
{
    return obj["info"].toInt();
}

QJsonObject JsonDataGen::userList(const QList<QVariant> &datas)
{
    QJsonObject list;
    list["type"]="data";
    list["content"]="userOnline";
    QJsonArray array;
    for(QVariant p:datas)
    {
        array.append(p.value<UserMeta>().toJson());
    }
    list["info"]=array;
    return list;
}

bool JsonDataGen::isUserList(const QJsonObject &obj)
{
    return (obj["type"]=="data")&&(obj["content"]=="userOnline");
}

QMap<QString,QString> JsonDataGen::deUserList(const QJsonObject &obj)
{
    if(!isUserList(obj))
        return QMap<QString,QString>();
    QJsonArray list=obj["info"].toArray();
    QMap<QString,QString> res;
    QPair<QString,QString> temp;
    for(int i=0;i<list.size();i++)
    {
        temp=UserMeta::fromJson(list[i].toObject());
        res.insert(temp.first,temp.second);
    }
    return res;
}

QJsonObject JsonDataGen::connectRequest(QString name)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="connectRequest";
    obj["info"]=name;
    return obj;
}

bool JsonDataGen::isConnectRequest(const QJsonObject &obj)
{
    return (obj["type"]=="command")&&(obj["content"]=="connectRequest");
}

QString JsonDataGen::deConnectRequest(const QJsonObject &obj)
{
    return obj["info"].toString();
}

bool JsonDataGen::isDeckData(const QJsonObject &obj)
{
    return (obj["type"]=="command")&&(obj["content"]=="deckData");
}

QPair<QPair<QStringList,QStringList>,QString> JsonDataGen::deDeckData(const QJsonObject &obj)
{
    QJsonArray array;
    array=obj["info"].toArray();
    QStringList names;
    QStringList cards;
    for(int i=0;i<array.size();i++)
    {
        QJsonObject aobj=array[i].toObject();
        names.append(aobj["name"].toString());
        cards.append(aobj["cards"].toString());
    }
    return QPair<QPair<QStringList,QStringList>,QString>(QPair<QStringList,QStringList>(names,cards),obj["curDeck"].toString());
}

QJsonObject JsonDataGen::deckData(QStringList names, QStringList cards,QString cur)
{
    QJsonObject list;
    list["type"]="command";
    list["content"]="deckData";
    QJsonArray array;
    for(int i=0;i<names.length();i++)
    {
        QJsonObject aobj;
        aobj["name"]=names[i];
        aobj["cards"]=cards[i];
        array.append(aobj);
    }
    list["curDeck"]=cur;
    list["info"]=array;
    return list;
}

QJsonObject JsonDataGen::connectConfirm(QString name)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="connectConfirm";
    obj["info"]=name;
    return obj;
}

bool JsonDataGen::isConnectConfirm(const QJsonObject &obj)
{
    return (obj["type"]=="command")&&(obj["content"]=="connectConfirm");
}

QString JsonDataGen::deConnectConfirm(const QJsonObject &obj)
{
    return obj["info"].toString();
}

QJsonObject JsonDataGen::connectRefuse(QString name)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="connectRefuse";
    obj["info"]=name;
    return obj;
}

bool JsonDataGen::isConnectRefuse(const QJsonObject &obj)
{
    return (obj["type"]=="command")&&(obj["content"]=="connectRefuse");
}

QString JsonDataGen::deConnectRefuse(const QJsonObject &obj)
{
    return obj["info"].toString();
}

QJsonObject JsonDataGen::signupInfo(QString name, QString psw)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="signup";
    QJsonArray users;
    QJsonObject user;
    user["name"]=name;
    user["password"]=psw;
    users.append(user);
    obj["info"]=users;
    return obj;
}

bool JsonDataGen::isSignupInfo(const QJsonObject &obj)
{
    return (obj["type"]=="command")&&(obj["content"]=="signup");
}

QPair<QString, QString> JsonDataGen::deSignupInfo(const QJsonObject &obj)
{
    QJsonArray array=obj["info"].toArray();
    QJsonObject objt= array[0].toObject();
    return QPair<QString,QString>(objt["name"].toString(),objt["password"].toString());
}

QJsonObject JsonDataGen::signupRecv(int flag)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="signupRecv";
    obj["info"]=flag;
    return obj;
}

bool JsonDataGen::isSignupRecv(const QJsonObject &obj)
{
    return obj["type"]=="command"&&obj["content"]=="signupRecv";
}

int JsonDataGen::deSignupRecv(const QJsonObject &obj)
{
    return  obj["info"].toInt();
}

QJsonObject JsonDataGen::cardList(QList<Card> cards)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="CardList";
    QJsonArray array;
    for(auto p:cards)
    {
        QJsonObject aobj;
        aobj["name"]=p.getName();
        aobj["type"]=Card::typeToText(p.getType());
        aobj["place"]=Card::placeToText(p.getPlace());
        aobj["attr"]=Card::attrToText(p.getAttr());
        aobj["strength"]=p.getStrength();
        array.append(aobj);
    }
    obj["info"]=array;
    return obj;
}

bool JsonDataGen::isCardList(const QJsonObject &obj)
{
    return (obj["type"]=="command")&&(obj["content"]=="CardList");
}

QList<Card> JsonDataGen::deCardList(const QJsonObject &obj)
{
    QJsonArray array;
    array=obj["info"].toArray();
    QList<Card> cards;
    for(int i=0;i<array.size();i++)
    {
        QJsonObject aobj=array[i].toObject();
        Card card(aobj["name"].toString(),
                Card::typeFromText(aobj["type"].toString()),
                Card::placeFromText(aobj["place"].toString()),
                Card::attrFromText(aobj["attr"].toString()),
                aobj["strength"].toInt());
        cards.append(card);
    }
    return cards;
}

QJsonObject JsonDataGen::editList(QStringList name,QStringList type,QString dname,int flag)
{
    QJsonObject obj;
    obj["cmd"]="editList";
    obj["fromGA"]=false;
    obj["deckName"]=dname;
    obj["flag"]=flag;
    QJsonArray array;
    for(int i=0;i<name.length();i++)
    {
        QJsonObject aobj;
        aobj["name"]=name.at(i);
        aobj["type"]=type.at(i);
        array.append(aobj);
    }
    obj["info"]=array;
    return obj;
}

bool JsonDataGen::isEditList(const QJsonObject &obj)
{
    return obj["cmd"]=="editList";
}

QPair<QPair<QString,int>,QPair<QStringList,QStringList>> JsonDataGen::deEditList(const QJsonObject &obj)
{
    QJsonArray array;
    array=obj["info"].toArray();
    QStringList name;
    QStringList type;
    for(int i=0;i<array.size();i++)
    {
        QJsonObject aobj=array[i].toObject();
        name.append(aobj["name"].toString());
        type.append(aobj["type"].toString());
    }
    return QPair<QPair<QString,int>,QPair<QStringList,QStringList>>(QPair<QString,int>(obj["deckName"].toString(),obj["flag"].toInt()),QPair<QStringList,QStringList>(name,type));
}

bool JsonDataGen::isEditConfirm(const QJsonObject &obj)
{
    return obj["cmd"]=="editConfirm";
}

QPair<QPair<QString,int>,QPair<QStringList,int>> JsonDataGen::deEditConfirm(const QJsonObject &obj)
{
    QJsonArray array;
    array=obj["info"].toArray();
    QStringList list;
    for(int i=0;i<array.size();i++)
    {
        QJsonObject aobj=array[i].toObject();
        list.append(aobj["name"].toString());
    }
    return QPair<QPair<QString,int>,QPair<QStringList,int>>(QPair<QString,int>(obj["deckName"].toString(),obj["submitFlag"].toInt()),QPair<QStringList,int>(list,obj["flag"].toInt()));
}

QJsonObject JsonDataGen::editConfirm(QPair<QString,int> namef,QStringList list,int flag)
{
    QJsonObject obj;
    obj["cmd"]="editConfirm";
    obj["fromGA"]=true;
    obj["flag"]=flag;
    obj["deckName"]=namef.first;
    obj["submitFlag"]=namef.second;
    QJsonArray array;
    for(auto p:list)
    {
        QJsonObject aobj;
        aobj["name"]=p;
        array.append(aobj);
    }
    obj["info"]=array;
    return obj;
}

QJsonObject JsonDataGen::warpGameCMD(const QJsonObject &cmd)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="gameCMD";
    obj["info"]=cmd;
    return obj;
}

bool JsonDataGen::isGameCMD(const QJsonObject &obj)
{
    return (obj["type"]=="command")&&(obj["content"]=="gameCMD");
}

bool JsonDataGen::isFromGA(const QJsonObject &obj)
{
    return obj["fromGA"].toBool();
}

QJsonObject JsonDataGen::deGameCMD(const QJsonObject &obj)
{
    return obj["info"].toObject();
}

QJsonObject JsonDataGen::warpCMDbyName(QJsonObject obj, QString name)
{
    obj["senderName"]=name;
    return obj;
}

bool JsonDataGen::isCMDbyName(const QJsonObject &obj, QString name)
{
    if(deCMDName(obj)==name)
        return true;
    return false;
}

QString JsonDataGen::deCMDName(const QJsonObject &obj)
{
    return obj["senderName"].toString();
}

QJsonObject JsonDataGen::cmdSingleton(QString cmd, QString info)
{
    QJsonObject obj;
    obj["content"]=cmd;
    obj["info"]=info;
    return obj;
}

bool JsonDataGen::isCmdSingleton(const QJsonObject &obj,QString cmd)
{
    return obj["content"]==cmd;
}

QString JsonDataGen::deCmdSingleton(const QJsonObject &obj)
{
    return obj["info"].toString();
}

QJsonObject JsonDataGen::cmdEffect(QString effect, QList<RowPair> infos)
{
    QJsonObject obj;
    obj["content"]=effect;
    QJsonArray array;
    for(auto p:infos)
    {
        QJsonObject aobj;
        aobj["from"]=Card::rowInfoToJson(p.first);
        aobj["to"]=Card::rowInfoToJson(p.second);
        array.append(aobj);
    }
    obj["info"]=array;
    return obj;
}

bool JsonDataGen::isCmdEffect(const QJsonObject &obj, QString effect)
{
    return obj["content"]==effect;
}

QList<RowPair> JsonDataGen::deCmdEffect(const QJsonObject &obj)
{
    QList<RowPair> list;
    QJsonArray array=obj["info"].toArray();
    for(int i=0;i<array.size();i++)
    {
        QJsonObject aobj=array[i].toObject();
        list.append(RowPair(Card::rowInfoFromJson(aobj["from"].toObject()),
                    Card::rowInfoFromJson(aobj["to"].toObject())));
    }
    return list;
}

QJsonObject JsonDataGen::cmdSimpleEffect(QString effect, RowPair info)
{
    QJsonObject obj;
    obj["content"]=effect;
    obj["from"]=Card::rowInfoToJson(info.first);
    obj["to"]=Card::rowInfoToJson(info.second);
    return obj;
}

bool JsonDataGen::isCmdSimpleEffect(const QJsonObject &obj, QString effect)
{
    return obj["content"]==effect;
}

RowPair JsonDataGen::deCmdSimpleEffect(const QJsonObject &obj)
{
    return RowPair(Card::rowInfoFromJson(obj["from"].toObject()),Card::rowInfoFromJson(obj["to"].toObject()));
}

QJsonObject JsonDataGen::cmdSimpleEffectWithP(QString effect, RowPair info,QPair<int,int> data)
{
    QJsonObject obj;
    obj["content"]=effect;
    obj["from"]=Card::rowInfoToJson(info.first);
    obj["to"]=Card::rowInfoToJson(info.second);
    obj["1"]=data.first;
    obj["2"]=data.second;
    return obj;
}

bool JsonDataGen::isCmdSimpleEffectWithP(const QJsonObject &obj, QString effect)
{
    return obj["content"]==effect;
}

QPair<RowPair, QPair<int, int> > JsonDataGen::deCmdSimpleEffectWithP(const QJsonObject &obj)
{
    return QPair<RowPair,QPair<int, int> >(RowPair(Card::rowInfoFromJson(obj["from"].toObject()),Card::rowInfoFromJson(obj["to"].toObject())),QPair<int,int>(obj["0"].toInt(),obj["1"].toInt()));
}

QJsonObject JsonDataGen::cmdSimpleEffectWithD(QString effect, RowPair info, QString data)
{
    QJsonObject obj;
    obj["content"]=effect;
    obj["from"]=Card::rowInfoToJson(info.first);
    obj["to"]=Card::rowInfoToJson(info.second);
    obj["data"]=data;
    return obj;
}

bool JsonDataGen::isCmdSimpleEffectWithD(const QJsonObject &obj, QString effect)
{
    return obj["content"]==effect;
}

QPair<RowPair, QString> JsonDataGen::deCmdSimpleEffectWithD(const QJsonObject &obj)
{
    return QPair<RowPair,QString>(RowPair(Card::rowInfoFromJson(obj["from"].toObject()),Card::rowInfoFromJson(obj["to"].toObject())),obj["data"].toString());
}

QJsonObject JsonDataGen::cmdEffectWithD(QString effect, QList<RowPair> infos, QList<int> datas)
{
    QJsonObject obj;
    obj["content"]=effect;
    QJsonArray array;
    for(auto p:infos)
    {
        QJsonObject aobj;
        aobj["from"]=Card::rowInfoToJson(p.first);
        aobj["to"]=Card::rowInfoToJson(p.second);
        array.append(aobj);
    }
    obj["info"]=array;
    QJsonArray array1;
    for(int i=0;i<datas.length();i++)
    {
        QJsonObject aobj;
        aobj[QString("data%1").arg(i)]=datas[i];
        array1.append(aobj);
    }
    obj["datas"]=array1;
    return obj;
}

bool JsonDataGen::isCmdEffectWithD(const QJsonObject &obj, QString effect)
{
    return obj["content"]==effect;
}

QPair<QList<RowPair>, QList<int>> JsonDataGen::deCmdEffectWithD(const QJsonObject &obj)
{
    QList<RowPair> list;
    QJsonArray array=obj["info"].toArray();
    for(int i=0;i<array.size();i++)
    {
        QJsonObject aobj=array[i].toObject();
        list.append(RowPair(Card::rowInfoFromJson(aobj["from"].toObject()),
                    Card::rowInfoFromJson(aobj["to"].toObject())));
    }
    QList<int> datas;
    QJsonArray array1=obj["datas"].toArray();
    for(int i=0;i<array1.size();i++)
    {
        QJsonObject obj=array1[i].toObject();
        datas.append(obj[QString("data%1").arg(i)].toInt());
    }
    return QPair<QList<RowPair>, QList<int>>(list,datas);
}

QJsonObject JsonDataGen::cmdEffectWithS(QString effect, QList<RowPair> infos, QStringList datas)
{
    QJsonObject obj;
    obj["content"]=effect;
    QJsonArray array;
    for(auto p:infos)
    {
        QJsonObject aobj;
        aobj["from"]=Card::rowInfoToJson(p.first);
        aobj["to"]=Card::rowInfoToJson(p.second);
        array.append(aobj);
    }
    obj["info"]=array;
    QJsonArray array1;
    for(int i=0;i<datas.length();i++)
    {
        QJsonObject aobj;
        aobj[QString("data%1").arg(i)]=datas[i];
        array1.append(aobj);
    }
    obj["datas"]=array1;
    return obj;
}

bool JsonDataGen::isCmdEffectWithS(const QJsonObject &obj, QString effect)
{
    return obj["content"]==effect;
}

QPair<QList<RowPair>, QStringList> JsonDataGen::deCmdEffectWithS(const QJsonObject &obj)
{
    QList<RowPair> list;
    QJsonArray array=obj["info"].toArray();
    for(int i=0;i<array.size();i++)
    {
        QJsonObject aobj=array[i].toObject();
        list.append(RowPair(Card::rowInfoFromJson(aobj["from"].toObject()),
                    Card::rowInfoFromJson(aobj["to"].toObject())));
    }
    QStringList datas;
    QJsonArray array1=obj["datas"].toArray();
    for(int i=0;i<array1.size();i++)
    {
        QJsonObject obj=array1[i].toObject();
        datas.append(obj[QString("data%1").arg(i)].toString());
    }
    return QPair<QList<RowPair>, QStringList>(list,datas);
}

QJsonObject JsonDataGen::cmdEffectSingleton(QString effect, QList<RowPair> infos, QString data)
{
    QJsonObject obj;
    obj["content"]=effect;
    QJsonArray array;
    for(auto p:infos)
    {
        QJsonObject aobj;
        aobj["from"]=Card::rowInfoToJson(p.first);
        aobj["to"]=Card::rowInfoToJson(p.second);
        array.append(aobj);
    }
    obj["info"]=array;
    obj["data"]=data;
    return obj;
}

bool JsonDataGen::isCmdEffectSingleton(const QJsonObject &obj, QString effect)
{
    return obj["content"]==effect;
}

QPair<QList<RowPair>, QString> JsonDataGen::deCmdEffectSingleton(const QJsonObject &obj)
{
    QList<RowPair> list;
    QJsonArray array=obj["info"].toArray();
    for(int i=0;i<array.size();i++)
    {
        QJsonObject aobj=array[i].toObject();
        list.append(RowPair(Card::rowInfoFromJson(aobj["from"].toObject()),
                    Card::rowInfoFromJson(aobj["to"].toObject())));
    }
    return QPair<QList<RowPair>, QString>(list,obj["data"].toString());
}

QJsonObject JsonDataGen::cmdConfirm(QString cmd)
{
    QJsonObject obj;
    obj["content"]=cmd;
    return obj;
}

bool JsonDataGen::isCmdConfirm(const QJsonObject &obj, QString cmd)
{
    return obj["content"]==cmd;
}

QJsonObject JsonDataGen::cmdWarpEnd(const QJsonObject &obj)
{
    QJsonObject objs=obj;
    objs["end"]=true;
    return objs;
}

bool JsonDataGen::isCmdEnd(const QJsonObject &obj)
{
    if(obj.find("end")==obj.end())
        return false;
    else
        return obj["end"].toBool();
}

QJsonObject JsonDataGen::cmdWarpKey(const QJsonObject &obj,QString key)
{
    QJsonObject objs=obj;
    objs[key]=true;
    return objs;
}

QJsonObject JsonDataGen::cmdWarpPair(const QJsonObject &obj, QString key, QString value)
{
    QJsonObject objs=obj;
    objs[key]=value;
    return objs;
}

QStringList JsonDataGen::deCmdKeyRecursive(const QJsonObject &obj, QString key)
{
    if(isCmds(obj))
    {
        QStringList list;
        QList<QJsonObject> objs=deCmds(obj);
        for(auto p:objs)
        {
            list.append(deCmdKeyRecursive(p,key));
        }
        return list;
    }
    if(obj.contains(key))
    {
        QStringList list;
        list.append(obj[key].toString());
        return list;
    }
    return QStringList();
}

QJsonObject JsonDataGen::cmdWarpMyOp(const QJsonObject &obj)
{
    if(isCmds(obj))
    {
        QList<QJsonObject> res;
        QList<QJsonObject> objs=deCmds(obj);
        for(auto p:objs)
        {
            res.append(cmdWarpMyOp(p));
        }
        return cmds(res);
    }
    QJsonObject objs=obj;
    objs["op"]="my";
    return objs;
}

bool JsonDataGen::isCmdMyOp(const QJsonObject &obj)
{
    if(obj["op"]=="my")
        return true;
    return false;
}

QJsonObject JsonDataGen::cmdWarpEnOp(const QJsonObject &obj)
{
    if(isCmds(obj))
    {
        QList<QJsonObject> res;
        QList<QJsonObject> objs=deCmds(obj);
        for(auto p:objs)
        {
            res.append(cmdWarpEnOp(p));
        }
        return cmds(res);
    }
    QJsonObject objs=obj;
    objs["op"]="en";
    return objs;
}

bool JsonDataGen::isCmdEnOp(const QJsonObject &obj)
{
    if(obj["op"]=="en")
        return true;
    return false;
}

QJsonObject JsonDataGen::cmdWarpFeedback(const QJsonObject &obj)
{
    QJsonObject objs=obj;
    objs["feedback"]=true;
    return objs;
}

bool JsonDataGen::isCmdFeedback(const QJsonObject &obj)
{
    if(obj.find("feedback")==obj.end())
        return false;
    else
        return obj["feedback"].toBool();
}

QJsonObject JsonDataGen::cmdWarpAnother(const QJsonObject &obj)
{
    QJsonObject objs=obj;
    objs["fromAnother"]=true;
    return objs;
}

bool JsonDataGen::isCmdAnother(const QJsonObject &obj)
{
    if(obj.find("fromAnother")==obj.end())
        return false;
    else
        return obj["fromAnother"].toBool();
}

bool JsonDataGen::hasChild(const QJsonObject &obj, QString con)
{
    if(obj["content"]==con)
        return true;
    if(isCmds(obj))
    {
        bool bas=false;
        QList<QJsonObject> objs=deCmds(obj);
        for(auto p:objs)
        {
            bas=bas||hasChild(p,con);
        }
        return bas;
    }
    return false;
}

bool JsonDataGen::hasKey(const QJsonObject &obj, QString key)
{
    if(obj.contains(key))
        return true;
    if(isCmds(obj))
    {
        bool bas=false;
        QList<QJsonObject> objs=deCmds(obj);
        for(auto p:objs)
        {
            bas=bas||hasKey(p,key);
        }
        return bas;
    }
    return false;
}

bool JsonDataGen::hasTrueKey(const QJsonObject &obj, QString key)
{
    if(obj.contains(key)&&obj[key]==true)
        return true;
    if(isCmds(obj))
    {
        bool bas=false;
        QList<QJsonObject> objs=deCmds(obj);
        for(auto p:objs)
        {
            bas=bas||hasKey(p,key);
        }
        return bas;
    }
    return false;
}

QStringList JsonDataGen::deSingletonChild(const QJsonObject &obj, QString con)
{
    if(isCmds(obj))
    {
        QStringList list;
        QList<QJsonObject> objs=deCmds(obj);
        for(auto p:objs)
        {
            list.append(deSingletonChild(p,con));
        }
        return list;
    }
    if(obj["content"]==con)
    {
        QStringList list;
        list.append(deCmdSingleton(obj));
        return list;
    }
    return QStringList();
}

QStringList JsonDataGen::deStringListChild(const QJsonObject &obj, QString con)
{
    if(isCmds(obj))
    {
        QStringList list;
        QList<QJsonObject> objs=deCmds(obj);
        for(auto p:objs)
        {
            list.append(deSingletonChild(p,con));
        }
        return list;
    }
    if(obj["content"]==con)
    {
        return deStringList(obj);
    }
    return QStringList();
}

void JsonDataGen::removeKeyRecursive(QJsonObject &obj, QString key)
{
    if(isCmds(obj))
    {
        QList<QJsonObject> objs=deCmds(obj);
        for(auto p:objs)
        {
            removeKeyRecursive(p,key);
        }
    }
    if(obj.contains(key))
    {
        obj.remove(key);
    }
}

QJsonObject JsonDataGen::cmdWarpUpdate(const QJsonObject &obj)
{
    QJsonObject objt=obj;
    objt["update"]=true;
    return objt;
}

QJsonObject JsonDataGen::cmds(const QList<QJsonObject> &objs)
{
    QJsonObject obj;
    obj["content"]="cmds";
    QJsonArray array;
    for(auto p:objs)
    {
        array.append(p);
    }
    obj["info"]=array;
    return obj;
}

bool JsonDataGen::isCmds(const QJsonObject &obj)
{
    return obj["content"]=="cmds";
}

QList<QJsonObject> JsonDataGen::deCmds(const QJsonObject &obj)
{
    QList<QJsonObject> objs;
    QJsonArray array=obj["info"].toArray();
    for(int i=0;i<array.count();i++)
    {
        objs.append(array[i].toObject());
    }
    return objs;
}

QJsonObject JsonDataGen::loginInfo(QString name, QString psw)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="login";
    QJsonArray users;
    QJsonObject user;
    user["name"]=name;
    user["password"]=psw;
    users.append(user);
    obj["info"]=users;
    return obj;
}

bool JsonDataGen::isLoginInfo(const QJsonObject &obj)
{
    return (obj["type"]=="command")&&(obj["content"]=="login");
}

QPair<QString, QString> JsonDataGen::deLoginInfo(const QJsonObject &obj)
{
    QJsonArray array=obj["info"].toArray();
    QJsonObject objt= array[0].toObject();
    return QPair<QString,QString>(objt["name"].toString(),objt["password"].toString());
}

QJsonObject JsonDataGen::GA(QJsonObject obj)
{
    QJsonObject objs=obj;
    objs["fromGA"]=true;
    return objs;
}

QJsonObject JsonDataGen::confirm(QString cmd)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]=cmd;
    return obj;
}

bool JsonDataGen::isConfirm(const QJsonObject &obj, QString cmd)
{
    return (obj["type"]=="command")&&(obj["content"]==cmd);
}

QJsonObject JsonDataGen::singleton(QString cmd, QString info)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]=cmd;
    obj["info"]=info;
    return obj;
}

bool JsonDataGen::isSingleton(const QJsonObject &obj, QString cmd)
{
    return (obj["type"]=="command")&&(obj["content"]==cmd);
}

QString JsonDataGen::deSingleton(const QJsonObject &obj)
{
    return obj["info"].toString();
}

QJsonObject JsonDataGen::stringList(QString cmd, QStringList infos)
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]=cmd;
    obj["length"]=infos.length();
    int s=0;
    for(auto p:infos)
    {
        obj[QString("info%1").arg(s)]=p;
        s++;
    }
    return obj;
}

bool JsonDataGen::isStringList(const QJsonObject &obj, QString cmd)
{
    return (obj["type"]=="command")&&(obj["content"]==cmd);
}

QStringList JsonDataGen::deStringList(const QJsonObject &obj)
{
    int length=obj["length"].toInt();
    QStringList list;
    for(int i=0;i<length;i++)
    {
        list.append(obj[QString("info%1").arg(i)].toString());
    }
    return list;
}

QJsonObject JsonDataGen::cmdStringList(QString cmd, QStringList infos)
{
    QJsonObject obj;
    obj["content"]=cmd;
    obj["length"]=infos.length();
    int s=0;
    for(auto p:infos)
    {
        obj[QString("info%1").arg(s)]=p;
        s++;
    }
    return obj;
}

bool JsonDataGen::isCmdStringList(const QJsonObject &obj, QString cmd)
{
    return obj["content"]==cmd;
}

QStringList JsonDataGen::deCmdStringList(const QJsonObject &obj)
{
    int length=obj["length"].toInt();
    QStringList list;
    for(int i=0;i<length;i++)
    {
        list.append(obj[QString("info%1").arg(i)].toString());
    }
    return list;
}

QJsonObject JsonDataGen::getUserOnline()
{
    QJsonObject obj;
    obj["type"]="command";
    obj["content"]="getUserOnline";
    return obj;
}

bool JsonDataGen::isGetUserOnline(const QJsonObject &obj)
{
    return (obj["type"]=="command")&&(obj["content"]=="getUserOnline");
}


JsonDataGen::JsonDataGen()
{

}
