#pragma once
#include "MySqlDAO.h"
#include "ConfigMgr.h"


MysqlDAO::MysqlDAO()
{
	auto& cfg = ConfigMgr::Inst();
	const auto& host = cfg["Mysql"]["Host"];
	const auto& port = cfg["Mysql"]["Port"];
	const auto& user = cfg["Mysql"]["User"];
	const auto& schema = cfg["Mysql"]["Schema"];
	const auto& passwd = cfg["Mysql"]["Passwd"];
	m_pool.reset(new MysqlPool(host + ":" + port, user, passwd, schema, 5));
}
MysqlDAO::~MysqlDAO()
{
	m_pool->Close();
}
int MysqlDAO::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	auto con = m_pool->getConnection();
	try
	{
		if(con ==nullptr)
		{
			return false;
		}
		std::unique_ptr<sql::PreparedStatement> stmt(con->m_con->prepareStatement("CALL reg_user(?,?,?,@result)"));
		std::cout << "Create user with Name: " << name << ", Email: " << email << ", password: " << pwd << std::endl;
		stmt->setString(1, name);
		stmt->setString(2, email);
		stmt->setString(3, pwd);
		stmt->execute();
		
		std::unique_ptr<sql::Statement> stmtResult(con->m_con->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmtResult->executeQuery("SELECT @result as result"));
		if (res->next())
		{
			int result = res->getInt("result");
			std::cout << "Result: " << result << std::endl;
			m_pool->returnConnection(std::move(con));
			return result;
		}
		m_pool->returnConnection(std::move(con));
		return -1;
	}
	catch (sql::SQLException &e)
	{
		m_pool->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )\n";
		return -1;
	}
}
bool MysqlDAO::CheckEmail(const std::string& name, const std::string& email)
{
	auto con = m_pool->getConnection();
	try
	{
		if (con == nullptr)
			return false;
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("SELECT email FROM user where name = ?"));
		pstmt->setString(1, name);
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		while (res->next())
		{
			std::cout << "Check Email: " << res->getString("email") << std::endl;
			if (email != res->getString("email"))
			{
				m_pool->returnConnection(std::move(con));
				return false;
			}
			m_pool->returnConnection(std::move(con));
			return true;
		}
		return true;
	}
	catch (const sql::SQLException &e)
	{
		m_pool->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )\n";
		return false;
	}
}
bool MysqlDAO::UpdatePwd(const std::string& name, const std::string& newpwd)
{
	auto con = m_pool->getConnection();
	try
	{
		if (con == nullptr)
			return false;
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("UPDATE user SET pwd = ? WHERE name = ?"));
		pstmt->setString(2, name);
		pstmt->setString(1, newpwd);
		std::cout << "Updating passwd of  user: " << name << " to " << newpwd << std::endl;
		
		int updateCount = pstmt->executeUpdate();
		std::cout << "Updated rows: " << updateCount << std::endl;
		m_pool->returnConnection(std::move(con));
		return true;
	}
	catch (const sql::SQLException& e)
	{
		m_pool->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )\n";
		return false;
	}
}
bool  MysqlDAO::CheckPwd(const std::string& email, const std::string& pwd,  UserInfo& userInfo)
{
	auto con = m_pool->getConnection();
	if (con == nullptr)
	{
		return false;
	}
	Defer defer([this, &con]()
		{
			m_pool->returnConnection(std::move(con));
		});
	try
	{
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("SELECT * FROM user WHERE email = ?"));
		pstmt->setString(1, email);
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		std::string origin_pwd = "";
		while (res->next())
		{
			origin_pwd = res->getString("pwd");
			std::cout << "Password: " << origin_pwd << std::endl;
			break;
		}
		if (pwd != origin_pwd)
		{
			return false;
		}
		userInfo.userName = res->getString("name");
		userInfo.userEmail = email;
		userInfo.uid = res->getInt("uid");
		userInfo.userPwd = origin_pwd;
		return true;
	}
	catch (sql::SQLException &e)
	{
		m_pool->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )\n";
		return false;
	}
}
bool MysqlDAO::AddFriendApply(const int& from, const int& to)
{
	auto con = m_pool->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		m_pool->returnConnection(std::move(con));
		});

	try {
		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("INSERT INTO friend_apply (from_uid, to_uid) values (?,?) "
			"ON DUPLICATE KEY UPDATE from_uid = from_uid, to_uid = to_uid"));
		pstmt->setInt(1, from); // from id
		pstmt->setInt(2, to);
		// 执行更新
		int rowAffected = pstmt->executeUpdate();
		if (rowAffected < 0) {
			return false;
		}
		return true;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}


	return true;
}
std::shared_ptr<UserInfo> MysqlDAO::GetUser(int uid)
{
	auto con = m_pool->getConnection();
	if (con == nullptr)
		return nullptr;
	Defer defer([this, &con] {
		m_pool->returnConnection(std::move(con)); });
	try
	{
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("SELECT * FROM user WHERE uid = ?"));
		pstmt->setInt(1, uid);
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		std::shared_ptr<UserInfo> user_ptr = nullptr;
		while (res->next())
		{
			user_ptr.reset(new UserInfo);
			user_ptr->userPwd = res->getString("pwd");
			user_ptr->userEmail = res->getString("email");
			user_ptr->userName = res->getString("name");
			user_ptr->userNick = res->getString("nick");
			user_ptr->userDesc = res->getString("desc");
			user_ptr->userSex = res->getInt("sex");
			user_ptr->uid = uid;
			break;
		}
		return user_ptr;
	}
	catch (const sql::SQLException& e)
	{
		m_pool->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )\n";
		return nullptr;


	}
}
std::shared_ptr<UserInfo> MysqlDAO::GetUser(std::string name)
{
	auto con = m_pool->getConnection();
	if (con == nullptr) {
		return nullptr;
	}

	Defer defer([this, &con]() {
		m_pool->returnConnection(std::move(con));
		});

	try {
		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("SELECT * FROM user WHERE name = ?"));
		pstmt->setString(1, name); // 将uid替换为你要查询的uid

		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		std::shared_ptr<UserInfo> user_ptr = nullptr;
		// 遍历结果集
		while (res->next()) {
			user_ptr.reset(new UserInfo);
			user_ptr->userPwd = res->getString("pwd");
			user_ptr->userEmail = res->getString("email");
			user_ptr->userName = res->getString("name");
			user_ptr->userNick = res->getString("nick");
			user_ptr->userDesc = res->getString("desc");
			user_ptr->userSex = res->getInt("sex");
			user_ptr->uid = res->getInt("uid");
			break;
		}
		return user_ptr;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return nullptr;
	}
}