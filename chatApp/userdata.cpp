#include "userdata.h"

SearchInfo::SearchInfo(int uid, QString name, QString nick, QString des, int sex, QString icon)
    :_uid(uid), _name(name), _nick(nick), _desc(des), _sex(sex), _icon(icon)
{

}

void FriendInfo::AppendChatMsgs(const std::vector<std::shared_ptr<TextChatData> > text_vec)
{
    for(const auto & text: text_vec){
        _chat_msgs.push_back(text);
    }
}
