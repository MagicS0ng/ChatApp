#pragma once
#include "const.h"
#include "MySqlPool.h"

class MysqlDAO
{
public:
	MysqlDAO();
	~MysqlDAO();
	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool CheckPwd(const std::string& email, const std::string & pwd, UserInfo& userInfo);
	bool UpdatePwd(const std::string& name, const std::string& newPwd);
	std::shared_ptr<UserInfo> GetUser(int uid);
private:
	std::unique_ptr<MysqlPool> m_pool;
};