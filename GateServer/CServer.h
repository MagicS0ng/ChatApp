#pragma once
#include "const.h"
#include "AsioIOServicePool.h"
class CServer : public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context& _ioc, unsigned short& port);
	void Start();
private:
	tcp::acceptor m_acceptor;				// ��������һ��tcp socket���ͻص�������
	net::execution_context& m_ioc;			// ioc_context, ����I/O
	tcp::socket m_socket;					// socket������ͨ��
};