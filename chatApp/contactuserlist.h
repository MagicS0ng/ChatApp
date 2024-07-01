#ifndef CONTACTUSERLIST_H
#define CONTACTUSERLIST_H
#include <QListWidget>
#include <QEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QDebug>
#include "listbaseitem.h"
#include "conuseritem.h"
#include "grouptipitem.h"
#include <QRandomGenerator>
class ConUserItem;
class ContactUserList : public QListWidget
{
    Q_OBJECT
public:
    ContactUserList(QWidget* parent = nullptr);
    void ShowRedPoint(bool show=true);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override ;
private:
    void addContactUserList();
public slots:
    void slotItemClicked(QListWidgetItem *);
signals:
    void sig_loading_contact_user();
    void sig_switch_apply_friend_page();
private:
    ConUserItem * _add_friend_item;
};

#endif // CONTACTUSERLIST_H
