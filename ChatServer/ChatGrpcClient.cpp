#include "ChatGrpcClient.h"

ChatGrpcClient::ChatGrpcClient()
{
    auto& cfgs = ConfigMgr::Inst();
    auto server_list = cfgs["PeerServer"]["Servers"];
    std::vector<std::string> words;
    std::stringstream ss(server_list);
    std::string word;
    while (std::getline(ss, word, ','))
    {
        words.push_back(word);
    }
    for(auto & word : words)
    {
        if (cfgs[word]["Name"].empty())
        {
            continue;
        }
        _pools[cfgs[word]["Name"]] = std::make_unique<ChatConPool>(5, cfgs[word]["Host"], cfgs[word]["Port"]);
    }
}
ChatGrpcClient::~ChatGrpcClient()
{
    
}

AddFriendRsp ChatGrpcClient::NotifyAddFriend(std::string server_ip, const AddFriendReq& req)
{
    AddFriendRsp rsp;
    Defer defer([&rsp, &req]() {
        rsp.set_error(ErrorCodes::Success);
        rsp.set_applyuid(req.applyuid());
        rsp.set_touid(req.touid());
        });
    auto find_iter = _pools.find(server_ip);
    if (find_iter == _pools.end())
    {
        return rsp;
    }
    std::cout << " request to " << find_iter->second << std::endl;
    auto& pool = find_iter->second;
    ClientContext context;
    auto stub = pool->getConnection();
    Status status = stub->NotifyAddFriend(&context, req, &rsp);
    Defer defercon([&stub, this, &pool]()
        {
            pool->returnConnection(std::move(stub));
        });
    if (!status.ok())
    {
        rsp.set_error(ErrorCodes::RPCFailed);
        return rsp;
    }
    return rsp;
}

AuthFriendRsp ChatGrpcClient::NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req)
{
    AuthFriendRsp rsp;
    rsp.set_error(ErrorCodes::Success);
    Defer defer([&rsp, &req]()
        {
            rsp.set_fromuid(req.fromuid());
            rsp.set_touid(req.touid());
        });
    auto find_iter = _pools.find(server_ip);
    if (find_iter == _pools.end())
    {
        return rsp;
    }
    auto& pool = find_iter->second;
    ClientContext context;
    auto stub = pool->getConnection();
    Status status = stub->NotifyAuthFriend(&context, req, &rsp);
    Defer defercon([&stub, this, &pool]()
        {
            pool->returnConnection(std::move(stub));
        });
    if (!status.ok())
    {
        rsp.set_error(ErrorCodes::RPCFailed);
        return rsp;
    }
    return rsp;
}

bool ChatGrpcClient::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo)
{
    std::string info_str = "";
    bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);
    if (b_base) {
        Json::Reader reader;
        Json::Value root;
        reader.parse(info_str, root);
        userinfo->uid = root["uid"].asInt();
        userinfo->userName = root["name"].asString();
        userinfo->userPwd = root["pwd"].asString();
        userinfo->userEmail = root["email"].asString();
        userinfo->nick = root["nick"].asString();
        userinfo->desc = root["desc"].asString();
        userinfo->sex = root["sex"].asInt();
        userinfo->icon = root["icon"].asString();
        std::cout << "user login uid is  " << userinfo->uid << " name  is "
            << userinfo->userName << " pwd is " << userinfo->userPwd << " email is " << userinfo->userEmail << std::endl;
    }
    else {
        
        std::shared_ptr<UserInfo> user_info = nullptr;
        user_info = MysqlMgr::GetInstance()->GetUser(uid);
        if (user_info == nullptr) {
            return false;
        }

        userinfo = user_info;
        Json::Value redis_root;
        redis_root["uid"] = uid;
        redis_root["pwd"] = userinfo->userPwd;
        redis_root["name"] = userinfo->userName;
        redis_root["email"] = userinfo->userEmail;
        redis_root["nick"] = userinfo->nick;
        redis_root["desc"] = userinfo->desc;
        redis_root["sex"] = userinfo->sex;
        redis_root["icon"] = userinfo->icon;
        RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
    }
}

TextChatMsgRsp ChatGrpcClient::NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtValue)
{
    TextChatMsgRsp rsp;
    rsp.set_error(ErrorCodes::Success);

    Defer defer([&rsp, &req]() {
        rsp.set_fromuid(req.fromuid());
        rsp.set_touid(req.touid());
        for (const auto& text_data : req.textmsgs()) {
            TextChatData* new_msg = rsp.add_textmsgs();
            new_msg->set_msgid(text_data.msgid());
            new_msg->set_msgcontent(text_data.msgcontent());
        }

        });

    auto find_iter = _pools.find(server_ip);
    if (find_iter == _pools.end()) {
        return rsp;
    }

    auto& pool = find_iter->second;
    ClientContext context;
    auto stub = pool->getConnection();
    Status status = stub->NotifyTextChatMsg(&context, req, &rsp);
    Defer defercon([&stub, this, &pool]() {
        pool->returnConnection(std::move(stub));
        });

    if (!status.ok()) {
        rsp.set_error(ErrorCodes::RPCFailed);
        return rsp;
    }

    return rsp;
}


