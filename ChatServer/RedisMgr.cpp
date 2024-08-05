#include "RedisMgr.h"
RedisMgr::~RedisMgr()
{
	Close();
}
RedisMgr::RedisMgr()
{
	auto& gCfgMgr = ConfigMgr::Inst();
	auto host = gCfgMgr["Redis"]["Host"];
	auto port = gCfgMgr["Redis"]["Port"];
	auto passwd = gCfgMgr["Redis"]["Passwd"];
	m_conPool.reset(new RedisConPool(5, host.c_str(), atoi(port.c_str()), passwd.c_str()));
}
 
bool RedisMgr::Get(const std::string& key, std::string& value)
{
	
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "Get %s", key.c_str());
	if (reply == NULL)
	{
		std::cout << "[ Get " << key << " ] failed" << std::endl;
		freeReplyObject(reply);
		return false;
	}
	if (reply->type != REDIS_REPLY_STRING)
	{
		std::cout << "[ GET " << key << " ] failed\n";
		return false;
	}
	value = reply->str;
	freeReplyObject(reply);
	std::cout << "Succeed to execute command [ GET " << key << " ]" << std::endl;
	return true;
}
bool RedisMgr::Set(const std::string& key, const std::string& value)
{
	// 指定 key-value pair， 如果key存在就覆盖旧值
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "SET %s %s", key.c_str(), value.c_str());
	if (NULL == reply)
	{
		std::cout << "Execute command [ SET " << key << " " << value << " ] Failed! \n";
		freeReplyObject(reply);
		return false;
	}
	if (!(reply->type == REDIS_REPLY_STATUS && ((strcmp(reply->str, "OK") == 0 || strcmp(reply->str, "ok")))))
	{
		std::cout << "Execute command [ SET " << key << " " << value << " ] Failed! \n";
		freeReplyObject(reply);
		return false;
	}
	freeReplyObject(reply);
	std::cout << "Execute command [ SET " << key << " " << value << " ] success !\n";
	return true;

}

bool RedisMgr::Auth(const std::string& password)
{
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "AUTH %s", password.c_str());
	if (reply->type == REDIS_REPLY_ERROR)
	{
		std::cout << "Authentication Failure!\n";
		freeReplyObject(reply);
		return false;
	}
	freeReplyObject(reply);
	std::cout << "Authentication Success!\n";
	return  true;
}
bool RedisMgr::LPush(const std::string& key, const std::string& value)
{
	// lpush key v1 v2
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "LPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == reply)
	{
		std::cout << "Execute command [ LPUSH " << key << " " << value << " ] failed!\n";
		freeReplyObject(reply);
		return false;
	}
	if (reply->type != REDIS_REPLY_INTEGER ||reply->integer <= 0)
	{
		std::cout << "Execute command [ LPUSH " << key << " " << value << " ] failed!\n";
		freeReplyObject(reply);
		return false;
	}
	std::cout << "Execute command [ LPUSH " << key << " " << value << " ] succeeded!\n";
	freeReplyObject(reply);
	return true;

}
bool RedisMgr::LPop(const std::string& key, std::string& value)
{
	// lpop key   key: [v1,v2]
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "LPOP %s", key.c_str());
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL)
	{
		std::cout << "Excute command [ LPOP " << key << " ] failed!\n";
		freeReplyObject(reply); 
		return false;
	}
	value = reply->str;
	std::cout << "Execute command [ LPOP " << key << " ] succeeded!\n";
	freeReplyObject(reply);
	return true;
}
bool RedisMgr::RPush(const std::string& key, const std::string& value)
{
	// rpush key value,  key: [v1, v2];
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "RPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == reply)
	{
		std::cout << "Execute command [ RPUSH " << key << " " << value << " ] failed!\n";
		freeReplyObject(reply);
		return false;
	}
	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0)
	{
		std::cout << "Execute command [ RPUSH " << key << " " << value << " ] failed!\n";
		freeReplyObject(reply);
		return false;
	}
	std::cout << "Execute command [ RPUSH " << key << " " << value << " ] succeeded!\n";
	freeReplyObject(reply);
	return true;
}
bool RedisMgr::RPop(const std::string& key, std::string& value)
{
	// pop key  key:[v1,v2]
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "RPOP %s", key.c_str());
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL)
	{
		std::cout << "Excute command [ RPOP " << key << " ] failed!\n";
		freeReplyObject(reply);
		return false;
	}
	value = reply->str;
	std::cout << "Execute command [ RPOP " << key << " ] succeeded!\n";
	freeReplyObject(reply);
	return true;
}
bool RedisMgr::HSet(const std::string& key, std::string hkey, const std::string& value)
{ 
	// 多级key HSET key field value
	// key1: [key2: v1]
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str());
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER)
	{
		std::cout << "Execute command [ HSET " << key << " " << hkey << " ] failed!\n";
		freeReplyObject(reply);
		return false;
	}
	std::cout << "Execute command [ HSET " << key << " " << hkey << " ] succeeded!\n";
	freeReplyObject(reply);
	return true;
	
}
bool RedisMgr::HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
	// 多级key HSET key field value
	// key1: [key2: v1]
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	const char* argv[4];
	size_t argvlen[4];
	argv[0] = "HSET";
	argvlen[0] = 4;

	argv[1] = key;
	argvlen[1] = strlen(key);

	argv[2] = hkey;
	argvlen[2] = strlen(hkey);

	argv[3] = hvalue;
	argvlen[3] = hvaluelen;
	auto reply = (redisReply*)redisCommandArgv(connect, 4, argv, argvlen);
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER)
	{
		std::cout << "Execute command [ HSET " << key << " ] failed!\n";
		freeReplyObject(reply);
		return false;
	}
	std::cout << "Execute command [ KSET " << key << hkey << " " << "] succeeded!\n";
	freeReplyObject(reply);
	return true;
}
std::string RedisMgr::HGet(const std::string& key, const std::string& hkey)
{
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return "";
	}
	const char* argv[3];
	size_t argvlen[3];
	argv[0] = "HGET";
	argvlen[0] = 4;

	argv[1] = key.c_str();
	argvlen[1] = key.length();

	argv[2] = hkey.c_str();
	argvlen[2] = hkey.length();

	
	auto reply = (redisReply*)redisCommandArgv(connect, 3, argv, argvlen);
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL)
	{
		std::cout << "Execute command [ HGET " << key << hkey << " ] failed!\n";
		freeReplyObject(reply);
		return "";
	}
	std::cout << "Execute command [ HSET " << key << hkey << " " << "] succeeded!\n";
	std::string value = reply->str;
	freeReplyObject(reply);
	return value;
}
bool RedisMgr::Del(const std::string& key)
{
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "DEL %s", key.c_str());
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER)
	{
		std::cout << "Execute command [ DEL " << key << " " << "] failed!\n";
		freeReplyObject(reply);
		return false;
	}
	std::cout << "Execute command [ DEL " << key << " " << "] succeeded!\n";
	freeReplyObject(reply);
	return true;
}
bool RedisMgr::ExistsKey(const std::string& key)
{
	auto connect = m_conPool->getConnection();
	if (connect == nullptr)
	{
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "EXISTS %s", key.c_str());
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER || reply->integer == 0)
	{
		std::cout << "Execute command [ EXISTS " << key << " " << "] failed!\n";
		freeReplyObject(reply);
		return false;
	}
	std::cout << "Execute command [ EXISTS " << key << " " << "] succeeded!\n";
	freeReplyObject(reply);
	return true;
}
void RedisMgr::Close()
{
	m_conPool->Close();
}
