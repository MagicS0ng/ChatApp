// ChatServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <csignal>
#include <thread>
#include <mutex>

#include "AsioIOServicePool.h"
#include "CServer.h"
#include "ConfigMgr.h"
#include "LogicSystem.h"
std::condition_variable cond_quit;
std::mutex mutex_quit;

int main()
{
	try
	{
		auto& cfg = ConfigMgr::Inst();  // ��ȡ����
		auto pool = AsioIOServicePool::GetInstance(); // io_context���߳��շ���Ϣ
		boost::asio::io_context io_context;	
		boost::asio::signal_set signals(io_context, SIGINT, SIGTERM); // SIGINT:C-c
		signals.async_wait([&io_context, pool](auto, auto) // �첽�ȴ�, ����SIGINT SIGTERM ͣ������
			{
				io_context.stop();
				pool->Stop();
			});
		auto port_str = cfg["SelfServer"]["Port"];
		CServer s(io_context, atoi(port_str.c_str()));
		io_context.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

