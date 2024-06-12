#pragma once
#include "const.h"
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "message.pb.h"
using grpc::Channel;
using message::StatusService;

class StatusConPool
{
public:
	StatusConPool(size_t poolSize, std::string host, std::string port);
	~StatusConPool();
	std::unique_ptr<StatusService::Stub> getConnection();
	void Close();
	void returnConnection(std::unique_ptr<StatusService::Stub> context);
private:
	std::queue<std::unique_ptr<StatusService::Stub>> m_connections;
	std::mutex m_mutex;
	std::condition_variable m_cond;
	std::atomic<bool> is_stop;
	size_t m_poolSize;
	std::string m_host;
	std::string m_port;

};
