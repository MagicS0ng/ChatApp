#pragma once
#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include "CServer.h"
#include <sstream>
#include "LogicNode.h"
#include "LogicSystem.h" 
#include "MsgNode.h"
#include "const.h"
class CServer;
class LogicSystem;
class MsgNode;
class LogicNode;
class CSession: public std::enable_shared_from_this<CSession>
{
	using tcp = boost::asio::ip::tcp;
public:
	CSession(boost::asio::io_context & io_context, CServer * server);
	~CSession();
	tcp::socket &GetSocket();
	std::string& GetSessionId();
	void SetUserId(int uid);
	int GetUserId();
	void Start();
	void Send(std::string msg, short msgid);
	void Send(char * msg, short max_length,short msgid);
	void Close();
	std::shared_ptr<CSession> SharedSelf();
	void AsyncReadBody(int);
	void AsyncReadHead(int);

	
private:
	void AsyncReadFull(std::size_t maxLength, std::function<void(const boost::system::error_code&, std::size_t) > handler);
	void AsyncReadLen(std::size_t read_len, std::size_t total_len, std::function<void(const boost::system::error_code&, std::size_t)> handler);
	void HandleWrite(const boost::system::error_code &error, std::shared_ptr<CSession> shared_self);

private:
	
	tcp::socket m_socket;
	std::string m_sessionid;
	int m_userid;
	char m_data[ChatSet::MAX_LENGTH];
	CServer * m_server;
	bool is_close ;
	bool is_head_parse ;
	std::queue<std::shared_ptr<SendNode>> m_send_que;
	std::mutex m_send_lock;
	std::shared_ptr<RecvNode> m_recv_msg_node;
	std::shared_ptr<MsgNode> m_recv_head_node;
};

