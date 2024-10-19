#pragma once

#include "const.h"
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/exception.h>
class SqlConnection
{
public:
	SqlConnection(sql::Connection * con, int64_t lasttime):m_con(con), m_last_opera_time(lasttime)
	{}
	std::unique_ptr<sql::Connection> m_con;
	int64_t m_last_opera_time;
};
class MysqlPool
{
public:
	MysqlPool(const std::string& url, const std::string& user, const std::string& pass, const std::string& schema, int poolSize);
	~MysqlPool();
	void Close();
	void checkConnection();
	std::unique_ptr<SqlConnection> getConnection();
	void returnConnection(std::unique_ptr<SqlConnection> con);
private:
	std::string m_url;
	std::string m_user;
	std::string m_pass;
	std::string m_schema;
	std::queue<std::unique_ptr<SqlConnection>> m_pool;
	std::mutex m_mutex;
	std::condition_variable m_cond;
	std::atomic<bool> m_is_stop;
	std::thread m_check_thread;
	int m_poolSize;
};


