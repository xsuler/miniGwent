#ifndef JSONDATAGEN_H
#define JSONDATAGEN_H
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QVariant>
#include"usermeta.h"
#include"card.h"


// this is a copy from ServerActor
class JsonDataGen
{
public:
    QJsonObject loginInfo(QString name,QString psw);
    bool isLoginInfo(const QJsonObject &obj);
    QPair<QString,QString> deLoginInfo(const QJsonObject &obj);

    QJsonObject confirm(QString cmd);
    bool isConfirm(const QJsonObject &obj,QString cmd);

    QJsonObject singleton(QString cmd,QString info);
    bool isSingleton(const QJsonObject &obj,QString cmd);
    QString deSingleton(const QJsonObject &obj);

    QJsonObject stringList(QString cmd,QStringList infos);
    bool isStringList(const QJsonObject &obj,QString cmd);
    QStringList deStringList(const QJsonObject &obj);

    QJsonObject cmdStringList(QString cmd,QStringList info);
    bool isCmdStringList(const QJsonObject &obj,QString cmd);
    QStringList deCmdStringList(const QJsonObject &obj);

    QJsonObject getUserOnline();
    bool isGetUserOnline(const QJsonObject &obj);

    QJsonObject loginRecv(int flag);
    bool isLoginRecv(const QJsonObject &obj);
    int deLoginRecv(const QJsonObject &obj);

    QJsonObject userList(const QList<QVariant> &datas);
    bool isUserList(const QJsonObject &obj);
    QMap<QString,QString> deUserList(const QJsonObject &obj);

    QJsonObject connectRequest(QString name);
    bool isConnectRequest(const QJsonObject &obj);
    QString deConnectRequest(const QJsonObject &obj);

    QJsonObject deckData(QStringList names,QStringList cards,QString cur);
    bool isDeckData(const QJsonObject &obj);
    QPair<QPair<QStringList,QStringList>,QString> deDeckData(const QJsonObject &obj);

    QJsonObject connectConfirm(QString name);
    bool isConnectConfirm(const QJsonObject &obj);
    QString deConnectConfirm(const QJsonObject &obj);

    QJsonObject connectRefuse(QString name);
    bool isConnectRefuse(const QJsonObject &obj);
    QString deConnectRefuse(const QJsonObject &obj);

    QJsonObject signupInfo(QString name,QString psw);
    bool isSignupInfo(const QJsonObject &obj);
    QPair<QString,QString> deSignupInfo(const QJsonObject &obj);

    QJsonObject signupRecv(int flag);
    bool isSignupRecv(const QJsonObject &obj);
    int deSignupRecv(const QJsonObject &obj);

    QJsonObject cardList(QList<Card>);
    bool isCardList(const QJsonObject &obj);
    QList<Card> deCardList(const QJsonObject &obj);

    QJsonObject editList(QStringList name,QStringList type,QString dname,int flag);
    bool isEditList(const QJsonObject &obj);
    QPair<QPair<QString,int>,QPair<QStringList,QStringList>> deEditList(const QJsonObject &obj);

    QJsonObject editConfirm(QPair<QString,int> namef,QStringList list,int flag);
    bool isEditConfirm(const QJsonObject &obj);
    QPair<QPair<QString,int>,QPair<QStringList,int>> deEditConfirm(const QJsonObject &obj);

    QJsonObject warpGameCMD(const QJsonObject &obj);
    bool isGameCMD(const QJsonObject &obj);
    QJsonObject deGameCMD(const QJsonObject &obj);

    bool isFromGA(const QJsonObject &obj);  //raw cmd
    QJsonObject GA(QJsonObject obj);  //raw cmd

    QJsonObject warpCMDbyName(QJsonObject obj,QString name);  //raw cmd
    bool isCMDbyName(const QJsonObject &obj,QString name);  //raw cmd
    QString deCMDName(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdSingleton(QString cmd,QString info);  //raw cmd
    bool isCmdSingleton(const QJsonObject &obj,QString cmd);  //raw cmd
    QString deCmdSingleton(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdEffect(QString effect,QList<RowPair> infos);  //raw cmd
    bool isCmdEffect(const QJsonObject &obj,QString effect);  //raw cmd
    QList<RowPair> deCmdEffect(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdSimpleEffect(QString effect,RowPair info);  //raw cmd
    bool isCmdSimpleEffect(const QJsonObject &obj,QString effect);  //raw cmd
    RowPair deCmdSimpleEffect(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdSimpleEffectWithP(QString effect,RowPair info,QPair<int,int>);  //raw cmd
    bool isCmdSimpleEffectWithP(const QJsonObject &obj,QString effect);  //raw cmd
    QPair<RowPair,QPair<int,int>> deCmdSimpleEffectWithP(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdSimpleEffectWithD(QString effect,RowPair info,QString data);  //raw cmd
    bool isCmdSimpleEffectWithD(const QJsonObject &obj,QString effect);  //raw cmd
    QPair<RowPair,QString> deCmdSimpleEffectWithD(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdEffectWithD(QString effect,QList<RowPair> infos,QList<int> datas);  //raw cmd
    bool isCmdEffectWithD(const QJsonObject &obj,QString effect);  //raw cmd
    QPair<QList<RowPair>,QList<int>> deCmdEffectWithD(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdEffectWithS(QString effect,QList<RowPair> infos,QStringList datas);  //raw cmd
    bool isCmdEffectWithS(const QJsonObject &obj,QString effect);  //raw cmd
    QPair<QList<RowPair>,QStringList> deCmdEffectWithS(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdEffectSingleton(QString effect,QList<RowPair> infos,QString data);  //raw cmd
    bool isCmdEffectSingleton(const QJsonObject &obj,QString effect);  //raw cmd
    QPair<QList<RowPair>,QString> deCmdEffectSingleton(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdConfirm(QString cmd);  //raw cmd
    bool isCmdConfirm(const QJsonObject &obj,QString cmd);  //raw cmd

    QJsonObject cmdWarpEnd(const QJsonObject &obj);  //raw cmd
    bool isCmdEnd(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdWarpKey(const QJsonObject &obj,QString key);  //raw cmd

    QJsonObject cmdWarpPair(const QJsonObject &obj,QString key,QString value);  //raw cmd
    QStringList deCmdKeyRecursive(const QJsonObject &obj,QString key);  //raw cmd

    QJsonObject cmdWarpMyOp(const QJsonObject &obj);  //raw cmd
    bool isCmdMyOp(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdWarpEnOp(const QJsonObject &obj);  //raw cmd
    bool isCmdEnOp(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdWarpFeedback(const QJsonObject &obj);  //raw cmd
    bool isCmdFeedback(const QJsonObject &obj);  //raw cmd

    QJsonObject cmdWarpAnother(const QJsonObject &obj);  //raw cmd
    bool isCmdAnother(const QJsonObject &obj);  //raw cmd

    bool hasChild(const QJsonObject &obj,QString con);
    bool hasKey(const QJsonObject &obj,QString key);
    bool hasTrueKey(const QJsonObject &obj,QString key);
    QStringList deSingletonChild(const QJsonObject &obj,QString con);
    QStringList deStringListChild(const QJsonObject &obj,QString con);
    void removeKeyRecursive(QJsonObject &obj,QString key);

    QJsonObject cmdWarpUpdate(const QJsonObject &obj);

    QJsonObject cmds(const QList<QJsonObject> &objs);
    bool isCmds(const QJsonObject &obj);
    QList<QJsonObject> deCmds(const QJsonObject &obj);

public:
    JsonDataGen();
};

#endif // JSONDATAGEN_H
