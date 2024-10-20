#ifndef MSGCARDS_H
#define MSGCARDS_H

#include "listbaseitem.h"
#include "userdata.h"

namespace Ui {
class msgCards;
}

class msgCards : public ListBaseItem
{
    Q_OBJECT

public:
    explicit msgCards(QWidget *parent = nullptr);
    ~msgCards();
    QSize sizeHint() const override;
    std::shared_ptr<UserInfo> GetUserInfo();
    void SetInfo(std::shared_ptr<FriendInfo> friend_info);
    void SetInfo(std::shared_ptr<UserInfo> user_info);
    void updateLastMsg(std::vector<std::shared_ptr<TextChatData>> msgs);
private:
    Ui::msgCards *ui;
    std::shared_ptr<UserInfo> _user_info;
};

#endif // MSGCARDS_H
