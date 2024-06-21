#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QAction>
#include <QRandomGenerator>
#include "global.h"
#include <QKeyEvent>
#include "msgcards.h"
#include "loadingdialog.h"
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
private:
    void showSearch(bool isSearch);
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::chatDialog *ui;
    ChatUIMode m_state;
    ChatUIMode m_mode;
    bool is_loading;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
private slots:
    void slotLoadingChatFriends();
    void on_add_btn_clicked();
};

#endif // CHATDIALOG_H
