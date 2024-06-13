#ifndef LISTBASEITEM_H
#define LISTBASEITEM_H
#include <QWidget>
#include "global.h"

class ListBaseItem: public QWidget
{
    Q_OBJECT
public:
    explicit ListBaseItem(QWidget * parent = nullptr);
    void SetItemType(ListItemType itemType);
    ListItemType GetItemType();
private:
    ListItemType m_itemType;
public slots:
signals:

};

#endif // LISTBASEITEM_H
