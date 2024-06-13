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
