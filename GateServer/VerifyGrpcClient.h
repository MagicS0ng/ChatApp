#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "RPConPool.h"
#include "ConfigMgr.h"
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;
using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;


class VerifyGrpcClient: public Singleton<VerifyGrpcClient>
{
	friend class Singleton<VerifyGrpcClient>;
public:
	GetVarifyRsp GetVarifyCode(std::string email);
private:
	std::unique_ptr<RPConPool> pool_;
	VerifyGrpcClient();
	//std::unique_ptr<VarifyService::Stub> m_stub; //用于与服务器通信
};