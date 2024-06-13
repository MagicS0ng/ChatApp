#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QAction>
#include <QRandomGenerator>
#include "global.h"
#include <QKeyEvent>
#include "msgcards.h"
#include "loadingdialog.h"
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
private:
    void showSearch(bool isSearch);
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::chatDialog *ui;
    ChatUIMode m_state;
    ChatUIMode m_mode;
    bool is_loading;
private slots:
    void slotLoadingChatFriends();
};

#endif // CHATDIALOG_H
