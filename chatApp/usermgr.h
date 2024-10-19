#ifndef USERMGR_H
#define USERMGR_H

#include <QObject>
#include <QJsonArray>
#include <VideoCallingDialog.h>
#include "userdata.h"
#include "singleton.h"
class UserMgr: public QObject, public Singleton<UserMgr>
{
    Q_OBJECT
    friend class Singleton<UserMgr>;
public:
    ~UserMgr();
    void SetToken(QString token);
    void SetUserInfo(std::shared_ptr<UserInfo>);
    int GetUid();
    QString GetName();
    QString GetIcon();
    std::shared_ptr<UserInfo> GetUserInfo();
    std::vector<std::shared_ptr<ApplyInfo>> GetApplyList();
    bool AlreadyApply(int uid);
    void AddApplyList(std::shared_ptr<ApplyInfo> app);
    void AppendApplyList(QJsonArray );
    void AppendFriendList(QJsonArray);
    bool CheckFriendById(int uid);
    void AddFriend(std::shared_ptr<AuthRsp> auth_rsp);
    void AddFriend(std::shared_ptr<AuthInfo> auth_info);
    std::shared_ptr<FriendInfo> GetFriendById(int uid);

    std::vector<std::shared_ptr<FriendInfo>> GetChatListPerPage();
    bool IsLoadChatFin();
    void UpdateChatLoadedCount();
    std::vector<std::shared_ptr<FriendInfo>> GetConListPerPage();
    void UpdateContactLoadedCount();
    bool IsLoadConFin();
    void AppendFriendChatMsg(int friend_id,std::vector<std::shared_ptr<TextChatData>>);
private:
    QString m_name;
    QString m_token;
    int m_uid;
    std::shared_ptr<UserInfo> m_user_info;
    std::vector<std::shared_ptr<ApplyInfo>> _apply_list;
    QMap<int, std::shared_ptr<FriendInfo>> _friend_map;
    std::vector<std::shared_ptr<FriendInfo>> _friend_list;
    int _chat_loaded;
    int _contact_loaded;
    bool is_calling=false;

private:
    UserMgr();
};

#endif // USERMGR_H
