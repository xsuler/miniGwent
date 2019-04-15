#include "player.h"
#include<QtGlobal>
#include<QTime>

QList<QPair<int, Card *>> Player::typeFilter(QList<Card *> cards,CardType type)
{
    QList<QPair<int, Card *>> list;
    for(int i=0;i<cards.length();i++)
    {
        if(cards[i]->type==type)
        {
            list.append(QPair<int, Card *>(i,cards[i]));
        }
    }
    return list;
}

QList<QPair<int, Card *> > Player::exTypeFilter(QList<Card *> cards, CardType type)
{
    QList<QPair<int, Card *>> list;
    for(int i=0;i<cards.length();i++)
    {
        if(cards[i]->type!=type)
        {
            list.append(QPair<int, Card *>(i,cards[i]));
        }
    }
    return list;
}
//remember to update other cards
void Player::moveToGraveyard(RowInfo info)
{
    if(row[info.first]->at(info.second)->attr!=CardAttr::Lost)
    {
        graveyard.append(row[info.first]->at(info.second));
        for(int i=0;i<graveyard.length();i++)
        {
            graveyard[i]->graveIndex=i;
        }
    }
    row[info.first]->removeAt(info.second);
    for(int i=0;i<row[info.first]->length();i++)
    {
        row[info.first]->at(i)->row=info.first;
        row[info.first]->at(i)->index=i;
    }
}


void Player::washCards()
{
    if(deck.length()<=1)
        return;
    int d=0;
    for(int i=1;i<deck.length();i++)
    {
        d=qrand()%i;
        deck.swap(i,d);
    }
    for(int i=0;i<deck.length();i++)
    {
        deck[i]->deckIndex=i;
    }
}

int Player::sumStrengthInRow(int index)
{
    int res=0;
    for(int i=0;i<row[index]->length();i++)
    {
        res+=row[index]->at(i)->curStrength;
    }
    return res;
}

void Player::replaceOneHand(int index)
{
    if(deck.length()<=0)
        return;
    int d=qrand()%(deck.length());
    Card* tmp=hand[index];
    hand[index]=deck[d];
    deck[d]=tmp;
    for(int i=0;i<deck.length();i++)
    {
        deck[i]->deckIndex=i;
    }
}

void Player::getToHand(int n)
{
    if(deck.length()<n)
    {
        hand.append(deck);
        deck.clear();
        return;
    }
    hand.append(deck.mid(0,n));
    deck=deck.mid(n,deck.length()-n);
    for(int i=0;i<deck.length();i++)
    {
        deck[i]->deckIndex=i;
    }
}

Card* Player::getWeakest()
{
    int min=100;
    Card *temp;
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<row[j]->length();i++)
        {
            if(row[j]->at(i)->curStrength<min)
            {
                min=row[j]->at(i)->curStrength;
                temp=row[j]->at(i);
            }
        }
    }
    return temp;
}

void Player::refresh()
{
    row[0]->clear();
    row[1]->clear();
    row[2]->clear();
    fixInfo();
    weather.clear();
    curDeploy=nullptr;
    deployPending.clear();
    skillPendingCount=0;
    deployFlag=0;
    isUpdateCard=0;
}

void Player::clear()
{
    row[0]->clear();
    row[1]->clear();
    row[2]->clear();
    hand.clear();
    deck.clear();
    graveyard.clear();
    name.clear();
    weather.clear();
    curDeploy=nullptr;
    deployPending.clear();
    skillPendingCount=0;
    deployFlag=0;
    isUpdateCard=0;
    scores.clear();
}

void Player::fixInfo()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<row[i]->length();j++)
        {
            row[i]->at(j)->row=i;
            row[i]->at(j)->index=j;
        }
    }
    for(int i=0;i<deck.length();i++)
    {
        deck[i]->deckIndex=i;
    }
    for(int i=0;i<graveyard.length();i++)
    {
        graveyard[i]->graveIndex=i;
    }
}

int Player::allInRow()
{
    return row[0]->length()+row[1]->length()+row[2]->length();
}

int Player::sumStrength()
{
    int res=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<row[i]->length();j++)
        {
            res+=row[i]->at(j)->curStrength;
        }
    }
    return res;
}


void Player::insertIntoDeck(int index, Card *card)
{
    deck.insert(index,card);
    for(int i=0;i<deck.length();i++)
    {
        deck[i]->deckIndex=i;
    }
}

void Player::insertIntoHand(int index, Card *card)
{
    hand.insert(index,card);
}

void Player::removeWeather(int index, Weather w)
{
    auto r=weather;
    for(int i=0;i<r.length();i++)
    {
        if(r[i].first==index&&r[i].second==w)
        {
            weather.removeAt(i);
        }
    }
}

void Player::clearWeatherInRow(int index)
{
    auto r=weather;
    for(int i=0;i<r.length();i++)
    {
        if(r[i].first==index)
        {
            weather.removeAt(i);
        }
    }
}

void Player::insertIntoRow(RowInfo info, Card *card)
{
    row[info.first]->insert(info.second,card);
    for(int i=0;i<row[info.first]->length();i++)
    {
        row[info.first]->at(i)->row=info.first;
        row[info.first]->at(i)->index=i;
    }
}

void Player::removeFromDeck(int index)
{
    deck.removeAt(index);
    for(int i=0;i<deck.length();i++)
    {
        deck[i]->deckIndex=i;
    }
}

void Player::removeFromRow(RowInfo info)
{
    row[info.first]->removeAt(info.second);
    for(int i=0;i<row[info.first]->length();i++)
    {
        row[info.first]->at(i)->deckIndex=i;
    }
}

bool Player::containsWeather(Weather w)
{
    for(auto p:weather)
    {
        if(p.second==w)
            return true;
    }
    return false;
}

Card *Player::getStrongest()
{
    int max=-1;
    Card *temp;
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<row[j]->length();i++)
        {
            if(row[j]->at(i)->curStrength>max)
            {
                max=row[j]->at(i)->curStrength;
                temp=row[j]->at(i);
            }
        }
    }
    return temp;
}

QList<Card *> Player::getRandomInList(const QList<Card*> &cds,int x)
{
    QList<Card*> cards=cds;
    if(x>cards.length())
        return QList<Card*>();
    int d=0;
    for(int i=1;i<cards.length();i++)
    {
        d=qrand()%i;
        cards.swap(i,d);
    }
    return cards.mid(0,x);
}

Card *Player::getStrongestInRow(int index)
{
    Card* res;
    int max=-1;
    for(int i=0;i<row[index]->length();i++)
    {
        if(row[index]->at(i)->curStrength>max)
        {
            max=row[index]->at(i)->curStrength;
            res=row[index]->at(i);
        }
    }
    return res;
}

Card *Player::getWeakestInRow(int index)
{
    Card* res;
    int min=100;
    for(int i=0;i<row[index]->length();i++)
    {
        if(row[index]->at(i)->curStrength<min)
        {
            min=row[index]->at(i)->curStrength;
            res=row[index]->at(i);
        }
    }
    return res;
}

Card *Player::getStrongestInList(const QList<Card *> &list)
{
    Card* res;
    int max=-1;
    for(int i=0;i<list.length();i++)
    {
        if(list[i]->curStrength>max)
        {
            max=list[i]->curStrength;
            res=list[i];
        }
    }
    return res;
}

Card *Player::getWeakestInList(const QList<Card *> &list)
{
    Card* res;
    int min=100;
    for(int i=0;i<list.length();i++)
    {
        if(list[i]->curStrength<min)
        {
            min=list[i]->curStrength;
            res=list[i];
        }
    }
    return res;
}

QList<Card *> Player::getContainerOfRow(int index)
{
    QList<Card*> res;
    for(int i=0;i<row[index]->length();i++)
    {
        res.append(row[index]->at(i));
    }
    return res;
}

Player::Player()
{
    isUpdateCard=0;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    row.append(new QList<Card*>);
    row.append(new QList<Card*>);
    row.append(new QList<Card*>);
    deployFlag=0;
    skillPendingCount=0;
}
