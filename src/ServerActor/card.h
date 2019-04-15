#ifndef CARD_H
#define CARD_H
#include<QObject>

class JsonDataGen;
class Player;

enum State
{
    Shield,
};

enum CardType
{
    King,
    Gold,
    Sliver,
    Copper,
    TError
};
enum CardPlace
{
    myAnywhere,
    enAnywhere,
    my1,
    my2,
    my3,
    en1,
    en2,
    en3,
    PError
};

//indicate whether into graveyard after death
enum CardAttr
{
    Lost,
    Plain,
    AError
};

typedef QPair<int,int> RowInfo;
typedef QPair<RowInfo,RowInfo> RowPair;


/* basic class of cards
 *
 * author:
 * sule
 *
 * 2017.9
*/
class Card
{
public:
    QString name;
    //gold, sliver, king or copper
    CardType type;
    //indicate place limit
    CardPlace place;
    //whether loss
    CardAttr attr;
    //basic strength
    int strength;
    //current armor
    int armor;
    //current strength
    int curStrength;
    //which row this card is exist
    int row;
    //index in row
    int index;
    //index in deck
    int deckIndex;
    //index in graveyard
    int graveIndex;
    //state such as Shield
    QList<State> states;
public:
    JsonDataGen* JDG;
public:
    //parse cards from file
    static QList<Card> parseCards();
    //parse holdable cards from file
    static QList<Card> getHoldable();
    QString getName();
    //erase one state
    void eraseState(State st);
    //whether has state
    bool hasState(State st);
    CardType getType();
    CardPlace getPlace();
    CardAttr getAttr();
    int getStrength();
    //the json data indicate my destroy
    QJsonObject destroyJson();
    //the hurt effect
    QJsonObject hurts(Player &me,Player &en,const QJsonObject &obj);
    //the ate effect
    QJsonObject eat(Player &me,Player &en,const QJsonObject &obj,Card *sender,int flag);
    //the increase effect
    QJsonObject increase(Player &me, Player &en, const QJsonObject &obj);
    //my deploy skills
    virtual QJsonObject deploy(Player &me,Player &en,int row,int index);
    //dynamic update
    virtual QJsonObject update(Player &me, Player &en, const QJsonObject &obj,const QJsonObject &info);
    //skill's feedback
    virtual QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
    //effect by other cards
    virtual QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    static QStringList names(const QList<Card*> list);
    static QJsonObject rowInfoToJson(const RowInfo &info);
    static RowInfo rowInfoFromJson(const QJsonObject &obj);
    static CardType typeFromText(QString s);
    static CardPlace placeFromText(QString s);
    static CardAttr attrFromText(QString s);
    static QString typeToText(CardType s);
    static QString placeToText(CardPlace s);
    static QString attrToText(CardAttr s);
public:
    Card(QString name,CardType type,CardPlace place,CardAttr attr,int strength):name(name),type(type),place(place),attr(attr),strength(strength){}
    Card(){}
};

/* cards container
 *
 * author:
 * sule
 *
 * 2017.9
*/
class C
{
public:
    static QList<Card> cardsAvailable;
    static QList<Card> Holdable;
public:
    C(){}
};


#endif // CARD_H
