#pragma once
#include "const.h"
class CServer : public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context& _ioc, unsigned short& port);
	void Start();
private:
	tcp::acceptor m_acceptor;
	net::execution_context& m_ioc;
	tcp::socket m_socket;
};