#ifndef NETWORKACTOR_H
#define NETWORKACTOR_H


#include <QObject>
#include<QtNetwork>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include"jsondatagen.h"

const QHostAddress hostAddr=QHostAddress::LocalHost;
const int port=3000;

/*handle the incoming message from servr
 *
 * auhor:
 * sule
 *
 * 2017.9
*/
class NetworkActor : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    JsonDataGen JDG;
    int myPassFlag;
    int enemyPassFlag;
public:
    void login(QString name,QString psw);
    void getUserOnline();
    void connectRequest(QString name);
    void connectConfirm(QString name);
    void connectRefuse(QString name);
    void signupRequest(QString name,QString psw);
    void getCardList(int);
    void getDeck();
    template<class T>
    QVariantList slistToVlist(QList<T> strl);
    void saveEdit(QStringList name,QStringList type,QString dname,int flag);
    void startConfirm(QString name);
    void recordDeck(QString deck);
    void replaceOne(int index);
    void close();
protected:
    void handler(const QJsonObject &obj);
    void sendMessage(const QJsonObject &obj);
signals:
    void editConfirm(int);
    void loginRecv(int);
    void curDeckName(QString);
    void signupRecv(int);
    void userList(QMap<QString,QString>);
    void connectRequestNA(QString name);
    void connectConfirmNA(QString name);
    void connectRefuseNA(QString name);
    void cardList(QList<Card>,int);
    void deckData(QPair<QPair<QStringList,QStringList>,QString>);
    void showReplace(QStringList,int);
    void replaceTo(QString name);
    void showTable(QStringList);
    void showShield(QVariantList rows,QVariantList indexs,int flag);
    void destroyCard(QVariantList rows,QVariantList indexs);
    void insertCard(QStringList names,QVariantList rows,QVariantList indexs,int flag);
    void enemyDestroyCard(QVariantList rows,QVariantList indexs);
    void turn();
    void start();
    void fakeTurn();
    void noDeck();
    void endRound(QString winner,QString myScore,QString enScore);
    void chooseSkill(QStringList list);
    void clearWeather(int flag);
    void useCard(QString name);
    void enemyDrop(QString name,int hand,int row,int index,int flag);
    void chooseOneOfEnemyRow();
    void showWeather(QString name,int index,int flag);
    void eraseShield(int row,int index,int flag);
    void updateStrength(int row,int index,int strength,int flag);
    void updateArmor(int row,int index,int armor,int flag);
    void finishChooseRow();
    void finishChooseCard();
    void chooseOneOfCard(int flag);
    void appendHand(QString);
    void enemyPass();
    void endGame(QVariantList list,int flag);
    void refreshData(int myDeckNum,int myGraveNum,int enDeckNum,int enGraveNum,int myTStrength,int enTStrength,int flag);

private slots:
    void messageParser();
    void errorR(QAbstractSocket::SocketError);

public slots:
    void replaceFinish();
    void dropCard(int handIndex,int rowIndex,int row);
    void chosed(int index);
    void chooseEnemyRow(int index);
    void chooseOneCard(int row,int index);
    void forceTurn();
    void pass();
    void passE();

public:
    explicit NetworkActor(QObject *parent = nullptr);
    ~NetworkActor();
};

template<class  T>
QVariantList NetworkActor::slistToVlist(QList<T> strl)
{
    QVariantList list;
    for(auto p:strl)
    {
        list.append(QVariant::fromValue(p));
    }
    return list;
}


#endif // NETWORKACTOR_H
