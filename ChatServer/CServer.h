#pragma once
#include <boost/asio.hpp>
#include <memory.h>
#include <map>
#include <iostream>
#include <mutex>
#include <functional>
#include "CSession.h"
#include "AsioIOServicePool.h"
#include "UserMgr.h"
using tcp = boost::asio::ip::tcp;
class CSession;
class CServer
{
public:
	CServer(boost::asio::io_context& io_context, short port);
	~CServer();
	void ClearSession(std::string);
private:
	void HandleAccept(std::shared_ptr<CSession> , const boost::system::error_code& error);
	void StartAccept();
	boost::asio::io_context& m_io_context;
	short m_port;
	tcp::acceptor m_acceptor;
	std::map<std::string, std::shared_ptr<CSession>> m_sessions;
	std::mutex m_mutex;
};