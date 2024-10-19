#include "StatusGrpcClient.h"


StatusGrpcClient::StatusGrpcClient()
{
	auto& gCfgMgr = ConfigMgr::Inst();
	std::string host = gCfgMgr["StatusServer"]["Host"];
	std::string port = gCfgMgr["StatusServer"]["Port"];
	m_pool.reset(new StatusConPool(5, host, port));
}
StatusGrpcClient::~StatusGrpcClient()
{
	
}
GetChatServerRsp StatusGrpcClient::GetChatServer(int uid)
{
	ClientContext context;
	GetChatServerRsp reply;
	GetChatServerReq request;
	request.set_uid(uid);
	auto stub = m_pool->getConnection();
	Status status = stub->GetChatServer(&context, request, &reply);
	Defer defer([&stub, this]()
		{
			m_pool->returnConnection(std::move(stub));
		});
	if (status.ok())
	{
		return reply;
	}
	else
	{
		reply.set_error(ErrorCodes::RPCFailed);
		return reply;
	}
}
LoginRsp StatusGrpcClient::Login(int uid, std::string token)
{
	ClientContext context;
	LoginRsp reply;
	LoginReq request;
	request.set_uid(uid);
	request.set_token(token);
	auto stub = m_pool->getConnection();
	Status status = stub->Login(&context, request, &reply);
	Defer defer([&stub, this]()
		{
			m_pool->returnConnection(std::move(stub));
		});
	if (status.ok())
	{
		return reply;
	}
	else
	{
		reply.set_error(ErrorCodes::RPCFailed);
		return reply;
	}
}