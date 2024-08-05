#pragma once
#include "const.h"
#include "Singleton.h"
#include <grpcpp/grpcpp.h>
#include "message.pb.h"
#include "message.grpc.pb.h"
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "RedisMgr.h"
#include "UserMgr.h"
#include "MysqlMgr.h"
#include "ConfigMgr.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;
using message::AddFriendReq;
using message::AddFriendRsp;

using message::AuthFriendReq;
using message::AuthFriendRsp;

using message::GetChatServerRsp;
using message::LoginRsp;
using message::LoginReq;
using message::ChatService;

using message::TextChatMsgReq;
using message::TextChatMsgRsp;
using message::TextChatData;

class ChatConPool
{
public:
	ChatConPool(size_t poolSize, std::string host,std::string port)
	:b_stop_(false), _poolSize(poolSize), _host(host), _port(port)
	{
		for (size_t i = 0; i < poolSize; i++)
		{
			std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
			_connections.push(ChatService::NewStub(channel));


		}
	}
	~ChatConPool()
	{
		std::lock_guard<std::mutex> lock(_mutex);
		Close();
		while (!_connections.empty())
		{
			_connections.pop();
		}
	}
	std::unique_ptr<ChatService::Stub> getConnection()
	{
		std::unique_lock < std::mutex> lock(_mutex);
		_cond.wait(lock, [this]()
			{
				if (b_stop_)
				{
					return true;
				}
				return !_connections.empty();
			});
		if (b_stop_)
		{
			return nullptr;
		}
		auto context = std::move(_connections.front());
		_connections.pop();
		return context;
	}
	void Close()
	{
		b_stop_ = true;
		_cond.notify_all();
	}
	void returnConnection(std::unique_ptr<ChatService::Stub> context)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		if (b_stop_)
		{
			return;
		}
		_connections.push(std::move(context));
		_cond.notify_one();
	}
private:
	std::atomic<bool> b_stop_;
	size_t _poolSize;
	std::string _host;
	std::string _port;
	std::queue<std::unique_ptr<ChatService::Stub>> _connections;
	std::mutex _mutex;
	std::condition_variable _cond;
};
class ChatGrpcClient: public Singleton<ChatGrpcClient>
{
	friend class Singleton<ChatGrpcClient>;
public:
	~ChatGrpcClient();
	AddFriendRsp NotifyAddFriend(std::string server_ip, const AddFriendReq &req);
	AuthFriendRsp NotifyAuthFriend(std::string server_ip, const AuthFriendReq &req);
	bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo> &userInfo);
	TextChatMsgRsp NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtValue);
private:
	ChatGrpcClient();
	std::unordered_map<std::string, std::unique_ptr<ChatConPool>> _pools;
	
};

