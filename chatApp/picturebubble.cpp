#include "picturebubble.h"

PictureBubble::PictureBubble(const QPixmap &picture, ChatRole role, QWidget *parent):BubbleFrame(role,parent)
{
    QLabel *lb = new QLabel();
    lb->setScaledContents(true);
    QPixmap pxMap = picture.scaled(QSize(PIC_MAX_WIDTH, PIC_MAX_HEIGHT), Qt::KeepAspectRatio);
    lb->setPixmap(pxMap);
    this->setWidget(lb);

    int left_margin = this->layout()->contentsMargins().left();
    int right_margin = this->layout()->contentsMargins().right();
    int v_margin = this->layout()->contentsMargins().bottom();
    setFixedSize(pxMap.width()+left_margin+right_margin, pxMap.height()+v_margin*2);
}
