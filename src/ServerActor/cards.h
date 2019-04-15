#ifndef CARDS_H
#define CARDS_H
#include"card.h"

class Earth:public Card
{
public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    Earth();
};

class Light:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Light();
};


class Frost:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Frost();
};

class Fog:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Fog();
};

class Rain:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Rain();
};

class Lacerate:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Lacerate();
};

class Horn:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Horn();
};

class Mirror:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
public:
   Mirror();
};

class Lgni:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    Lgni();
};

class Dagon:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Dagon();
};

class Foglet:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    Foglet();
};

class Geel:public Card
{
private:
    int count;
    QList<Card*> cards;
    QList<int> indexs;
public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
   Geel();
};

class CelHarpy:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    CelHarpy();
};

class CelHarpyEgg:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    CelHarpyEgg();
};

class CelHarpyBaby:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    CelHarpyBaby();
};

class WSpirit:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    WSpirit();
};

class Wolf:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    Wolf();
};

class LEarth:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    LEarth();
};

class CroneBre:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    CroneBre();
};

class CroneWea:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    CroneWea();
};

class CroneWhi:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    CroneWhi();
};

class Arch:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    Arch();
};

class WHRider:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    WHRider();
};

class Caranthir:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Caranthir();
};

class Frightener:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Frightener();
};

class Elder:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    Elder();
};

class Arachas:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    Arachas();
};

class VranWarrior:public Card
{
public:
    int eatFlag;
public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
   VranWarrior();
};

class ArachasBe:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    ArachasBe();
};

class ArachasBaby:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    ArachasBaby();
};

class ThPotion:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
    QJsonObject feedback(Player &me,Player &en,const QJsonObject &obj);
public:
    ThPotion();
};

class Roach:public Card
{
public:

public:
    QJsonObject deploy(Player &me,Player &en,int row,int index);
    QJsonObject update(Player &me, Player &en, const QJsonObject &obj, const QJsonObject &info);
    QJsonObject effect(Player &me, Player &en, const QJsonObject &obj, Card* sender, int flag );
public:
    Roach();
};
#endif // CARDS_H
