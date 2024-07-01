#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QAction>
#include <QRandomGenerator>
#include "global.h"
#include <QKeyEvent>
#include "msgcards.h"
#include "statewidget.h"
#include "loadingdialog.h"
#include "statelabel.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <httpmgr.h>
#include "grouptipitem.h"
#include "conuseritem.h"
#include "userdata.h"
namespace Ui {
class chatDialog;
}

class chatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chatDialog(QWidget *parent = nullptr);
    ~chatDialog();
    void handleGlobalMousePress(QMouseEvent *event);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void CloseFindDlg();
private:
    void AddLBGroup(StateWidget * lb);
    void showSearch(bool isSearch);
    void addChatFriend();
    void initHttpHandler();
    void ClearLabelState(StateWidget *lb);
private:
    Ui::chatDialog *ui;
    ChatUIMode m_state;
    ChatUIMode m_mode;
    bool is_loading;
    QList<StateWidget*> _lb_list;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
public slots:
    void SlotSideContact();
    void SlotSideChat();
    void slotLoadingChatFriends();
    void slotTextChanged(const QString &str);
    void SlotFocusOut();
    void SlotLoadingContactUser();
    void SlotSwitchApplyFriendPage();
    void SlotFriendInfoPage();
    void SlotShowSearch(bool show);
    void SlotApplyFriend(std::shared_ptr<AddFriendApply> apply);
// private slots:
//     void on_send_btn_clicked();
};

#endif // CHATDIALOG_H
