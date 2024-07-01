#pragma once
#include "const.h"
#include "message.pb.h"
#include "message.grpc.pb.h"
#include "ConfigMgr.h"
#include <mutex>
#include <grpcpp/grpcpp.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "RedisMgr.h"
#include <climits>
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginReq;
using message::LoginRsp;
using message::StatusService;

class ChatServer
{
public:
	ChatServer(): host(""), port(""), name(""), con_count(0){}
	ChatServer(const ChatServer&cs):host(cs.host),port(cs.port),name(cs.name),con_count(cs.con_count){}
	ChatServer&operator=(const ChatServer &cs) {
		if (this == &cs)
		{
			return *this;
		}
		host = cs.host;
		port = cs.port;
		name = cs.name;
		con_count = cs.con_count;
	}
	std::string host;
	std::string port;
	std::string name;
	int con_count;
};
class StatusServiceImpl final : public StatusService::Service
{
	const std::string USERTOKENPREFIX{ "utoken_" };
public:
	StatusServiceImpl();
	Status GetChatServer(ServerContext *  context, const GetChatServerReq * request,GetChatServerRsp * reply) override;
	Status Login(ServerContext* context, const LoginReq* request,LoginRsp* reply) override;
private:
	void insertToken(int uid, std::string token);
	ChatServer getChatServer();
	std::unordered_map < std::string, ChatServer> m_servers;
	std::mutex m_server_mutex;
};
