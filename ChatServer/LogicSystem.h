#pragma once
#include "CSession.h"
#include "const.h"
#include "StatusGrpcClient.h"
#include "MysqlMgr.h"
#include "LogicNode.h"
#include "RedisMgr.h"
#include "UserMgr.h"
#include "ChatGrpcClient.h"

class LogicNode;
typedef std::function<void(std::shared_ptr<CSession>, const short& msg_id, const std::string& msg_data)> FunCallBack;
class LogicSystem :public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();
	void PostMsgToQue(std::shared_ptr<LogicNode> msg);
private:
	LogicSystem();
	void DealMsg();
	void RegisterCallBack();
	void LoginHandler(std::shared_ptr<CSession> session, const short& msg_id, const std::string& msg_data);
	void SearchInfo(std::shared_ptr<CSession>, const short &, const std::string &);
	void AddFriendApply(std::shared_ptr<CSession>, const short&, const std::string&);
	void AuthFriendApply(std::shared_ptr<CSession>session, const short& msg_id, const std::string& msg_data);
	bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo);
	bool isPureDigit(const std::string& str);
	void GetUserByName(const std::string & name, Json::Value &rtvalue);
	void GetUserByUid(const std::string & uid_str, Json::Value &rtvalue);
	bool GetFriendApplyInfo(int to_uid, std::vector<std::shared_ptr<ApplyInfo>>& list);
	bool GetFriendList(int, std::vector<std::shared_ptr<UserInfo>>&);
private:
	std::thread m_worker_thread;
	std::queue < std::shared_ptr<LogicNode>> m_msg_que;
	std::mutex m_mutex;
	std::condition_variable m_consume;
	bool is_stop;
	std::map<short, FunCallBack> m_func_callbacks;
	//std::unordered_map<int, std::shared_ptr<UserInfo>> m_users;
};