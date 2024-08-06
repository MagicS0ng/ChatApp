#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
class SearchInfo
{
public:
    SearchInfo(int uid, QString name, QString nick, QString des, int sex, QString icon);
    int _uid;
    QString _name;
    QString _nick;
    QString _desc;
    int _sex;
    QString _icon;
};
struct AuthInfo
{
    AuthInfo(int uid, QString name,  QString nick,QString icon, int sex)
        :_uid(uid), _name(name),_nick(nick), _icon(icon),_sex(sex)
    {

    }
    int _uid;
    QString _name;
    QString _nick;
    QString _icon;
    int _sex;
};
struct AuthRsp
{
    AuthRsp(int uid, QString name,  QString nick,QString icon, int sex)
        :_uid(uid), _name(name),_nick(nick), _icon(icon),_sex(sex)
    {

    }
    int _uid;
    QString _name;
    QString _nick;
    QString _icon;
    int _sex;
};
struct UserInfo
{
    UserInfo(int uid, QString name, QString nick, QString icon, int sex):
        _uid(uid),_name(name), _nick(nick), _icon(icon), _sex(sex)
    {

    }
    UserInfo(std::shared_ptr<AuthInfo> auth):
        _uid(auth->_uid), _name(auth->_name),_icon(auth->_icon), _sex(auth->_sex)
    {

    }
    UserInfo(int uid, QString name,  QString icon):
        _uid(uid),_name(name), _icon(icon)
    {

    }
    UserInfo(std::shared_ptr<AuthRsp> auth):
        _uid(auth->_uid), _name(auth->_name),_icon(auth->_icon), _sex(auth->_sex)
    {

    }
    int _uid;
    QString _name;
    QString _nick;
    QString _icon;
    int _sex;
};
class AddFriendApply
{
public:
    AddFriendApply(int from_uid, QString name, QString desc, QString icon, QString nick, int sex)
        :_from_uid(from_uid), _name(name), _desc(desc), _icon(icon), _nick(nick), _sex(sex){};
    int _from_uid;
    QString _name;
    QString _desc;
    QString _icon;
    QString _nick;
    int     _sex;

};
struct ApplyInfo
{
    ApplyInfo(int uid, QString name, QString desc, QString icon, QString nick, int sex, int status)
        :_uid(uid), _name(name), _desc(desc), _icon(icon),_nick(nick), _sex(sex), _status(status)
    {

    }
    void SetIcon(QString head)
    {
        _icon = head;
    }
    int _uid;
    QString _name;
    QString _desc;
    QString _icon;
    QString _nick;
    int _sex;
    int _status;
};


#endif // USERDATA_H
