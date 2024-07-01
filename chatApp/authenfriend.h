#ifndef AUTHENFRIEND_H
#define AUTHENFRIEND_H

#include "clickedlabel.h"
#include "friendlabel.h"
#include <QDialog>
#include <QScrollArea>
#include <QScrollBar>
namespace Ui {
class AuthenFriend;
}

class AuthenFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenFriend(QWidget *parent = nullptr);
    ~AuthenFriend();
    void InitTipLbs();
    void AddTipLbs(ClickedLabel * , QPoint cur_point, QPoint & next_point, int text_width, int text_height);
    bool eventFilter(QObject * obj, QEvent * event);
private:
    void resetLabels();
    void addLabel(QString name);
private:
    Ui::AuthenFriend *ui;
    QMap<QString, ClickedLabel*> _add_labels;
    std::vector<QString> _add_label_keys;
    QPoint _label_point;
    QMap<QString, FriendLabel*> _friend_labels;
    std::vector<QString> _friend_label_keys;
    std::vector<QString> _tip_data;
    QPoint _tip_cur_point;
public slots:
    void ShowMoreLabels();
    void SlotLabelEnter();
    void SlotRemoveFriendLabel(QString);
    //通过点击tip实现增加和减少好友便签
    void SlotChangeFriendLabelByTip(QString, ClicklbState);
    //输入框文本变化显示不同提示
    void SlotLabelTextChange(const QString& text);
    //输入框输入完成
    void SlotLabelEditFinished();
    //输入标签显示提示框，点击提示框内容后添加好友便签
    void SlotAddFirendLabelByClickTip(QString text);
    //处理确认回调
    void SlotApplySure();
    //处理取消回调
    void SlotApplyCancel();
};

#endif // AUTHENFRIEND_H
