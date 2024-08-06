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
	UserInfo()
		:userName(""), userPwd(""), userEmail(""),
		nick(""), desc(""), sex(0), icon(""), uid(0) {}
	std::string userName;
	std::string userPwd;
	std::string userEmail;
	std::string nick;
	std::string desc;
	int sex;
	std::string icon;
	int uid;
};
struct ApplyInfo
{
	ApplyInfo(int uid, std::string name, std::string desc, std::string icon, std::string nick, int sex, int status)
		:_uid(uid), _name(name), _desc(desc),_icon(icon),_nick(nick),_sex(sex), _status(status)
	{
	}
	int _uid;
	std::string _name;
	std::string _desc;
	std::string _icon;
	std::string _nick;
	int _sex;
	int _status;
};
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
	MSG_CHAT_LOGIN = 1005,
	MSG_CHAT_LOGIN_RSP = 1006,
	ID_SEARCH_USER_REQ = 1007,
	ID_SEARCH_USER_RSP = 1008,
	ID_ADD_FRIEND_REQ = 1009,
	ID_ADD_FRIEND_RSP = 1010,
	ID_NOTIFY_ADD_FRIEND_REQ = 1011,
	ID_AUTH_FRIEND_REQ = 1013,
	ID_AUTH_FRIEND_RSP = 1014,
	ID_NOTIFY_AUTH_FRIEND_REQ = 1015,
	ID_TEXT_CHAT_MSG_REQ = 1017,
	ID_TEXT_CHAT_MSG_RSP = 1018,
	ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019

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
const std::string LOGIN_COUNT = "logincount";
const std::string USERIPPREFIX = "uip_";
const std::string USERTOKENPREFIX = "utoken_";
const std::string IPCOUNTPREFIX = "ipcount_";
const std::string USER_BASE_INFO = "ubaseinfo_";
const std::string NAME_INFO = "unameinfo_";
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