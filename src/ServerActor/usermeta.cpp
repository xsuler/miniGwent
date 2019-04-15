#include "usermeta.h"
#include<QDebug>

//in SA
QJsonObject UserMeta::toJson()
{
    QJsonObject obj;
    obj["name"]=name;
    return obj;
}

QPair<QString, QString> UserMeta::fromJson(const QJsonObject &obj)
{
    return QPair<QString, QString>(obj["name"].toString(),obj["password"].toString());
}

QString UserMeta::getName() const
{
    return name;
}

TSChan* UserMeta::getChan() const
{
    return chan;
}

UserMeta::UserMeta(const UserMeta &other)
{
    name=other.getName();
    chan=other.getChan();
}

UserMeta::~UserMeta()
{

}
