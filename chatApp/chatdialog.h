#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QAction>
#include <QRandomGenerator>
#include <QMouseEvent>
#include "global.h"
#include <QKeyEvent>
#include "msgcards.h"
#include "statewidget.h"
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
    void ClearLabelState(StateWidget *lb);
protected:
    bool eventFilter(QObject *, QEvent *) override;
    void handleGlobalMousePress(QMouseEvent *);
private:
    void showSearch(bool isSearch);
    void AddLBGroup(StateWidget * lb);
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::chatDialog *ui;
    ChatUIMode m_state;
    ChatUIMode m_mode;
    bool is_loading;
    QList<StateWidget*> _lb_list;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
private slots:
    void SlotSideContact();
    void SlotSideChat();
    void slotLoadingChatFriends();
    void slotTextChanged(const QString &str);
};

#endif // CHATDIALOG_H
