#ifndef TSSERVER_H
#define TSSERVER_H
#include<QObject>
#include<QPair>
#include<QMap>
#include<QtNetwork>
#include"tsproc.h"
#include"usermeta.h"

/* A thread-safe Server
 *
 * interface:
 * startServer
 *
 * author:
 * sule
 *
 * 2017.9
*/
class TSserver:public QTcpServer
{
    Q_OBJECT
private:
    //store users info, maybe useless
    QMap<QThread*,QPair<QTcpSocket*,TSproc*>> userList;
    //a common chan shared by all of the users
    TSChan userChan;
public:
    //start the server
    void startServer(QHostAddress addr,int port);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
public:
    TSserver(QObject *parent=0);
signals:
    void startThread();
};

#endif // TSSERVER_H
