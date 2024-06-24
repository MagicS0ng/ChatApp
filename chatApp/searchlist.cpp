#include "searchlist.h"

SearchList::SearchList(QWidget *parent):QListWidget(parent), _send_pending(false), _find_dlg(nullptr),_search_box(nullptr)
{
    Q_UNUSED(parent);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewport()->installEventFilter(this);
    connect(this, &QListWidget::itemClicked, this, &SearchList::slotItemClicked);
    addTipItem();
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sigUserSearch,this,&SearchList::slotUserSearch);
}

void SearchList::CloseFindDlg()
{

}

void SearchList::SetSearchBox(QWidget *box)
{

}

bool SearchList::eventFilter(QObject *watched, QEvent *event)
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
    if(watched==this->viewport()&&event->type() ==QEvent::Wheel)
    {
        QWheelEvent * wheelEvent = static_cast<QWheelEvent *>(event);
        int numDegrees = wheelEvent->angleDelta().y() / 8;
        int numSteps = numDegrees/15;
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()-numSteps);
        return true;
    }
    return QListWidget::eventFilter(watched, event);
}

void SearchList::waitPending(bool pending)
{

}

void SearchList::slotItemClicked(QListWidgetItem *item)
{

}

void SearchList::slotUserSearch(std::shared_ptr<SearchInfo> si)
{

}

void SearchList::addTipItem()
{
    auto *invalid_item = new QWidget();
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(250,10));
    this->addItem(item);
    invalid_item->setObjectName("invalid_item");
    this->setItemWidget(item, invalid_item);
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);


    auto * add_user_item = new AddUserItem();
    QListWidgetItem * userItem = new QListWidgetItem();
    item->setSizeHint(add_user_item->sizeHint());
    this->addItem(userItem);
    this->setItemWidget(userItem, add_user_item);
}
