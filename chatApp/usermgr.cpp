#include "usermgr.h"

UserMgr::UserMgr() {}
UserMgr::~UserMgr()
{

}

void UserMgr::SetName(QString name)
{
    m_name = name;
}
void UserMgr::SetUid(int uid)
{
    m_uid = uid;
}
void UserMgr::SetToken(QString token)
{
    m_token = token;
}

int UserMgr::GetUid()
{
    return m_uid;
}

QString UserMgr::GetName()
{
    return m_name;
}

std::vector<std::shared_ptr<ApplyInfo> > UserMgr::GetApplyList()
{
    return _apply_list;
}
