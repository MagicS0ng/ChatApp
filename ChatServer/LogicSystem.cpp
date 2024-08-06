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
	m_func_callbacks[Msg_IDS::ID_SEARCH_USER_REQ] = std::bind(&LogicSystem::SearchInfo, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	m_func_callbacks[Msg_IDS::ID_ADD_FRIEND_REQ] = std::bind(&LogicSystem::AddFriendApply, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
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

	// �����ݿ��ȡ�����б�

	// ��ȡ�����б�

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

	// session ���û�id
	session->SetUserId(uid);

	// Ϊ�û����õ�¼ip server������
	std::string ipkey = USERIPPREFIX + uid_str;
	RedisMgr::GetInstance()->Set(ipkey, server_name);

	//uid��session�󶨹��������Ժ�������˹���
	UserMgr::GetInstance()->SetUserSession(uid, session);
	return;
}

void LogicSystem::SearchInfo(std::shared_ptr<CSession> session, const short& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid_str = root["uid"].asString();
	std::cout << "user SearchInfo uid is " << uid_str << std::endl;
	Json::Value rtvalue;
	Defer defer([this, &rtvalue, session]()
		{
			std::string return_str = rtvalue.toStyledString();
			session->Send(return_str, Msg_IDS::ID_SEARCH_USER_RSP);
		});
	bool b_digit = isPureDigit(uid_str);
	if (b_digit)
	{
		GetUserByUid(uid_str, rtvalue);
	}
	else
	{
		GetUserByName(uid_str, rtvalue);
	}
}

void LogicSystem::AddFriendApply(std::shared_ptr<CSession>session, const short& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	auto applyname = root["applyname"].asString();
	auto bakname = root["bakname"].asString();
	auto touid = root["touid"].asInt();
	std::cout << "send";

	Json::Value rtvalue;
	rtvalue["error"] = ErrorCodes::Success;
	Defer defer([this, &rtvalue, session]
		{
			std::string return_str = rtvalue.toStyledString();
			session->Send(return_str, Msg_IDS::ID_ADD_FRIEND_RSP);
		});
	MysqlMgr::GetInstance()->AddFriendReply(uid, touid);

	auto to_str = std::to_string(touid);
	auto to_ip_key = USERIPPREFIX + to_str;
	std::string to_ip_value = "";
	bool b_ip = RedisMgr::GetInstance()->Get(to_ip_key, to_ip_value);
	if (!b_ip)
	{
		return;
	}
	auto& cfg = ConfigMgr::Inst();
	auto self_name = cfg["SelfServer"]["Name"];
	if (to_ip_value == self_name)
	{
		auto session = UserMgr::GetInstance()->GetSession(touid);
		if (session)
		{
			Json::Value notify;
			notify["error"] = ErrorCodes::Success;
			notify["applyuid"] = uid;
			notify["name"] = applyname;
			notify["desc"] = "";
			std::string return_str = notify.toStyledString();
			session->Send(return_str, Msg_IDS::ID_NOTIFY_ADD_FRIEND_REQ);
		}
		return;
	}
	std::string base_key = USER_BASE_INFO + std::to_string(uid);
	auto apply_info = std::make_shared<UserInfo>();
	bool b_info = GetBaseInfo(base_key, uid, apply_info);

	AddFriendReq add_req;
	add_req.set_applyuid(uid);
	add_req.set_touid(uid);
	add_req.set_name(applyname);
	add_req.set_desc("");
	if (b_info)
	{
		add_req.set_icon(apply_info->icon);
		add_req.set_sex(apply_info->sex);
		add_req.set_nick(apply_info->nick);
	}
	ChatGrpcClient::GetInstance()->NotifyAddFriend(to_ip_value, add_req);

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

bool LogicSystem::isPureDigit(const std::string& str)
{
	for (auto& c : str)
	{
		if (!std::isdigit(c))
		{
			return false;
		}
	}
	return true;
}

void LogicSystem::GetUserByName(const std::string& name, Json::Value& rtvalue)
{
	rtvalue["error"] = ErrorCodes::Success;

	std::string base_key = NAME_INFO + name;

	//���Ȳ�redis�в�ѯ�û���Ϣ
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		auto uid = root["uid"].asInt();
		auto name = root["name"].asString();
		auto pwd = root["pwd"].asString();
		auto email = root["email"].asString();
		auto nick = root["nick"].asString();
		auto desc = root["desc"].asString();
		auto sex = root["sex"].asInt();
		std::cout << "user  uid is  " << uid << " name  is "
			<< name << " pwd is " << pwd << " email is " << email << std::endl;

		rtvalue["uid"] = uid;
		rtvalue["pwd"] = pwd;
		rtvalue["name"] = name;
		rtvalue["email"] = email;
		rtvalue["nick"] = nick;
		rtvalue["desc"] = desc;
		rtvalue["sex"] = sex;
		return;
	}

	//redis��û�����ѯmysql
	//��ѯ���ݿ�
	std::shared_ptr<UserInfo> user_info = nullptr;
	user_info = MysqlMgr::GetInstance()->GetUser(name);
	if (user_info == nullptr) {
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}

	//�����ݿ�����д��redis����
	Json::Value redis_root;
	redis_root["uid"] = user_info->uid;
	redis_root["pwd"] = user_info->userPwd;
	redis_root["name"] = user_info->userName;
	redis_root["email"] = user_info->userEmail;
	redis_root["nick"] = user_info->nick;
	redis_root["desc"] = user_info->desc;
	redis_root["sex"] = user_info->sex;

	RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
	//auto server_name = ConfigMgr::Inst().GetValue("SelfServer", "Name");
	//����¼��������
	/*auto rd_res = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server_name);
	int count = 0;
	if (!rd_res.empty()) {
		count = std::stoi(rd_res);
	}

	count++;
	auto count_str = std::to_string(count);
	RedisMgr::GetInstance()->HSet(LOGIN_COUNT, server_name, count_str);*/

	//��������
	rtvalue["uid"] = user_info->uid;
	rtvalue["pwd"] = user_info->userPwd;
	rtvalue["name"] = user_info->userName;
	rtvalue["email"] = user_info->userEmail;
	rtvalue["nick"] = user_info->nick;
	rtvalue["desc"] = user_info->desc;
	rtvalue["sex"] = user_info->sex;

}

void LogicSystem::GetUserByUid(const std::string& uid_str, Json::Value& rtvalue)
{
	rtvalue["error"] = ErrorCodes::Success;
	std::string base_key = USER_BASE_INFO + uid_str;
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);
	if (b_base)
	{
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		auto uid = root["uid"].asInt();
		auto userPwd = root["pwd"].asString();
		auto userName = root["name"].asString();
		auto userEmail = root["email"].asString();
		auto nick = root["nick"].asString();
		auto desc = root["desc"].asString();
		auto sex = root["sex"].asInt();
		auto icon = root["icon"].asString();
		std::cout << "user login uid: " << uid << ", email: "
			<< userName << " pwd: " << userPwd << std::endl;
		rtvalue["uid"] = uid;
		rtvalue["pwd"] = userPwd;
		rtvalue["name"] = userName;
		rtvalue["email"] = userEmail;
		rtvalue["nick"] = nick;
		rtvalue["desc"] = desc;
		rtvalue["sex"] = sex;
		rtvalue["icon"] = icon;
		return;
	}
	auto uid = std::stoi(uid_str);
	std::shared_ptr<UserInfo> user_info = nullptr;
	user_info = MysqlMgr::GetInstance()->GetUser(uid);
	if (user_info == nullptr)
	{
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}
	Json::Value redis_root;
	redis_root["uid"] = uid;
	redis_root["pwd"] = user_info->userPwd;
	redis_root["name"] = user_info->userName;
	redis_root["email"] = user_info->userEmail;
	redis_root["nick"] = user_info->nick;
	redis_root["desc"] = user_info->desc;
	redis_root["sex"] = user_info->sex;
	redis_root["icon"] = user_info->icon;
	RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
	rtvalue["uid"] = uid;
	rtvalue["pwd"] = user_info->userPwd;
	rtvalue["name"] = user_info->userName;
	rtvalue["email"] = user_info->userEmail;
	rtvalue["nick"] = user_info->nick;
	rtvalue["desc"] = user_info->desc;
	rtvalue["sex"] = user_info->sex;
	rtvalue["icon"] = user_info->icon;

}
