#include "tschan.h"


//TSChan &TSChan::operator =(const TSChan &chan)
//{
//    dataList=chan.peekAll();
//    connectChan(this,&chan);
//}

void TSChan::connectChan(TSChan *chan1,TSChan *chan2)
{
    connect(chan1,SIGNAL(sendData(QVariant,QSharedPointer<QList<TSChan*>>)),chan2,SLOT(recvData(QVariant,QSharedPointer<QList<TSChan*>>)));
    connect(chan2,SIGNAL(sendData(QVariant,QSharedPointer<QList<TSChan*>>)),chan1,SLOT(recvData(QVariant,QSharedPointer<QList<TSChan*>>)));
    connect(chan1,SIGNAL(remvData(QSharedPointer<QList<TSChan*>>)),chan2,SLOT(deleData(QSharedPointer<QList<TSChan*>>)));
    connect(chan2,SIGNAL(remvData(QSharedPointer<QList<TSChan*>>)),chan1,SLOT(deleData(QSharedPointer<QList<TSChan*>>)));
}


void TSChan::addData(const QVariant &data)
{
    owner->clear();
    owner->append(this);
    dataList.append(data);
    emit sendData(data,owner);
}

void TSChan::addDataList(const QList<QVariant> &datas)
{
    for(auto p:datas)
    {
        addData(p);
    }
}

QList<QVariant> TSChan::peekAll() const
{
    return dataList;
}

QVariant TSChan::getData()
{
    if(dataList.isEmpty())
        return QVariant();
    owner->clear();
    owner->append(this);
    QVariant tmp=dataList.last();
    dataList.removeLast();
    emit remvData(owner);
    return QVariant(tmp);
}


QVariant TSChan::peekData()
{
    if(dataList.isEmpty())
        return QVariant();
    return QVariant(dataList.last());
}


void TSChan::recvData(const QVariant &data, QSharedPointer<QList<TSChan*>> owner)
{
    if(owner->contains(this))
        return;
    owner->append(this);
    dataList.append(data);
    emit sendData(data,owner);
}


void TSChan::deleData(QSharedPointer<QList<TSChan*>> owner)
{
    if(owner->contains(this))
        return;
    if(dataList.isEmpty())
        return;
    owner->append(this);
    dataList.removeLast();
    emit remvData(owner);
}


TSChan::TSChan()
{
    owner=QSharedPointer<QList<TSChan*>>(new QList<TSChan*>);
}

//TSChan::TSChan(const TSChan &other)
//{
//    dataList=other.peekAll();
//    connectChan(this,&other);
//}
