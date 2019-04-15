#ifndef USERMETA_H
#define USERMETA_H
#include"tschan.h"
#include<QString>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QMetaType>

/* userInfo
 *
 * interface:
 * toJson;fromJson;getName;getChan
 *
 * author:
 * sule
 *
 * 2017.9
*/
class UserMeta
{
private:
    QString name;
    TSChan* chan{nullptr};
public:
    //convert to json
    QJsonObject toJson();
    //convert from json
    static QPair<QString,QString> fromJson(const QJsonObject &obj);
    //get user's name
    QString getName() const;
    //get user's read/write chan
    TSChan* getChan() const;
public:
    UserMeta(){}
    UserMeta(QString name,TSChan* chan):name(name),chan(chan){}
    UserMeta(const UserMeta &other);
    ~UserMeta();
};

Q_DECLARE_METATYPE(UserMeta)

#endif // USERMETA_H
