#pragma once

#include "const.h"
#include "MysqlDAO.h"

class MysqlMgr : public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
public:
	~MysqlMgr();
	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
	bool CheckEmail(const std::string &name, const std::string & email);
	bool CheckPwd(const std::string &email,const std::string &pwd, UserInfo & userInfo);
	bool UpdatePwd(const std::string& name, const std::string& email);
	std::shared_ptr<UserInfo> GetUser(int uid);
private:
	MysqlMgr();
	MysqlDAO m_dao;
};