#ifndef APPLYFRIENDPAGE_H
#define APPLYFRIENDPAGE_H

#include <QWidget>
#include <QJsonArray>
#include <memory>
#include <QPainter>
#include <QStyleOption>
#include <QRandomGenerator>
#include <unordered_map>
#include "userdata.h"
#include "applyfrienditem.h"
// #include "authenfriend.h"
#include "UserMgr.h"
#include "tcpmgr.h"
namespace Ui {
class ApplyFriendPage;
}

class ApplyFriendPage : public QWidget
{
    Q_OBJECT

public:
    explicit ApplyFriendPage(QWidget *parent = nullptr);
    ~ApplyFriendPage();
    void AddNewApply(std::shared_ptr<AddFriendApply> apply);
protected:
    void paintEvent(QPaintEvent *event);
private:
    void loadApplyList();
private:
    Ui::ApplyFriendPage *ui;
    std::unordered_map<int, ApplyFriendItem *> _unauth_items;
public slots:
    void slot_auth_rsp(std::shared_ptr<AuthRsp>);
signals:
    void sig_show_search();
};

#endif // APPLYFRIENDPAGE_H
