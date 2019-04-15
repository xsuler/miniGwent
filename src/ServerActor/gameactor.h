#ifndef GAMEACTOR_H
#define GAMEACTOR_H

#include<QObject>
#include"jsondatagen.h"
#include"player.h"
#include<QTimer>


/* handle the core game process
 *
 * author:
 * sule
 *
 * 2017.9
*/
class GameActor:public QObject
{
    Q_OBJECT
private:
    //json data generator
    JsonDataGen JDG;
    //two players
    QList<Player> player;
    //indicate the current player
    int curPlayer;
public:
    //recieve Json command from TSProc
    void recvCMD(const QJsonObject &obj);
protected:
    //the list of passed name
    QList<QString> passed;
    //the list of winner
    QList<QString> winner;
    QTimer *REtimer;
    //count the times of replacement
    int replaceCount;
    //indicate the current round
    int curRound;
    //get first values from a list of pair
    template<class T,class R>
    QList<T> firsts(QList<QPair<T,R>> list);
    //get second values from a list of pair
    template<class T,class R>
    QList<R> seconds(QList<QPair<T,R>> list);
    //update player
    QJsonObject playerUpdate(QString name);
    //clear my info
    void clear();
    //update all the cards when turn the round
    QJsonObject cardsStartUpdate(QString name);
    ////update all the cards when drop one card
    QJsonObject cardsDropUpdate(QString name,const QJsonObject &feedback,Card* curDeploy);
    //update all the cards when a feedback come in
    QJsonObject cardsFeedbackUpdate(QString name,const QJsonObject &feedback);
    //get another player
    Player& another(const Player &p);
    //warp the sending command
    QJsonObject warp(const QJsonObject &obj,QString name);
    Player &playerByName(QString name);
    //convert names to cards
    QList<Card*> stringToCards(QString str);
    //convert cards to names
    QString stringFromCards(const QList<Card*> &cards);
    //init game
    void initPlayer(QString name,QString deck);
    QStringList decodeDeck(QString);
    QString encodeDeck(QStringList deck);
    //check whether a deck is legal
    int editCheck(QStringList names,QStringList types);
    //get another player's name
    QString anotherName(QString name);
signals:
    //send CMD to TSProc
    void sendCMD(const QJsonObject &obj);
private slots:
    //start a round
    void startRound();
public:
    explicit GameActor(QObject *parent=nullptr);
    ~GameActor();
};

template<class T, class R>
QList<T> GameActor::firsts(QList<QPair<T,R> > list)
{
    QList<T> ts;
    for(auto p:list)
    {
        ts.append(p.first);
    }
    return ts;
}

template<class T, class R>
QList<R> GameActor::seconds(QList<QPair<T,R> > list)
{
    QList<R> ts;
    for(auto p:list)
    {
        ts.append(p.second);
    }
    return ts;
}

#endif // GAMEACTOR_H
