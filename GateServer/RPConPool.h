#pragma once
#include <string>
#include <memory>
#include <queue>
#include "message.grpc.pb.h"
#include <grpcpp/grpcpp.h>
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;
using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;
class RPConPool
{
public:
	RPConPool(size_t poolSize, std::string host, std::string port);
	~RPConPool();
	std::unique_ptr<VarifyService::Stub> getConnection();
	void returnConnection(std::unique_ptr<VarifyService::Stub> context);
	void Close();
	
private:
	std::atomic<bool> is_stop;
	size_t poolSize_;
	std::string host_;
	std::string port_;
	std::queue<std::unique_ptr<VarifyService::Stub>> connections_;
	std::mutex mutex_;
	std::condition_variable cv;
};

