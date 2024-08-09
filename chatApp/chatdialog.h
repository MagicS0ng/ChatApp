#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QAction>
#include <QRandomGenerator>
#include <QMouseEvent>
#include "global.h"
#include <QKeyEvent>
#include <QListWidgetItem>
#include "msgcards.h"
#include "statewidget.h"
#include "loadingdlg.h"
#include "userdata.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <httpmgr.h>
namespace Ui {
class chatDialog;
}

class chatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chatDialog(QWidget *parent = nullptr);
    ~chatDialog();
    void addChatFriend();
    void initHttpHandler();
    void ClearLabelState(StateWidget *lb);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void handleGlobalMousePress(QMouseEvent *);
private:
    void showSearch(bool isSearch);
    void AddLBGroup(StateWidget * lb);
    void keyPressEvent(QKeyEvent *event) override;
    void SetSelectChatItem(int uid = 0);
    void SetSelectChatPage(int uid = 0);
    void loadMoreChatUser();
    void loadMoreConUser();
    void UpdateChatMsg(std::vector<std::shared_ptr<TextChatData>> msgdata);
private:
    Ui::chatDialog *ui;
    ChatUIMode m_state;
    ChatUIMode m_mode;
    bool is_loading;
    QList<StateWidget*> _lb_list;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    QMap<int, QListWidgetItem*> _chat_items_added;
    int _cur_chat_uid;
    QWidget* _last_widget;
private slots:
    void SlotSideContact();
    void SlotSideChat();
    void slotLoadingChatFriends();
    void slotTextChanged(const QString &str);
    void slot_loading_contact_user();
public slots:
    void slot_apply_friend(std::shared_ptr<AddFriendApply> apply);
    void slot_add_auth_friend(std::shared_ptr<AuthInfo> auth_info);
    void slot_auth_rsp(std::shared_ptr<AuthRsp> auth_rsp);
    void slot_jump_chat_item(std::shared_ptr<SearchInfo> si);
    void slot_side_chat();
    void slot_friend_info_page(std::shared_ptr<UserInfo> user_info);
    void slot_switch_apply_friend_page();
    void slot_jump_chat_item_from_info_page(std::shared_ptr<UserInfo> user_info);
    void slot_item_clicked(QListWidgetItem *item);
    void slot_append_send_chat_msg(std::shared_ptr<TextChatData> msgdata);
    void slot_text_chat_msg(std::shared_ptr<TextChatMsg>);
};

#endif // CHATDIALOG_H
