#ifndef LINEITEM_H
#define LINEITEM_H

#include "listbaseitem.h"

#include <QWidget>

namespace Ui {
class LineItem;
}

class LineItem : public ListBaseItem
{
    Q_OBJECT

public:
    explicit LineItem(QWidget *parent = nullptr);
    ~LineItem();
    QSize sizeHint() const override;
private:
    Ui::LineItem *ui;
};

#endif // LINEITEM_H
