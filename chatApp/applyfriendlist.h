#ifndef APPLYFRIENDLIST_H
#define APPLYFRIENDLIST_H
#include <QListWidget>
#include <QWheelEvent>
#include <QEvent>
#include <QEvent>
#include <QScrollBar>
#include "listbaseitem.h"




class ApplyFriendList: public QListWidget
{
    Q_OBJECT
public:
    ApplyFriendList(QWidget *parent=nullptr);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private slots:

signals:
    void sig_show_search(bool);
};

#endif // APPLYFRIENDLIST_H
