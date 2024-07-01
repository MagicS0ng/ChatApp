#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "const.h"
#include "ConfigMgr.h"
#include "hiredis.h"
#include "RedisMgr.h"
#include "MysqlMgr.h"
#include "AsioIOServicePool.h"
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include "StatusServiceImpl.h"
#include <memory>
#include <grpcpp/grpcpp.h>

void RunServer()
{
	auto& cfg = ConfigMgr::Inst();
	std::string server_address(cfg["StatusServer"]["Host"] + ":" + cfg["StatusServer"]["Port"]);
	StatusServiceImpl service;

	grpc::ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	boost::asio::io_context io_context;
	boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
	signals.async_wait([&server, &io_context](const boost::system::error_code& error, int signal_number)
		{
			if (!error)
			{
				std::cout << "Shutting down server..." << std::endl;
				server->Shutdown();;
				io_context.stop();
			}
		});
	std::thread([&io_context]() {io_context.run(); }).detach();
	server->Wait();
	io_context.stop();
}

int main()
{
	try {
		RunServer();
		RedisMgr::GetInstance()->Close();
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		RedisMgr::GetInstance()->Close();
		return -1;
	}
	return 0;
}
