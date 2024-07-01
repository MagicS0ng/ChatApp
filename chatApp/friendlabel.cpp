#include "friendlabel.h"
#include "ui_friendlabel.h"

FriendLabel::FriendLabel(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FriendLabel)
{
    ui->setupUi(this);
    ui->close_lb->SetState("normal","hover","pressed",
                           "selected_normal","selected_hover","selected_pressed");
    connect(ui->close_lb, &ClickedLabel::clicked, this, &FriendLabel::SlotClose);
}

FriendLabel::~FriendLabel()
{
    delete ui;
}

void FriendLabel::SetText(QString text)
{
    _text =text;
    ui->tip_lb->setText(_text);
    ui->tip_lb->adjustSize();
    QFontMetrics fontMetrics(ui->tip_lb->font());
    auto textWidth = fontMetrics.horizontalAdvance(ui->tip_lb->text());
    auto textHeight = fontMetrics.height();
    this->setFixedWidth(ui->tip_lb->width()+ui->close_lb->width()+5);
    this->setFixedHeight(textHeight+2);
    qDebug()<< "  this->setFixedHeight " << this->height();
    _width = this->width();
    _height = this->height();
}

int FriendLabel::Width()
{
    return _width;
}

int FriendLabel::Height()
{
    return _height;
}

QString FriendLabel::Text()
{
    return _text;
}

void FriendLabel::SlotClose()
{
    emit SigClose(_text);
}
