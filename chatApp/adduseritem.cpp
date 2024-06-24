#include "adduseritem.h"
#include "ui_adduseritem.h"

AddUserItem::AddUserItem(QWidget *parent)
    : ListBaseItem(parent)
    , ui(new Ui::AddUserItem)
{
    ui->setupUi(this);
    SetItemType(ListItemType::ADD_USER_ITEM);
}

AddUserItem::~AddUserItem()
{
    delete ui;
}
