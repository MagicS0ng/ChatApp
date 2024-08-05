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
					std::string(msg_node->m_recvnode->m_data,msg_node->m_recvnode->m_cur_len));
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
	std::cout << "User login uid is [" << uid << "] user token is [" << root["token"].asString() << "]\n";
	auto rsp = StatusGrpcClient::GetInstance()->Login(uid, root["token"].asString());
	Json::Value rtvalue;
	Defer defer([this, &rtvalue, session]()
		{
			std::string return_str = rtvalue.toStyledString();
			session->Send(return_str, Msg_IDS::MSG_CHAT_LOGIN_RSP);
		});
	rtvalue["error"] = rsp.error();
	if (rsp.error() != ErrorCodes::Success)
	{
		return;
	}
	auto find_iter = m_users.find(uid);
	std::shared_ptr<UserInfo> user_info = nullptr;
	if (find_iter == m_users.end())
	{
		user_info = MysqlMgr::GetInstance()->GetUser(uid);
		if (user_info == nullptr)
		{
			rtvalue["error"] = ErrorCodes::UidInvalid;
			return;
		}
		m_users[uid] = user_info;
	}
	else
	{
		user_info = find_iter->second;
	}
	rtvalue["uid"] = uid;
	rtvalue["token"] = rsp.token();
	rtvalue["name"] = user_info->userName;
	std::cout << "uid: [" << uid << "], token: [" << rsp.token() << "], name: [" << user_info->userName<< "]" << std::endl;

}