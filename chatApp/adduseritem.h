#ifndef ADDUSERITEM_H
#define ADDUSERITEM_H

#include <QWidget>
#include "listbaseitem.h"

namespace Ui {
class AddUserItem;
}

class AddUserItem : public ListBaseItem
{
    Q_OBJECT

public:
    explicit AddUserItem(QWidget *parent = nullptr);
    ~AddUserItem();
    QSize sizeHint() const override
    {
        return QSize(250,70);
    }
private:
    Ui::AddUserItem *ui;
};

#endif // ADDUSERITEM_H
