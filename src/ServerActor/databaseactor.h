#ifndef DATABASEACTOR_H
#define DATABASEACTOR_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QObject>


/* the dateBase handler for GameActor
 *
 * useing sqlite3
 *
 * author:
 * sule
 *
 * 2017.9
*/
class DatabaseActor:public QObject
{
    Q_OBJECT
private:
    QSqlDatabase db;
public:
    //insert a deck
    void insertDeck(QString owner,QString deckName,QString deck);
    //record as the current deck
    void recordDeck(QString owner,QString deckName);
    //create tables if not exists
    static void createTable();
    //get current deck's name
    QString getCurDeckName(QString owner);
    bool isdeckExist(QString owner,QString deckName);
    void updateDeck(QString owner,QString deckName,QString deck);
    //return all the deck of the owner
    QMap<QString,QString> getAllDeck(QString owner);
    //insert a user
    void insertUser(QString name,QString psw);
    bool isUserExist(QString name);
    bool isPasswordRight(QString name,QString psw);
public:
    explicit DatabaseActor(QObject *parent=nullptr);
    ~DatabaseActor();
};

#endif // DATABASEACTOR_H
