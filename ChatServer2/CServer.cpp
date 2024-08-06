#include "CServer.h"
CServer::CServer(boost::asio::io_context& io_context, short port):m_io_context(io_context), m_port(port),
m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
	std::cout << "Server start... listen on port [" << m_port << "]" << std::endl;
	StartAccept();
}
CServer::~CServer()
{

}
void CServer::ClearSession(std::string sessionid)
{
	if (m_sessions.find(sessionid) != m_sessions.end())
	{
		UserMgr::GetInstance()->RmvUserSession(m_sessions[sessionid]->GetUserId());
	}
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_sessions.erase(sessionid);
	}
	
}
void CServer::HandleAccept(std::shared_ptr<CSession> new_session, const boost::system::error_code& error)
{
	if (!error)
	{
		new_session->Start();
		std::lock_guard<std::mutex> lock(m_mutex);
		m_sessions.insert(std::make_pair(new_session->GetSessionId(), new_session));
	}
	else {
		std::cout << "session accept failed, error is " << error.what() << std::endl;
	}
	StartAccept();
}
void CServer::StartAccept()
{
	auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<CSession> new_session = std::make_shared<CSession>(io_context, this);
	// 通过 bind, 将CServer的成员函数变成async_accept可以接收的 变量
	// placeholder是调用时传入的参数
	m_acceptor.async_accept(new_session->GetSocket(), std::bind(&CServer::HandleAccept, this, new_session, std::placeholders::_1));
}