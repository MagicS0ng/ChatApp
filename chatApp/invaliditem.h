#ifndef INVALIDITEM_H
#define INVALIDITEM_H
#include "listbaseitem.h"


class InvalidItem: ListBaseItem
{
    Q_OBJECT
public:
    explicit InvalidItem(QWidget *parent=nullptr);
    QSize sizeHint() const override
    {
        return QSize(240, 10);
    }
};

#endif // INVALIDITEM_H
