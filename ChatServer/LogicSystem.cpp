#include "LogicSystem.h"

LogicSystem::LogicSystem() :is_stop(false)
{
	RegisterCallBack();
	m_worker_thread = std::thread(&LogicSystem::DealMsg, this);
}
LogicSystem::~LogicSystem()
{
	is_stop = true;
	m_consume.notify_one();
	m_worker_thread.join();
}
void LogicSystem::PostMsgToQue(std::shared_ptr<LogicNode> msg)
{
	std::unique_lock<std::mutex> unique_lk(m_mutex);
	m_msg_que.push(msg);
	if (m_msg_que.size() == 1)
	{
		unique_lk.unlock();
		m_consume.notify_one();
	}
}
void LogicSystem::DealMsg()
{
	for (;;)
	{
		std::unique_lock<std::mutex> unique_lk(m_mutex);
		while (m_msg_que.empty() && !is_stop)
		{
			m_consume.wait(unique_lk);
		}
		if (is_stop)
		{
			while (!m_msg_que.empty())
			{
				auto msg_node = m_msg_que.front();
				std::cout << "recv_msg id is " << msg_node->m_recvnode->m_msg_id << std::endl;
				auto call_back_iter = m_func_callbacks.find(msg_node->m_recvnode->m_msg_id);
				if (call_back_iter == m_func_callbacks.end())
				{
					m_msg_que.pop();
					continue;
				}
				call_back_iter->second(msg_node->m_session, msg_node->m_recvnode->m_msg_id,
					std::string(msg_node->m_recvnode->m_data, msg_node->m_recvnode->m_cur_len));
				m_msg_que.pop();
			}
			break;
		}
		auto msg_node = m_msg_que.front();
		std::cout << "recv_msg id is " << msg_node->m_recvnode->m_msg_id << std::endl;
		auto call_back_iter = m_func_callbacks.find(msg_node->m_recvnode->m_msg_id);
		if (call_back_iter == m_func_callbacks.end())
		{
			m_msg_que.pop();
			std::cout << "msg id [" << msg_node->m_recvnode->m_msg_id << "] handler not found " << std::endl;
			continue;
		}
		call_back_iter->second(msg_node->m_session, msg_node->m_recvnode->m_msg_id,
			std::string(msg_node->m_recvnode->m_data, msg_node->m_recvnode->m_cur_len));
		m_msg_que.pop();
	}
}
void LogicSystem::RegisterCallBack()
{
	m_func_callbacks[Msg_IDS::MSG_CHAT_LOGIN] = std::bind(&LogicSystem::LoginHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}
void LogicSystem::LoginHandler(std::shared_ptr<CSession> session, const short& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	auto token = root["token"].asString();
	std::cout << "User login uid is [" << uid << "] user token is [" << token << "]\n";

	Json::Value rtvalue;
	Defer defer([this, &rtvalue, session]
		{
			std::string  return_str = rtvalue.toStyledString();
			session->Send(return_str, Msg_IDS::MSG_CHAT_LOGIN_RSP);
		});
	std::string uid_str = std::to_string(uid);
	std::string token_key = USERTOKENPREFIX + uid_str;
	std::string token_value = "";
	bool success = RedisMgr::GetInstance()->Get(token_key, token_value);
	if (!success)
	{
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}
	if (token_value != token)
	{
		rtvalue["error"] = ErrorCodes::TokenInvalid;
		return;
	}
	rtvalue["error"] = ErrorCodes::Success;
	std::string base_key = USER_BASE_INFO + uid_str;
	auto user_info = std::make_shared<UserInfo>();
	bool b_base = GetBaseInfo(base_key, uid, user_info);
	if (!b_base)
	{
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}
	rtvalue["uid"] = uid;
	rtvalue["pwd"] = user_info->userPwd;
	rtvalue["name"] = user_info->userName;
	rtvalue["email"] = user_info->userEmail;
	rtvalue["nick"] = user_info->nick;
	rtvalue["desc"] = user_info->desc;
	rtvalue["sex"] = user_info->sex;
	rtvalue["icon"] = user_info->icon;

	// 从数据库获取申请列表

	// 获取好友列表

	auto server_name = ConfigMgr::Inst().GetValue("SelfServer", "Name");
	auto rd_res = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server_name);
	int count = 0;
	if (!rd_res.empty())
	{
		count = std::stoi(rd_res);
	}
	count++;
	auto count_str = std::to_string(count);
	std::cout << "server name: " << server_name << std::endl;
	RedisMgr::GetInstance()->HSet(LOGIN_COUNT, server_name, count_str);

	// session 绑定用户id
	session->SetUserId(uid);

	// 为用户设置登录ip server的名字
	std::string ipkey = USERIPPREFIX + uid_str;
	RedisMgr::GetInstance()->Set(ipkey, server_name);

	//uid和session绑定管理，方便以后设计踢人功能
	UserMgr::GetInstance()->SetUserSession(uid, session);
	return;
}

bool LogicSystem::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo)
{
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);
	if (b_base)
	{
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		userinfo->uid = root["uid"].asInt();
		userinfo->userPwd = root["pwd"].asString();
		userinfo->userName = root["name"].asString();
		userinfo->userEmail = root["email"].asString();
		userinfo->nick = root["nick"].asString();
		userinfo->desc = root["desc"].asString();
		userinfo->sex = root["sex"].asInt();
		userinfo->icon = root["icon"].asString();
		std::cout << "user login uid: " << userinfo->uid << ", email: "
			<< userinfo->userName << " pwd: " << userinfo->userPwd << std::endl;
	}
	else
	{
		std::shared_ptr<UserInfo> user_info = nullptr;
		user_info = MysqlMgr::GetInstance()->GetUser(uid);
		if (user_info == nullptr)
		{
			return false;
		}
		userinfo = user_info;
		Json::Value redis_root;
		redis_root["uid"] = uid;
		redis_root["pwd"] = userinfo->userPwd;
		redis_root["name"] = userinfo->userName;
		redis_root["email"] = userinfo->userEmail;
		redis_root["nick"] = userinfo->nick;
		redis_root["desc"] = userinfo->desc;
		redis_root["sex"] = userinfo->sex;
		redis_root["icon"] = userinfo->icon;
		RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
	}
}
