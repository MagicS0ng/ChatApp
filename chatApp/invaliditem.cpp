#include "invaliditem.h"

InvalidItem::InvalidItem(QWidget *parent): ListBaseItem(parent) {
    SetItemType(ListItemType::INVALID_ITEM);
}
