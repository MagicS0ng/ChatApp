#pragma once
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include "Singleton.h"
#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "hiredis.h"
#include <cassert>
#include <queue>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>


struct UserInfo
{
	std::string userName;
	std::string userPwd;
	std::string userEmail;
	int uid;
};
#define CODEPREFIX "code_"
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

enum ChatSet
{
	MAX_LENGTH = 2048, HEAD_TOTAL_LEN = 4, HEAD_ID_LEN = 2, HEAD_DATA_LEN = 2, MAX_RECVQUE = 10000, MAX_SENDQUE = 1000
};
enum Msg_IDS
{
	MSG_CHAT_LOGIN=1005,
	MSG_CHAT_LOGIN_RSP=1006,
};
//class ConfigMgr;
enum ErrorCodes {
	Success = 0,
	ErrorJson = 1001,
	RPCFailed = 1002,
	VarifyExpired = 1003,
	VarifyCodeErr = 1004,
	UserExist = 1005,
	PasswdErr = 1006,
	EmailNotMatch = 1007,
	PasswdUpFailed = 1008,
	PasswdInvalid = 1009,
	//RPCGetFailed = 1010,
	TokenInvalid = 1010,
	UidInvalid = 1011,
};
class Defer
{
public:
	Defer(std ::function<void()> func): m_func(func){}
	~Defer()
	{
		m_func();
	}
private:
	std::function<void()> m_func;
};