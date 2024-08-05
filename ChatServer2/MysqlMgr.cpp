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
bool MysqlMgr::CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo)
{
	return m_dao.CheckPwd(email, pwd, userInfo);
}
std::shared_ptr<UserInfo> MysqlMgr::GetUser(int uid)
{
	return m_dao.GetUser(uid);
}
