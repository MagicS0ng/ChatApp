#ifndef APPLYFRIENDITEM_H
#define APPLYFRIENDITEM_H

#include "listbaseitem.h"

#include <QWidget>

namespace Ui {
class ApplyFriendItem;
}

class ApplyFriendItem : public ListBaseItem
{
    Q_OBJECT

public:
    explicit ApplyFriendItem(QWidget *parent = nullptr);
    ~ApplyFriendItem();
    void SetInfo(int uid, QString name, QString avatar, QString msg);
    void ShowAddBtn(bool);
private:
    Ui::ApplyFriendItem *ui;
    QString _name;
    QString _head;
    QString _msg;
    int _uid;
signals:
    void SigAuthFriend(int uid);
};

#endif // APPLYFRIENDITEM_H
