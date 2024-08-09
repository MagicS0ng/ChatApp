#include "chattingview.h"

ChattingView::ChattingView(QWidget * parent):QWidget(parent), isAppended(false)
{
    QVBoxLayout *pMainLayout = new QVBoxLayout();
    this->setLayout(pMainLayout);
    pMainLayout->setContentsMargins(0,0,0,0);

    m_pScrollArea = new QScrollArea();
    m_pScrollArea->setObjectName("chat_area");
    pMainLayout->addWidget(m_pScrollArea);
    QWidget * w = new QWidget(this);
    w->setObjectName("chat_bg");
    w->setAutoFillBackground(true);

    QVBoxLayout *pVLayout_1 = new QVBoxLayout();
    pVLayout_1->addWidget(new QWidget(), 100000);
    w->setLayout(pVLayout_1);
    m_pScrollArea->setWidget(w);
    m_pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar * pVScrollBar = m_pScrollArea->verticalScrollBar();
    connect(pVScrollBar, &QScrollBar::rangeChanged, this, &ChattingView::OnVScrollBarMoved);
    QHBoxLayout *pHLayout_1 = new QHBoxLayout();
    pHLayout_1->addWidget(pVScrollBar,0,Qt::AlignRight);
    pHLayout_1->setContentsMargins(0,0,0,0);
    m_pScrollArea->setLayout(pHLayout_1);
    pVScrollBar->setHidden(true);
    m_pScrollArea->setWidgetResizable(true);
    m_pScrollArea->installEventFilter(this);
    initStyleSheet();

}

void ChattingView::appendMsgBubble(QWidget *bubble)
{
    QVBoxLayout *vl = qobject_cast<QVBoxLayout *>(m_pScrollArea->widget()->layout());
    vl->insertWidget(vl->count()-1, bubble);
    isAppended = true;
}

void ChattingView::prependMsgBubble(QWidget *bubble)
{

}

void ChattingView::insertMsgBubble(QWidget *pre, QWidget *re)
{

}

void ChattingView::removeAllItem()
{
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(m_pScrollArea->widget()->layout());

    int count = layout->count();

    for (int i = 0; i < count - 1; ++i) {
        QLayoutItem *item = layout->takeAt(0); // 始终从第一个控件开始删除
        if (item) {
            if (QWidget *widget = item->widget()) {
                delete widget;
            }
            delete item;
        }
    }
}

bool ChattingView::eventFilter(QObject *o, QEvent *e)
{
    if(e->type()==QEvent::Enter&&o==m_pScrollArea)
    {
        m_pScrollArea->verticalScrollBar()->setHidden(m_pScrollArea->verticalScrollBar()->maximum()==0);
    }else   if(e->type()==QEvent::Leave&&o==m_pScrollArea)
    {
        m_pScrollArea->verticalScrollBar()->setHidden(true);
    }
    return QWidget::eventFilter(o, e);
}

void ChattingView::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p,this);
}

void ChattingView::OnVScrollBarMoved(int min , int max)
{
    if(isAppended)
    {
        QScrollBar *pVScrollBar = m_pScrollArea->verticalScrollBar();
        pVScrollBar->setSliderPosition(pVScrollBar->maximum());
        QTimer::singleShot(500,[this]{
            isAppended=false;
        });
    }

}

void ChattingView::initStyleSheet()
{

}
