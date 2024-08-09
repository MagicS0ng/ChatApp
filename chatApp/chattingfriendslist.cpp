#include "chattingfriendslist.h"

ChattingFriendsList::ChattingFriendsList(QWidget * parent):QListWidget(parent),_loading_pending(false)
{
    Q_UNUSED(parent);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewport()->installEventFilter(this);
}

bool ChattingFriendsList::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==this->viewport())
    {
        if(event->type()==QEvent::Enter)
        {
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        }else if(event->type()==QEvent::Leave)
        {
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }
    if(watched==this->viewport()&&event->type()==QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);
        int numDegree = wheelEvent->angleDelta().y()/8;
        int numSteps = numDegree/15;
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()-numSteps);

        QScrollBar *scrollBar = this->verticalScrollBar();
        int maxScrollValue = scrollBar->maximum();
        int currentValue = scrollBar->value();
        if(maxScrollValue - currentValue <=0)
        {
            auto b_loaded = UserMgr::GetInstance()->IsLoadChatFin();
            if(b_loaded)
            {
                return  true;
            }
            if(_loading_pending)
            {
                return true;
            }

            qDebug() << "load more friends";
            _loading_pending = true;
            QTimer::singleShot(100, [this]()
                               {
                _loading_pending = false;
                QCoreApplication::quit();
            });

            emit sigLoadingChatFriends();
        }
        return true;
    }
    return QListWidget::eventFilter(watched,event);
}
