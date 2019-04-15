#ifndef GRAPHACTOR_H
#define GRAPHACTOR_H

#include <QObject>
#include"networkactor.h"

class GraphActor : public QObject
{
    Q_OBJECT
public:
    void startGA();
public:
    NetworkActor NA;
private:
    QMap<QString,QString> realNames;
    QString curDeck;
    QMap<QString,QString> Cardinfo;
    QString curDeckName;
    int userListCMD;
    QVariantList names;
    QVariantList types;
    QVariantList strengths;
    QMap<QString,QString> curDeckList;
protected:
    QString typeByName(QString name);
    int strengthByName(QString name);
    QList<Card> cardsByNames(const QStringList &names);
    QStringList getNamesFromCards(const QList<Card> &cards);
    QStringList getTypesFromCards(const QList<Card> &cards);
    QList<int> getStrengthsFromCards(const QList<Card> &cards);
    Card cardByName(QString name);
    QString encodeDeck(const QStringList &deck);
    QStringList decodeDeck(QString);
    QList<Card> stringToCards(QString str);
    QString stringFromCards(const QList<Card> &cards);
    template<class  T>
    QVariantList slistToVlist(const QList<T> &strl);
public:
    explicit GraphActor(QObject *parent = nullptr);
signals:
    // to Graph
    void start();
    void loginRecvG(int flag);
    void signupRecvG(int flag);
    void showUserList(QVariantList list);
    void refreshUserList(QVariantList list);
    void noDeck();
    void showConnectRequest(QString name);
    void showConnectConfirm(QString name);
    void showConnectRefuse(QString name);
    void showCardAvailable(QVariantList names,QVariantList types,QVariantList strengths,int flag,QString curDeckName,QVariantList cnames,QVariantList ctypes,QVariantList cstrengths);
    void editConfirm(int flag);
    void showDeckList(QVariantList list,QString curDeck);
    void showDeckInfoG(QVariantList names,QVariantList types,QVariantList strengths);
    void showReplace(QVariantList names,QVariantList types,QVariantList strengths,int limit);
    void chooseSkill(QVariantList names,QVariantList types,QVariantList strengths);
    void replaceTo(QString name,QString type,int strength);
    void showTable(int flagG,int deck,QVariantList names,QVariantList types,QVariantList strengths);
    void useCard(QString name,QString type,int strength);
    void placeLimit(QVariantList me,QVariantList en);
    void showInfo(QString name,QString cardDetail);
    void appendHand(QString name,QString type,int strength);
    void enemyDrop(QString name,QString type,int strength,int hand,int row,int index,int flag);
    void insertCard(QVariantList names,QVariantList types,QVariantList strengths,QVariantList rows,QVariantList indexs,int flag);

public slots:
    // form Graph
    void loginRequest(QString name,QString psw);
    void getMyRank();
    void getUserOnline(int);
    void getUserElO();
    void getDeck();
    void connectRequest(QString name);
    void connectConfirm(QString name);
    void connectRefuse(QString name);
    void signupRequest(QString name,QString psw);
    void showEditMode(int,QString);
    QString getRealName(QString str);
    void saveEdit(QVariantList name,QVariantList type,QString dname,int flag);
    void showDeckInfo(QString name);
    void recordDeck(QString str);
    QString getCurDeck();
    void startConfirm(QString name);
    void replaceOne(int index);
    void changePlaceLimit(QString name);
    void showCardInfo(QString name);
    void close();

public slots:
    // form NA
    void loginRecv(int);
    void signupRecv(int);
    void userList(QMap<QString,QString>);
    void connectRequestNA(QString name);
    void connectConfirmNA(QString name);
    void connectRefuseNA(QString name);
    void cardList(QList<Card> cards,int);
    void editConfirmNA(int);
    void curDeckNameNA(QString);
    void deckData(QPair<QPair<QStringList,QStringList>,QString>);
    void showReplaceNA(QStringList hand,int);
    void replaceToNA(QString name);
    void showTableNA(QStringList);
    void useCardNA(QString name);
    void enemyDropNA(QString,int,int,int,int);
    void chooseSkillNA(QStringList names);
    void appendHandNA(QString);
    void insertCardNA(QStringList names,QVariantList rows,QVariantList indexs,int flag);
};

template<class  T>
QVariantList GraphActor::slistToVlist(const QList<T> &strl)
{
    QVariantList list;
    for(auto p:strl)
    {
        list.append(QVariant::fromValue(p));
    }
    return list;
}

#endif // GRAPHACTOR_H
