#include "tsserver.h"
#include"tsthread.h"


void TSserver::startServer(QHostAddress addr, int port)
{
    listen(addr,port);
}

void TSserver::incomingConnection(qintptr socketDescriptor)
{
    TSthread *thread=new TSthread(socketDescriptor,this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(this,SIGNAL(startThread()),thread,SLOT(startThread()));
    emit startThread();
    QTcpSocket* con=thread->getSocket();
    TSproc *proc=thread->getProc(&userChan);
    userList.insert(thread,QPair<QTcpSocket*,TSproc*>(con,proc));
}

TSserver::TSserver(QObject *parent):QTcpServer(parent)
{
    qRegisterMetaType<UserMeta>("UserMeta");
    qRegisterMetaType<QSharedPointer<QList<TSChan*>>>("QSharedPointer<QList<TSChan*>>");
}

