#ifndef TSTHREAD_H
#define TSTHREAD_H
#include<QThread>
#include<QtNetwork>
#include"tsproc.h"


/* thread class for users
 *
 * interface:
 * getSocket;getProc
 *
 * author:
 * sule
 *
 * 2017.9
*/
class TSthread : public QThread
{
    Q_OBJECT
private:
    int socketDescriptor;
    QTcpSocket *socket;
    TSproc *proc;
    TSChan *temp;
    QList<QVariant> tempList;
public:
    void run() override;
    //return the socket of the in coming connection
    QTcpSocket* getSocket(){return socket;}
    //return the handler object
    TSproc* getProc(TSChan *chan);
signals:
    void error(QTcpSocket::SocketError socketError);
private slots:
    void startThread();
public:
    TSthread(int socketDescriptor,QObject *parent):socketDescriptor(socketDescriptor),QThread(parent){}
};

#endif // TSTHREAD_H
