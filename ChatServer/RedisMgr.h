#pragma once
#include "const.h"
#include "ConfigMgr.h"

class RedisConPool
{

private:
	std::atomic<bool> m_stop;
	size_t m_poolSize;
	const char * m_host;
	int m_port;
	const char* pwd_;

	std::queue<redisContext*> m_connections;
	std::mutex m_mutex;
	std::condition_variable m_cond;
	std::thread check_thread_;
	int counter_;
private:
	void checkThread()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_stop)
		{
			return;
		}
		auto poolSize = m_connections.size();
		for (int i = 0; i < poolSize && !m_stop; i++)
		{
			auto* context = m_connections.front();
			m_connections.pop();
			try
			{
				auto reply = (redisReply*)redisCommand(context, "PING");
				freeReplyObject(reply);
				m_connections.push(context);

			}
			catch (std::exception& e)
			{
				std::cout << "Error keeping connection alive: " << e.what() << std::endl;
				redisFree(context);
				context = redisConnect(m_host, m_port);
				if (context == nullptr || context->err != 0)
				{
					if (context != nullptr)
					{
						redisFree(context);
					}
					continue;
				}
				auto reply = (redisReply*)redisCommand(context, "AUTH &s", pwd_);
				if (reply->type == REDIS_REPLY_ERROR)
				{
					std::cout << "Authentication Failure" << std::endl;
					freeReplyObject(reply);
					continue;
				}
				freeReplyObject(reply);
				std::cout << "Authentication Success" << std::endl;
				m_connections.push(context);
			}
		}

	}
public:
	RedisConPool(size_t poolSize, const char* host, int port, const char* pwd) :
		m_poolSize(poolSize), m_host(host), m_port(port), m_stop(false), pwd_(pwd), counter_(0)
	{
		for (size_t i = 0; i < m_poolSize; i++)
		{
			auto* context = redisConnect(host, port);
			if (context == nullptr || context->err != 0)
			{
				if (context != nullptr)
				{
					redisFree(context);
				}
				continue;
			}
			auto reply = (redisReply*)redisCommand(context, "AUTH %s", pwd);
			if (reply->type == REDIS_REPLY_ERROR)
			{
				std::cout << "Authentication Failure!\n";
				freeReplyObject(reply);
				redisFree(context);
				continue;
			}
			freeReplyObject(reply);
			std::cout << "Autentication Success!\n";
			m_connections.push(context);
		}
		check_thread_ = std::thread([this]() {


			while (!m_stop)
			{
				counter_++;
				if (counter_ >= 60)
				{
					checkThread();
					counter_ = 0;
				}
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			});
		
	}
	~RedisConPool()
	{
		
	}
	void ClearConnection()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		while (!m_connections.empty())
		{
			auto* context = m_connections.front();
			redisFree(context);
			m_connections.pop();
		}
	}
	redisContext* getConnection()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cond.wait(lock, [this]
			{
				if (m_stop)
				{
					return true;
				}
				return !m_connections.empty();
			});
		if (m_stop)
			return nullptr;
		auto* context = m_connections.front();
		m_connections.pop();
		return context;
	}
	void returnConnection(redisContext * context)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_stop)
		{
			return;
		}
		m_connections.push(context);
		m_cond.notify_one();
	}
	void Close()
	{
		m_stop = true;
		m_cond.notify_all();
		check_thread_.join();
	}
};


class RedisMgr :public Singleton<RedisMgr>
{
	friend class Singleton<RedisMgr>;
public:
	~RedisMgr();
	bool Get(const std::string& key, std::string& value);
	bool Set(const std::string& key, const std::string& value);
	bool Auth(const std::string& password);
	bool LPush(const std::string& key, const std::string& value);
	bool LPop(const std::string& key, std::string& value);
	bool RPush(const std::string& key, const std::string& value);
	bool RPop(const std::string &key, std::string &value);
	bool HSet(const std::string &key,std::string hkey, const std::string &value);
	bool HSet(const char *key, const char *hkey, const char * hvalue, size_t hvaluelen);
	bool HDel(const std::string& key, const std::string& field);
	std::string HGet(const std::string &key, const std::string &hkey);
	bool Del(const std::string &key);
	bool ExistsKey(const std::string &key);
	void Close();
private:
	RedisMgr();
	/*redisContext* m_connect;
	redisReply* m_reply;*/

	std::unique_ptr<RedisConPool> m_conPool;

};