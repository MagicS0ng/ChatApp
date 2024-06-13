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

void msgCards::SetInfo(QString name, QString avatar, QString msg)
{
    m_name = name;
    m_avatar = avatar;
    m_msg = msg;

    QPixmap pxmap(m_avatar);
    ui->icon_lb->setPixmap(pxmap.scaled(ui->icon_lb->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);
    ui->friend_id->setText(m_name);
    ui->friend_msg->setText(m_msg);
}
