// ChatServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <csignal>
#include <thread>
#include <mutex>
#include "ChatServiceImpl.h"
#include "AsioIOServicePool.h"
#include "CServer.h"
#include "ConfigMgr.h"
#include "LogicSystem.h"
std::condition_variable cond_quit;
std::mutex mutex_quit;

int main()
{
	auto& cfg = ConfigMgr::Inst();
	auto server_name = cfg["SelfServer"]["Name"];
	try
	{
		auto pool = AsioIOServicePool::GetInstance(); // io_context多线程收发消息
		// 设置登录数量为0;
		RedisMgr::GetInstance()->HSet(LOGIN_COUNT, server_name, "0");
		// 定义一个GrpcServer
		std::string server_address(cfg["SelfServer"]["Host"] + ":" + cfg["SelfServer"]["RPCPort"]);
		ChatServiceImpl service;
		grpc::ServerBuilder builder;
		builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
		builder.RegisterService(&service);
		std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
		std::cout << "RPC Server listening on " << server_address << std::endl;

		std::thread grpc_server_thread([&server]
			{
				server->Wait();
			});
		boost::asio::io_context io_context;	
		boost::asio::signal_set signals(io_context, SIGINT, SIGTERM); // SIGINT:C-c
		signals.async_wait([&io_context, pool, &server](auto, auto) // 异步等待, 触发SIGINT SIGTERM 停掉服务
			{
				io_context.stop();
				pool->Stop();
				server->Shutdown();
			});
		auto port_str = cfg["SelfServer"]["Port"];
		CServer s(io_context, atoi(port_str.c_str()));
		io_context.run();
		RedisMgr::GetInstance()->HDel(LOGIN_COUNT, server_name);
		RedisMgr::GetInstance()->Close();
		grpc_server_thread.join();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

