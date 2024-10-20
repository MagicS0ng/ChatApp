#include "CServer.h"
#include "ConfigMgr.h"
#include "RedisMgr.h"

int main()
{
	auto & gCfgMgr = ConfigMgr::Inst();
	std::string gate_port_str = gCfgMgr["GateServer"]["port"];
	unsigned short gate_port = atoi(gate_port_str.c_str());
	try
	{
		unsigned short port = static_cast<unsigned short>(8080);	// 端口
		net::io_context ioc{ 1 };									// 并发数量
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);		// 捕捉termination或interrupt 信号 Ctrl-C SIGTERM
		signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) // 异步地等待信号
			{
				if (error)
				{
					return;
				}
				ioc.stop();
			});
		std::make_shared<CServer>(ioc, port)->Start();
		std::cout << "Gate Server listening on port: " << port << "\n";
		ioc.run();
	}
	catch (std::exception & e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	return 0;
}