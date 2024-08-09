#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include "global.h"
#include "chatitembase.h"
#include "textbubble.h"
#include "picturebubble.h"
#include "userdata.h"
#include "usermgr.h"
namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();
    void SetUserInfo(std::shared_ptr<UserInfo> user_info);
    void AppendChatMsg(std::shared_ptr<TextChatData> msg);
protected:
    void paintEvent(QPaintEvent * event);
private slots:
    void on_send_btn_clicked();
signals:
    void sendMsg();
private:
    Ui::ChatPage *ui;
    std::shared_ptr<UserInfo> _user_info;
};

#endif // CHATPAGE_H
