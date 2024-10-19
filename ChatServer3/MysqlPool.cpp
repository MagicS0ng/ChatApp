#include "MysqlPool.h"




MysqlPool::MysqlPool(const std::string & url, const std::string & user, const std::string & pass, const std::string & schema, int poolSize)
	:m_url(url),m_user(user), m_pass(pass), m_schema(schema), m_poolSize(poolSize)
{
	try
	{
		for (int i = 0; i < poolSize; i++)
		{
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
			auto* con = driver->connect(m_url, m_user, m_pass);
			con->setSchema(m_schema);
			auto currentTime = std::chrono::system_clock::now().time_since_epoch();
			long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();
			m_pool.push(std::make_unique<SqlConnection>(con, timestamp));
		}
		m_check_thread = std::thread([this]() {
			while (!m_is_stop)
			{
				checkConnection();
				std::this_thread::sleep_for(std::chrono::seconds(60));
			}
			});
		m_check_thread.detach();

	}
	catch (sql::SQLException &e)
	{
		std::cout << "Mysql pool init error! error is " << e.what();
	}
}
MysqlPool::~MysqlPool()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	while (!m_pool.empty())
	{
		m_pool.pop();
	}
}
void MysqlPool::Close()
{
	m_is_stop = true;
	m_cond.notify_all();
}
void MysqlPool::checkConnection()
{
	std::lock_guard<std::mutex> guard(m_mutex);
	int poolSz = m_pool.size();
	auto currentTime = std::chrono::system_clock::now().time_since_epoch();
	long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();
	for (int i = 0; i < poolSz; i++)
	{
		auto con = std::move(m_pool.front());
		m_pool.pop();
		Defer defer([this, &con]()
			{
				m_pool.push(std::move(con));
			});
		if (timestamp - con->m_last_opera_time < 5)
		{
			continue;
		}
		try
		{
			std::unique_ptr<sql::Statement> stmt(con->m_con->createStatement());
			stmt->executeQuery("SELECT 1");
			con->m_last_opera_time = timestamp;
			std::cout << "execute timer alive query, cur is " << timestamp << std::endl;
		}
		catch (sql::SQLException &e)
		{
			std::cout << "Error keeping  connection alive: " << e.what() << std::endl;
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
			auto* newcon = driver->connect(m_url, m_user, m_pass);
			newcon->setSchema(m_schema);
			con->m_con.reset(newcon);
			con->m_last_opera_time = timestamp;
		}
	}
}
std::unique_ptr<SqlConnection> MysqlPool::getConnection()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_cond.wait(lock, [this]() {
		if (m_is_stop)
		{
			return true;
		}return !m_pool.empty();
		});
	if (m_is_stop)
		return nullptr;
	std::unique_ptr<SqlConnection> con(std::move(m_pool.front()));
	m_pool.pop();
	return con;
}
void  MysqlPool::returnConnection(std::unique_ptr<SqlConnection> con)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_is_stop)
	{
		return;
	}
	m_pool.push(std::move(con));
	m_cond.notify_one();
}
