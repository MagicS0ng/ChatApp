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
bool MysqlDAO::AddFriendReply(const int& uid, const int& touid)
{
	auto con = m_pool->getConnection();
	if (con == nullptr)
	{
		return false;
	}
	Defer defer([this, &con]
	{
		m_pool->returnConnection(std::move(con));
	});
	try
	{
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement(
		"INSERT INTO friend_apply (from_uid, to_uid) values (?, ?)"
		"ON DUPLICATE KEY UPDATE from_uid = from_uid, to_uid = to_uid"
		));
		pstmt->setInt(1, uid);
		pstmt->setInt(2, touid);
		int rowAffected = pstmt->executeUpdate();
		if (rowAffected < 0)
		{
			return false;
		}
		return true;
	}
	catch (sql::SQLException& e)
	{
		m_pool->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )\n";
		return false;
	}
	return true;
}
bool MysqlDAO::AuthFriendApply(const int& from, const int& to)
{
	auto con = m_pool->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		m_pool->returnConnection(std::move(con));
		});

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("UPDATE friend_apply SET status = 1 "
			"WHERE from_uid = ? AND to_uid = ?"));
		pstmt->setInt(1, to); // from id
		pstmt->setInt(2, from);
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
bool MysqlDAO::AddFriend(const int& from, const int& to, std::string back_name)
{
	auto con = m_pool->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		m_pool->returnConnection(std::move(con));
		});

	try {

		con->m_con->setAutoCommit(false);

		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
			"VALUES (?, ?, ?) "
		));
		pstmt->setInt(1, from); // from id
		pstmt->setInt(2, to);
		pstmt->setString(3, back_name);
		int rowAffected = pstmt->executeUpdate();
		if (rowAffected < 0) {
			con->m_con->rollback();
			return false;
		}

		std::unique_ptr<sql::PreparedStatement> pstmt2(con->m_con->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
			"VALUES (?, ?, ?) "
		));
		pstmt2->setInt(1, to); // from id
		pstmt2->setInt(2, from);
		pstmt2->setString(3, "");
		int rowAffected2 = pstmt2->executeUpdate();
		if (rowAffected2 < 0) {
			con->m_con->rollback();
			return false;
		}

		con->m_con->commit();
		std::cout << "addfriend insert friends success" << std::endl;

		return true;
	}
	catch (sql::SQLException& e) {
		if (con) {
			con->m_con->rollback();
		}
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}


	return true;
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
			user_ptr->nick = res->getString("nick");
			user_ptr->desc = res->getString("desc");
			user_ptr->sex = res->getInt("sex");
			user_ptr->icon = res->getString("icon");
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
	if (con == nullptr)
	{
		return nullptr;
	}
	Defer defer([this, &con]()
		{
			m_pool->returnConnection(std::move(con));
		});
	try
	{
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("SELECT * FROM user WHERE name = ?"));
		pstmt->setString(1, name);
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		std::unique_ptr<UserInfo> user_ptr = nullptr;
		while (res->next())
		{
			user_ptr.reset(new UserInfo);
			user_ptr->uid = res->getInt("uid");
			user_ptr->userEmail = res->getString("email");
			user_ptr->userName = res->getString("name");
			user_ptr->nick = res->getString("nick");
			user_ptr->desc = res->getString("desc");
			user_ptr->sex = res->getInt("sex");
			user_ptr->icon = res->getString("icon");
			break;
		}return user_ptr;
	}
	catch(sql::SQLException & e)
	{
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
		return nullptr;
	}
}

bool MysqlDAO::GetApplyList(int touid, std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit)
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
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement(
			"select apply.from_uid, apply.status, user.name, "
			"user.nick, user.sex from friend_apply as apply join user on apply.from_uid = user.uid where apply.to_uid = ? "
			"and apply.id > ? order by apply.id ASC LIMIT ? "));
		pstmt->setInt(1, touid);
		pstmt->setInt(2, begin);
		pstmt->setInt(3, limit);
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		
		while (res->next())
		{
			auto name = res->getString("name");
			auto uid = res->getInt("from_uid");
			auto status = res->getInt("status");
			auto nick = res->getString("nick");
			auto sex = res->getInt("sex");
			auto apply_ptr = std::make_shared<ApplyInfo>(uid, name, "", "", nick, sex, status);
			applyList.push_back(apply_ptr);
		}
		return true;
	}
	catch (sql::SQLException& e)
	{
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
		return false;
	}
}

bool MysqlDAO::GetFriendList(int self_id, std::vector<std::shared_ptr<UserInfo>>& user_info_list)
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
		std::unique_ptr<sql::PreparedStatement> pstmt(con->m_con->prepareStatement("select * from friend where self_id = ? "));

		pstmt->setInt(1, self_id);
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		while (res->next()) {
			auto friend_id = res->getInt("friend_id");
			auto back = res->getString("back");
			auto user_info = GetUser(friend_id);
			if (user_info == nullptr) {
				continue;
			}

			user_info->back = user_info->userName;
			user_info_list.push_back(user_info);
		}
		return true;
	}
	catch (sql::SQLException& e)
	{
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
		return false;
	}
}
