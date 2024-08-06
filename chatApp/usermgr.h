#ifndef USERMGR_H
#define USERMGR_H

#include <QObject>
#include "userdata.h"
#include "singleton.h"
class UserMgr: public QObject, public Singleton<UserMgr>
{
    Q_OBJECT
    friend class Singleton<UserMgr>;
public:
    ~UserMgr();
    void SetName(QString name);
    void SetUid(int uid);
    void SetToken(QString token);
    int GetUid();
    QString GetName();
    std::vector<std::shared_ptr<ApplyInfo>> GetApplyList();
    bool AlreadyApply(int uid);
    void AddApplyList(std::shared_ptr<ApplyInfo> & app);
private:
    QString m_name;
    QString m_token;
    int m_uid;
    std::vector<std::shared_ptr<ApplyInfo>> _apply_list;
private:
    UserMgr();
};

#endif // USERMGR_H
