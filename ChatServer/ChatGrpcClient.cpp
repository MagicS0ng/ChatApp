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
    return AddFriendRsp();
}

AuthFriendRsp ChatGrpcClient::NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req)
{
    return AuthFriendRsp();
}

bool ChatGrpcClient::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userInfo)
{
    return false;
}

TextChatMsgRsp ChatGrpcClient::NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtValue)
{
    return TextChatMsgRsp();
}


