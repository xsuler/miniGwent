#ifndef CARD_H
#define CARD_H
#include<QObject>

// this is a copy from ServerActor

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

enum CardAttr
{
    Lost,
    Plain,
    AError
};

typedef QPair<int,int> RowInfo;
typedef QPair<RowInfo,RowInfo> RowPair;

class Card
{
public:
    QString name;
    CardType type;
    CardPlace place;
    CardAttr attr;
    int strength;
    int armor;
    int curStrength;
    int row;
    int index;
    int deckIndex;
    int graveIndex;
    QList<State> states;
public:
    JsonDataGen* JDG;
public:
    static QList<Card> parseCards();
    static QList<Card> getHoldable();
    QString getName();
    void eraseState(State st);
    bool hasState(State st);
    CardType getType();
    CardPlace getPlace();
    CardAttr getAttr();
    int getStrength();
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

class C
{
public:
    static QList<Card> cardsAvailable;
    static QList<Card> Holdable;
public:
    C(){}
};


#endif // CARD_H
