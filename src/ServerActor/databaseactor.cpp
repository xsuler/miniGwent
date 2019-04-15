#include "databaseactor.h"
#include<QDebug>
#include<iostream>
using std::cout;
using std::endl;
void DatabaseActor::insertDeck(QString owner, QString deckName, QString deck)
{
    QSqlQuery query(db);
    deck.insert(0,"a");
    query.exec(tr("update deck set iscurdeck = '%1' where owner = '%2'").arg(0).arg(owner));
    query.exec(tr("insert into deck values('%1', '%2', '%3', '%4')").arg(owner).arg(deckName).arg(deck).arg(1));
}

void DatabaseActor::recordDeck(QString owner, QString deckName)
{
    QSqlQuery query(db);
    query.exec(tr("update deck set iscurdeck = '%1' where owner = '%2'").arg(0).arg(owner));
    query.exec(tr("update deck set iscurdeck = '%1' where owner = '%2' and deckName = '%3'").arg(1).arg(owner).arg(deckName));
}

void DatabaseActor::createTable()
{
    QSqlDatabase DB;
    DB=QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("datafile.db");
    DB.open();
    QSqlQuery query(DB);
    query.exec("create table if not exists user (username text, password text)");
    query.exec("create table if not exists deck (owner text, deckName text, deckCard text, iscurdeck integer)");
    DB.close();
}

QString DatabaseActor::getCurDeckName(QString owner)
{
    QSqlQuery query(db);
    query.exec(tr("select deckName from deck where owner = '%1' and iscurdeck = '%2'").arg(owner).arg(1));
    QString res;
    while (query.next())
    {
        res=query.value(0).toString();
        return res;
    }
    query.exec(tr("select deckName from deck where owner = '%1' and iscurdeck = '%2'").arg(owner).arg(0));
    if (query.next())
    {
        res=query.value(0).toString();
        query.exec(tr("update deck set iscurdeck = '%1' where owner = '%2' and deckName = '%3'").arg(1).arg(owner).arg(res));
        return res;
    }
}

bool DatabaseActor::isdeckExist(QString owner, QString deckName)
{
    QSqlQuery query(db);
    query.exec(tr("select deckName from deck where owner = '%1' and deckName = '%2'").arg(owner).arg(deckName));
    return query.next();
}

void DatabaseActor::updateDeck(QString owner, QString deckName, QString deck)
{
    QSqlQuery query(db);
    deck.insert(0,"a");
    query.exec(tr("update deck set iscurdeck = '%1' where owner = '%2'").arg(0).arg(owner));
    query.exec(tr("update deck set deckCard = '%1' where owner = '%2' and deckName = '%3'").arg(deck).arg(owner).arg(deckName));
}

QMap<QString,QString> DatabaseActor::getAllDeck(QString owner)
{
    QSqlQuery query(db);
    query.exec(tr("select deckName,deckCard from deck where owner = '%1'").arg(owner));
    QMap<QString,QString> map;
    while (query.next())
    {
        QString str=query.value(1).toString();
        str.remove(0,1);
        map.insert(query.value(0).toString(),str);
    }
    return map;
}

void DatabaseActor::insertUser(QString name, QString psw)
{
    QSqlQuery query(db);
    query.exec(tr("insert into user values('%1', '%2')").arg(name).arg(psw));
}

bool DatabaseActor::isUserExist(QString name)
{
    QSqlQuery query(db);
    query.exec(tr("select username from user where username = '%1'").arg(name));
    return query.next();
}

bool DatabaseActor::isPasswordRight(QString name, QString psw)
{
    QSqlQuery query(db);
    query.exec(tr("select password from user where username = '%1'").arg(name));
    query.next();
    return query.value(0).toString()==psw;
}

DatabaseActor::DatabaseActor(QObject *parent):QObject(parent)
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("datafile.db");
    db.open();
}

DatabaseActor::~DatabaseActor()
{
    db.close();
}
