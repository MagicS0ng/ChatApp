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
int MysqlDAO::RegUserTransaction(const std::string& name, const std::string& email, const std::string& pwd)
{
	auto con = m_pool->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con] {
		m_pool->returnConnection(std::move(con));
		});

	try {
		//开始事务
		con->m_con->setAutoCommit(false);
		//执行第一个数据库操作，根据email查找用户
			// 准备查询语句

		std::unique_ptr<sql::PreparedStatement> pstmt_email(con->m_con->prepareStatement("SELECT 1 FROM user WHERE email = ?"));

		// 绑定参数
		pstmt_email->setString(1, email);

		// 执行查询
		std::unique_ptr<sql::ResultSet> res_email(pstmt_email->executeQuery());

		auto email_exist = res_email->next();
		if (email_exist) {
			con->m_con->rollback();
			std::cout << "email " << email << " exist";
			return 0;
		}

		// 准备查询用户名是否重复
		std::unique_ptr<sql::PreparedStatement> pstmt_name(con->m_con->prepareStatement("SELECT 1 FROM user WHERE name = ?"));

		// 绑定参数
		pstmt_name->setString(1, name);

		// 执行查询
		std::unique_ptr<sql::ResultSet> res_name(pstmt_name->executeQuery());

		auto name_exist = res_name->next();
		if (name_exist) {
			con->m_con->rollback();
			std::cout << "name " << name << " exist";
			return 0;
		}

		// 准备更新用户id
		std::unique_ptr<sql::PreparedStatement> pstmt_upid(con->m_con->prepareStatement("UPDATE user_id SET id = id + 1"));

		// 执行更新
		pstmt_upid->executeUpdate();

		// 获取更新后的 id 值
		std::unique_ptr<sql::PreparedStatement> pstmt_uid(con->m_con->prepareStatement("SELECT id FROM user_id"));
		std::unique_ptr<sql::ResultSet> res_uid(pstmt_uid->executeQuery());
		int newId = 0;
		// 处理结果集
		if (res_uid->next()) {
			newId = res_uid->getInt("id");
		}
		else {
			std::cout << "select id from user_id failed" << std::endl;
			con->m_con->rollback();
			return -1;
		}

		// 插入user信息
		std::unique_ptr<sql::PreparedStatement> pstmt_insert(con->m_con->prepareStatement("INSERT INTO user (uid, name, email, pwd) VALUES (?, ?, ?, ?)"));
		pstmt_insert->setInt(1, newId);
		pstmt_insert->setString(2, name);
		pstmt_insert->setString(3, email);
		pstmt_insert->setString(4, pwd);
		//执行插入
		pstmt_insert->executeUpdate();
		// 提交事务
		con->m_con->commit();
		std::cout << "newuser insert into user success" << std::endl;
		return newId;
	}
	catch (sql::SQLException& e) {
		// 如果发生错误，回滚事务
		if (con) {
			con->m_con->rollback();
		}
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
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
		return false;
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
		userInfo.userEmail = res->getString("email");
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
UserInfo MysqlDAO::SearchUser(const std::string& name, bool& isExist)
{
	UserInfo userInfo;
	userInfo.userName = "";
	userInfo.userPwd = "";
	userInfo.userEmail = "";
	userInfo.uid = -1;
	auto con = m_pool->getConnection();
	try
	{
		if (con == nullptr)
		{
			return std::move(userInfo);
		}
		std::unique_ptr<sql::PreparedStatement> stmt(con->m_con->prepareStatement("SELECT * FROM user WHERE name = ?"));

		stmt->setString(1, name);
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		if (res->next())
		{
			int uid = res->getInt("uid");
			std::string name = res->getString("name");
			std::string email = res->getString("email");
			std::cout << "Search Result: uid:[" << uid << "], name: [" << name << "], email: [" << email << "]";
			userInfo.uid = uid;
			userInfo.userName = name;
			userInfo.userEmail = email;
			userInfo.userPwd = "";
			isExist = true;
			return std::move(userInfo);
		}
		m_pool->returnConnection(std::move(con));
		return std::move(userInfo);
	}
	catch (sql::SQLException& e)
	{
		m_pool->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )\n";
		return std::move(userInfo);
	}
}