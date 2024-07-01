// ChatServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <csignal>
#include <thread>
#include <mutex>
#include "RedisMgr.h"
#include "AsioIOServicePool.h"
#include "CServer.h"
#include "ConfigMgr.h"
#include "LogicSystem.h"
#include "ChatServiceImpl.h"

std::condition_variable cond_quit;
std::mutex mutex_quit;


int main()
{
	auto& cfg = ConfigMgr::Inst();  // ��ȡ����
	auto server_name = cfg["SelfServer"]["Name"];
	try
	{
		auto pool = AsioIOServicePool::GetInstance(); // io_context���߳��շ���Ϣ
		RedisMgr::GetInstance()->HSet(LOGIN_COUNT, server_name, "0");

		std::string server_address(cfg["SelfServer"]["Host"] + ":" + cfg["SelfServer"]["RPCPort"]);
		ChatServiceImpl service;
		grpc::ServerBuilder builder;
		// �����˿ں���ӷ���
		builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
		builder.RegisterService(&service);
		// ����������gRPC������
		std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
		std::cout << "RPC Server listening on " << server_address << std::endl;
		//��������һ���̴߳���grpc����
		std::thread  grpc_server_thread([&server]() {
			server->Wait();
			});
		boost::asio::io_context io_context;	
		boost::asio::signal_set signals(io_context, SIGINT, SIGTERM); // SIGINT:C-c
		signals.async_wait([&io_context, pool, &server](auto, auto) // �첽�ȴ�, ����SIGINT SIGTERM ͣ������
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
		RedisMgr::GetInstance()->HDel(LOGIN_COUNT, server_name);
		RedisMgr::GetInstance()->Close();
	}
}

