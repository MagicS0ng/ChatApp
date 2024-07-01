#ifndef APPLYFRIENDPAGE_H
#define APPLYFRIENDPAGE_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include "global.h"
#include "applyfrienditem.h"
#include <QRandomGenerator>
#include "authenfriend.h"
#include "userdata.h"
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
    void paintEvent(QPaintEvent * event);
private:
    Ui::ApplyFriendPage *ui;
signals:
    void SigShowSearch(bool);
};

#endif // APPLYFRIENDPAGE_H
