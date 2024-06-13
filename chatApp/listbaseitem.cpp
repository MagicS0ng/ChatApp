#include "listbaseitem.h"

ListBaseItem::ListBaseItem(QWidget * parent):QWidget(parent)
{

}

void ListBaseItem::SetItemType(ListItemType itemType)
{
    m_itemType = itemType;
}

ListItemType ListBaseItem::GetItemType()
{
    return m_itemType;
}

void ListBaseItem::paintEvent(QPaintEvent *event)
{

        QStyleOption opt;
        opt.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, & opt,&p,this);

}
