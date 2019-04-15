#ifndef PLAYER_H
#define PLAYER_H
#include<QObject>
#include"card.h"

enum Weather
{
    fog,
    rain,
    frost,
    frostPlus
};

/* class of the player
 *
 * author:
 * sule
 *
 * 2017.9
*/
class Player
{
public:
    QString name;
    QList<Card*> deck;
    QList<Card*> hand;
    QList<QList<Card*>*> row;
    QList<Card*> graveyard;
    QList<QPair<int,Weather>> weather;
    //the current deploy card
    Card* curDeploy;
    //maybe there is a pending of deploy
    QList<Card*> deployPending;
    int skillPendingCount;
    int deployFlag;
    int  isUpdateCard;
    QList<int> scores;
public:
    static QList<QPair<int,Card*>> typeFilter(QList<Card*> cards,CardType type);
    static QList<QPair<int,Card*>> exTypeFilter(QList<Card*> cards,CardType type);
    void moveToGraveyard(RowInfo info);
    void washCards();
    int sumStrengthInRow(int index);
    void replaceOneHand(int index);
    void getToHand(int n);
    Card* getWeakest();
    void refresh();
    void clear();
    void fixInfo();
    int allInRow();
    int sumStrength();
    template<class T,class R>
    static QList<T> firsts(QList<QPair<T,R>> list);
    template<class T,class R>
    static QList<R> seconds(QList<QPair<T,R>> list);
    void insertIntoDeck(int index,Card* card);
    void insertIntoHand(int index,Card* card);
    void removeWeather(int index,Weather w);
    void clearWeatherInRow(int index);
    void insertIntoRow(RowInfo info,Card* card);
    void removeFromDeck(int index);
    //will not move to graveyard
    void removeFromRow(RowInfo info);
    bool containsWeather(Weather w);
    Card* getStrongest();
    QList<Card*> getRandomInList(const QList<Card*> &cards,int x);
    Card* getStrongestInRow(int index);
    Card* getWeakestInRow(int index);
    Card* getStrongestInList(const QList<Card*> &list);
    Card* getWeakestInList(const QList<Card*> &list);
    QList<Card *> getContainerOfRow(int index);
public:
    Player();
};

template<class T, class R>
QList<T> Player::firsts(QList<QPair<T,R> > list)
{
    QList<T> ts;
    for(auto p:list)
    {
        ts.append(p.first);
    }
    return ts;
}

template<class T, class R>
QList<R> Player::seconds(QList<QPair<T,R> > list)
{
    QList<R> ts;
    for(auto p:list)
    {
        ts.append(p.second);
    }
    return ts;
}

#endif // PLAYER_H
