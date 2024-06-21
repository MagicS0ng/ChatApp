#pragma once
#include "const.h"
#include "AsioIOServicePool.h"
class CServer : public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context& _ioc, unsigned short& port);
	void Start();
private:
	tcp::acceptor m_acceptor;				// 用来接收一个tcp socket，和回调函数，
	net::execution_context& m_ioc;			// ioc_context, 处理I/O
	tcp::socket m_socket;					// socket，用来通信
};