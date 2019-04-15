#include "tsthread.h"


void TSthread::run()
{
    socket=new QTcpSocket;
    if (!socket->setSocketDescriptor(socketDescriptor))
    {
        emit error(socket->error());
        return;
    }
    connect(socket,SIGNAL(disconnected()),socket,SLOT(deleteLater()));
    proc=new TSproc(socket);
    connect(proc,SIGNAL(quitThread()),this,SLOT(quit()));
    proc->moveToThread(this);
    proc->conChan(temp,tempList);
    exec();
}

TSproc *TSthread::getProc(TSChan *chan)
{
    temp=chan;
    tempList=chan->peekAll();
    return proc;
}

void TSthread::startThread()
{
    start();
}
