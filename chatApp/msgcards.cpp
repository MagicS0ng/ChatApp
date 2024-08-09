#include "msgcards.h"
#include "ui_msgcards.h"

msgCards::msgCards(QWidget *parent)
    : ListBaseItem(parent)
    , ui(new Ui::msgCards)
{
    ui->setupUi(this);
    SetItemType(ListItemType::CHAT_FRIEND_ITEM);
}

msgCards::~msgCards()
{
    delete ui;
}

QSize msgCards::sizeHint() const
{

        return QSize(240, 70);

}

std::shared_ptr<UserInfo> msgCards::GetUserInfo()
{
    return _user_info;
}

void msgCards::SetInfo(std::shared_ptr<UserInfo> user_info)
{
    _user_info = user_info;
    // 加载图片
    QPixmap pixmap(_user_info->_icon);

    // 设置图片自动缩放
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);

    ui->friend_id->setText(_user_info->_name);
    ui->friend_msg->setText(_user_info->_last_msg);
}
