#ifndef USERMETA_H
#define USERMETA_H
#include<QString>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QMetaType>

// this is a copy from ServerActor
class UserMeta
{
private:
    QString name;
    QString password;
public:
    QJsonObject toJson();
    static QPair<QString,QString> fromJson(const QJsonObject &obj);
    QString getName() const;
    QString getPassword() const;
    void setName(QString str);
public:
    UserMeta(){}
    UserMeta(QString name,QString password):name(name),password(password){}
    UserMeta(const UserMeta &other);
};

Q_DECLARE_METATYPE(UserMeta)

#endif // USERMETA_H
