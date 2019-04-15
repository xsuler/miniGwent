#include "usermeta.h"
#include<QDebug>

//in GA
QJsonObject UserMeta::toJson()
{
    QJsonObject obj;
    obj["name"]=name;
    obj["password"]=password;
    return obj;
}

QString UserMeta::getName() const
{
    return name;
}

QPair<QString, QString> UserMeta::fromJson(const QJsonObject &obj)
{
    return QPair<QString, QString>(obj["name"].toString(),obj["password"].toString());
}


QString UserMeta::getPassword() const
{
    return password;
}

void UserMeta::setName(QString str)
{
    name=str;
}

UserMeta::UserMeta(const UserMeta &other)
{
    name=other.getName();
    password=other.getPassword();
}
