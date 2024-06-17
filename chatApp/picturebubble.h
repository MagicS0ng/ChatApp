#ifndef PICTUREBUBBLE_H
#define PICTUREBUBBLE_H
#include "bubbleframe.h"
#include <QPixmap>
#include <QLabel>
class PictureBubble: public  BubbleFrame
{
    Q_OBJECT
    enum {PIC_MAX_WIDTH=160, PIC_MAX_HEIGHT=90};
public:
    PictureBubble(const QPixmap &picture, ChatRole role, QWidget *parent = nullptr);
};

#endif // PICTUREBUBBLE_H
