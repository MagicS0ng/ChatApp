#ifndef SEARCHLIST_H
#define SEARCHLIST_H
#include <QListWidget>
#include <QWheelEvent>
#include <QEvent>
#include <QScrollBar>
#include <QDebug>
#include <QDialog>
#include <memory>
#include "userdata.h"
#include "tcpmgr.h"
#include "AddUserItem.h"
#include "loadingdlg.h"
#include "customizededit.h"
#include "findfaileddlg.h"
#include "findsuccessdlg.h"

class SearchList: public QListWidget
{
    Q_OBJECT
public:
    SearchList(QWidget *parent=nullptr);
    void CloseFindDlg();
    void SetSearchBox(QWidget * box);
protected:
    bool eventFilter(QObject *watched, QEvent * event) override;
private:
    void addTipItem();
    void waitPending(bool pending=true);
private:
    bool _send_pending;
    std::shared_ptr<QDialog> _find_dlg;
    QWidget * _search_box;
    LoadingDlg * _loadingDlg;
private slots:
    void slotItemClicked(QListWidgetItem * item);
    void slotUserSearch(std::shared_ptr<SearchInfo> si);
signals:
    void sig_jump_chat_item(std::shared_ptr<SearchInfo> si);
};

#endif // SEARCHLIST_H
