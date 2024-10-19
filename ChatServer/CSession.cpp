#include "CSession.h"
CSession::CSession(boost::asio::io_context& io_context, CServer* server) :m_socket(io_context),  m_server(server),
is_close(false), is_head_parse(false)
{
	::memset(m_data, 0, ChatSet::MAX_LENGTH);
	boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
	m_sessionid = boost::uuids::to_string(a_uuid);
	m_recv_head_node = std::make_shared<MsgNode>(ChatSet::HEAD_TOTAL_LEN);
}

CSession::~CSession()
{
	std::cout << "~CSession destruct\n";
}
tcp::socket& CSession::GetSocket()
{
	return m_socket;
}
std::string& CSession::GetSessionId()
{
	return m_sessionid;
}
void CSession::SetUserId(int uid)
{
	m_userid = uid;
}
int CSession::GetUserId()
{
	return m_userid;
}
void CSession::Start()
{
	AsyncReadHead(ChatSet::HEAD_TOTAL_LEN);
}

void CSession::Send(std::string msg, short msgid)
{
	std::lock_guard<std::mutex> lock(m_send_lock);
	int send_que_size = m_send_que.size();
	if (send_que_size > ChatSet::MAX_SENDQUE)
	{
		std::cout << "Session: " << m_sessionid << " send queue filled, size is [" << ChatSet::MAX_SENDQUE << "] " << std::endl;
		return;
	}
	m_send_que.push(std::make_shared<SendNode>(msg.c_str(), msg.length(), msgid));
	if (send_que_size > 0) 
	{
		return;
	}
	auto& msgNode = m_send_que.front();
	boost::asio::async_write(m_socket, boost::asio::buffer(msgNode->m_data, msgNode->m_total_len),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, SharedSelf()));
}
void CSession::Send(char * msg, short max_length,short msgid)
{
	std::lock_guard<std::mutex> lock(m_send_lock);
	int send_que_size = m_send_que.size();
	if (send_que_size > MAX_SENDQUE)
	{
		std::cout << "Session: " << m_sessionid << " send queue filled, size is [" << ChatSet::MAX_SENDQUE << "] " << std::endl;
		return;
	}
	m_send_que.push(std::make_shared<SendNode>(msg, max_length , msgid));
	if (send_que_size > 0) // 保证同一个时刻，只有一个异步写操作执行，使用队列，保证顺序
	{
		return;
	}
	auto& msgNode = m_send_que.front();
	boost::asio::async_write(m_socket, boost::asio::buffer(msgNode->m_data, msgNode->m_total_len),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, SharedSelf()));
}
void CSession::Close()
{
	m_socket.close();
	is_close = true;
}

std::shared_ptr<CSession>CSession::SharedSelf()
{
	return shared_from_this();
}
void CSession::AsyncReadBody(int total_len)
{
	auto self = shared_from_this();
	AsyncReadFull(total_len, [self, this, total_len](const boost::system::error_code& ec, std::size_t bytes_transfered) {
		try
		{
			if (ec)
			{
				std::cout << "handle read failed, error is " << ec.what() << std::endl;
				Close();
				m_server->ClearSession(m_sessionid);
				return;
			}
			if (bytes_transfered < total_len)
			{
				std::cout << "read length not match, read [" << bytes_transfered << "], total [" << total_len << "]" << std::endl;
				Close();
				m_server->ClearSession(m_sessionid);
				return;
			}
			memcpy(m_recv_msg_node->m_data, m_data, bytes_transfered);
			m_recv_msg_node->m_cur_len += bytes_transfered;
			m_recv_msg_node->m_data[m_recv_msg_node->m_total_len] = '\0';
			std::cout << "receive data is [" << m_recv_msg_node->m_data << "]" << std::endl;
			LogicSystem::GetInstance()->PostMsgToQue(std::make_shared<LogicNode>(shared_from_this(), m_recv_msg_node));
			AsyncReadHead(ChatSet::HEAD_TOTAL_LEN);
		}

		catch (const std::exception& e)
		{
			std::cout << "Exception code is [" << e.what() << "]" << std::endl;
		}
		});
}


void CSession::AsyncReadHead(int total_len)
{
	auto self = shared_from_this();
	AsyncReadFull(HEAD_TOTAL_LEN, [self, this](const boost::system::error_code& ec, std::size_t bytes_transfered)
		{
			try
			{
				if (ec)
				{
					std::cout << "handle read failed, error is " << ec.what() << std::endl;
					Close();
					m_server->ClearSession(m_sessionid);
					return;
				}
				if (bytes_transfered < ChatSet::HEAD_TOTAL_LEN)
				{
					std::cout << "read length not match, read [" << bytes_transfered << "], total [" << ChatSet::HEAD_TOTAL_LEN << "]" << std::endl;
					Close();
					m_server->ClearSession(m_sessionid);
					return;
				}
				m_recv_head_node->Clear();
				memcpy(m_recv_head_node->m_data, m_data, bytes_transfered);

				short msg_id = 0;
				memcpy(&msg_id, m_recv_head_node->m_data, ChatSet::HEAD_ID_LEN); //拷贝 m_data的前HEAD_ID_LEN个，到msg_id的地址，为msg_id赋值
				msg_id = boost::asio::detail::socket_ops::network_to_host_short(msg_id); // 转换字节序
				std::cout << "msg id is [" << msg_id << "]" << std::endl;
				if (msg_id > MAX_LENGTH)
				{
					std::cout << "invalid msg_id is [" << msg_id << "]" << std::endl;
					m_server->ClearSession(m_sessionid);
					return;
				}
				short msg_len = 0;
				memcpy(&msg_len, m_recv_head_node->m_data + ChatSet:: HEAD_ID_LEN, ChatSet::HEAD_DATA_LEN);
				msg_len = boost::asio::detail::socket_ops::network_to_host_short(msg_len);
				std::cout << "msg len is [" << msg_len << "]" << std::endl;
				if (msg_len > MAX_LENGTH)
				{
					std::cout << "invalid msg len is [" << msg_len << "]" << std::endl;
					m_server->ClearSession(m_sessionid);
					return;
				}
				m_recv_msg_node = std::make_shared<RecvNode>(msg_len, msg_id);
				AsyncReadBody(msg_len);
			}
			catch (const std::exception& e)
			{
				std::cout << "Exception code is " << e.what() << std::endl;
			}
		});
}
void CSession::HandleWrite(const boost::system::error_code& error, std::shared_ptr<CSession> shared_self)
{
	try
	{
		if (!error)
		{
			std::lock_guard<std::mutex> lock(m_send_lock);
			m_send_que.pop();
			if (!m_send_que.empty())
			{
				auto& msgNode = m_send_que.front();
				boost::asio::async_write(m_socket, boost::asio::buffer(msgNode->m_data, msgNode->m_total_len),
					std::bind(&CSession::HandleWrite, this, std::placeholders::_1, shared_self));
			}
		}
		else
		{
			std::cout << "handle write failed, error is " << error.what() << std::endl;
			Close();
			m_server->ClearSession(m_sessionid);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception Code: [" << e.what() << "]" << std::endl;
	}
}
void CSession::AsyncReadFull(std::size_t maxLength, std::function<void(const boost::system::error_code&, std::size_t) > handler)
{
	::memset(m_data, 0, MAX_LENGTH);
	AsyncReadLen(0, maxLength, handler);
}
void CSession::AsyncReadLen(std::size_t read_len, std::size_t total_len, 	std::function<void(const boost::system::error_code &, std::size_t)> handler)
{
	auto self = shared_from_this();
	m_socket.async_read_some(boost::asio::buffer(m_data + read_len, total_len - read_len),
		[read_len, total_len, handler, self](const boost::system::error_code& ec, std::size_t bytesTransfered)
		{
			if (ec)
			{
				handler(ec, read_len + bytesTransfered);
				return;
			}
			if (read_len + bytesTransfered >= total_len)
			{
				handler(ec, read_len + bytesTransfered);
				return;
			}
			self->AsyncReadLen(read_len + bytesTransfered, total_len, handler);
		}
	);
}
