#ifndef BUBBLEFRAME_H
#define BUBBLEFRAME_H
#include <QFrame>
#include <QPainter>
#include "global.h"
#include <QHBoxLayout>
class BubbleFrame: public QFrame
{
    Q_OBJECT
    enum {WIDTH_SANJIAO=8};
public:
    BubbleFrame(ChatRole role, QWidget *parent = nullptr);
    void setMargin(int margin);
    void setWidget(QWidget * w);
protected:
    void paintEvent(QPaintEvent *e) override;
private:
    QHBoxLayout *m_pHLayout;
    ChatRole m_role;
    int m_margin;
};

#endif // BUBBLEFRAME_H
