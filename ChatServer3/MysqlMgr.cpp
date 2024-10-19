#pragma once

#include "MysqlMgr.h"



MysqlMgr::~MysqlMgr()
{
}

MysqlMgr::MysqlMgr()
{
}
int MysqlMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	return m_dao.RegUser(name, email, pwd);
}

bool MysqlMgr::CheckEmail(const std::string& name, const std::string& email)
{
	return m_dao.CheckEmail(name, email);
}
bool MysqlMgr::UpdatePwd(const std::string& name, const std::string& newPwd)
{
	return m_dao.UpdatePwd(name, newPwd);
}
bool MysqlMgr::AddFriendReply(const int & uid, const int & touid)
{
	return m_dao.AddFriendReply(uid, touid);
}
bool MysqlMgr::AuthFriendApply(const int& from, const int& to)
{
	return m_dao.AuthFriendApply(from, to);
}
bool MysqlMgr::AddFriend(const int& from, const int& to, std::string back_name)
{
	return m_dao.AddFriend(from, to, back_name);
}
bool MysqlMgr::CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo)
{
	return m_dao.CheckPwd(email, pwd, userInfo);
}
std::shared_ptr<UserInfo> MysqlMgr::GetUser(int uid)
{
	return m_dao.GetUser(uid);
}
std::shared_ptr<UserInfo> MysqlMgr::GetUser(std::string name)
{
	return m_dao.GetUser(name);
}

bool MysqlMgr::GetApplyList(int touid, std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit)
{
	return m_dao.GetApplyList(touid, applyList, begin, limit);
}

bool MysqlMgr::GetFriendList(int self_id, std::vector<std::shared_ptr<UserInfo>>& user_info)
{
	return m_dao.GetFriendList(self_id, user_info);
}
