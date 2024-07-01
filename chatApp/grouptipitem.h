#ifndef GROUPTIPITEM_H
#define GROUPTIPITEM_H

#include "listbaseitem.h"

#include <QWidget>

namespace Ui {
class GroupTipItem;
}

class GroupTipItem : public ListBaseItem
{
    Q_OBJECT

public:
    explicit GroupTipItem(QWidget *parent = nullptr);
    ~GroupTipItem();
    QSize sizeHint() const override;
    void SetGroupTip(QString str);
private:
    QString _tip;
    Ui::GroupTipItem *ui;
};

#endif // GROUPTIPITEM_H
