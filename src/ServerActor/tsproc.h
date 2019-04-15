#ifndef TSPROC_H
#define TSPROC_H
#include<QObject>
#include<QtNetwork>
#include<QDebug>
#include<QTimer>
#include"tschan.h"
#include"usermeta.h"
#include"jsondatagen.h"
#include"databaseactor.h"
#include"gameactor.h"

class TSserver;


/* handle the message from client
 *
 * author:
 * sule
 *
 * 2017.9
*/
class TSproc:public QObject
{
    Q_OBJECT
public:
    friend class TSserver;
    void conChan(TSChan *chan,const QList<QVariant> &datas);
private:
    //if is editing deck
    int editMode;
    //commonly shared by all of the users
    TSChan *userList;
    //if is logined
    int loginflag;
    //my read/write chan
    TSChan *myChan;
    //name of current deck
    QString curDeck;
    //another user's name
    QString toName;
    //used for spy on my chan
    TSChan spyChan;
    //another user's chan
    TSChan toChan;
    //user's data
    UserMeta *userData;
    //map of my deck
    QMap<QString,QString> deckMap;
    //json data generator
    JsonDataGen JDG;
    int initflag;
    int gameflag;
    QTimer *timer;
protected:
    GameActor GA;
    DatabaseActor DA;
    QTcpSocket *socket;
    //encode stringlist to String
    QString encodeDeck(QStringList deck);
    //only encode holdable card
    QString encodeHandDeck(QStringList deck);
    //send Json data to client
    void sendMessage(const QJsonObject &obj);
    void init();
    //write to another user
    void writeToAnother(const QJsonObject &obj);
    TSChan* getChanBy(QString name);
    //write to a chan by user's name
    void writeChanTo(QString name,const QJsonObject &obj);
signals:
    void quitThread();
private slots:
    //handle the incomming message
    void handler(const QJsonObject &obj);
    //parse message to json
    void messageParser();
    //spy on my chan
    void spyOnConnect();
public:
    TSproc(QTcpSocket *sock);
};

#endif // TSPROC_H
