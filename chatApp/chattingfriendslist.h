#ifndef CHATTINGFRIENDSLIST_H
#define CHATTINGFRIENDSLIST_H
#include <QObject>
#include <QListWidget>
#include <QEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QTimer>
#include <QCoreApplication>
#include "UserMgr.h"
class ChattingFriendsList: public QListWidget
{
    Q_OBJECT
public:
    ChattingFriendsList(QWidget * parent);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override; //change scrollbar visibilty while focusing
signals:
    void sigLoadingChatFriends();
private:
    bool _loading_pending;
};

#endif // CHATTINGFRIENDSLIST_H
