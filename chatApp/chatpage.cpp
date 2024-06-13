#include "chatpage.h"
#include "ui_chatpage.h"

ChatPage::ChatPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatPage)
{
    ui->setupUi(this);
    ui->recv_btn->SetState("normal","hover","press");
    ui->send_btn->SetState("normal","hover","press");

    ui->emoji_lb->SetState("normal", "hover","press","normal","hover","press");
    ui->file_lb ->SetState("normal", "hover","press","normal","hover","press");
}

ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, & opt,&p,this);
}
