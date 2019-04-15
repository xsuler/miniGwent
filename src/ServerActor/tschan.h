#ifndef MUTICHAN_H
#define MUTICHAN_H

#include <QObject>
#include <QVariant>
#include <QSharedPointer>

/* A thread-safe data type
 *
 * interface:
 * connectChan;addData;addDataList;peekAll;getData;peekData
 *
 * introduce:
 * after connecting two TSChan, when writting to one TSChan, another will recieve the QVariant data
 * when get from TSChan, the data will be poped, at the same time another connected TSChan will also
 * be poped
 *
 * author:
 * sule
 *
 * 2017.9
*/
class TSChan:public QObject
{
    Q_OBJECT
private:
    QList<QVariant> dataList;
public:
    //connect two chan
    static void connectChan(TSChan *chan1,TSChan *chan2);
    //add data to all of the connecting chan
    void addData(const QVariant &data);
    //add a list of Variant
    void addDataList(const QList<QVariant> &datalist);
    //this function won't pop the data
    QList<QVariant> peekAll() const;
    //pop the data and then return it
    QVariant getData();
    //peek the last data
    QVariant peekData();
    QSharedPointer<QList<TSChan*>> owner;
private slots:
    void recvData(const QVariant &data,QSharedPointer<QList<TSChan*>> owner);
    void deleData(QSharedPointer<QList<TSChan*>> owner);
signals:
    void sendData(const QVariant &data,QSharedPointer<QList<TSChan*>> owner);
    void remvData(QSharedPointer<QList<TSChan*>> owner);
public:
    TSChan();
    //TSChan(const TSChan& other);
};


#endif // MUTICHAN_H
