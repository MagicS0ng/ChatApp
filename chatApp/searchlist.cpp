#include "searchlist.h"

#include "findsuccessdlg.h"

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
    if(_find_dlg)
    {
        _find_dlg->hide();
        _find_dlg = nullptr;
    }
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
    QWidget *widget = this->itemWidget(item);
    if(!widget)
    {
        qDebug() << "Slot item clicked widget is nullptr";
        return ;
    }
    ListBaseItem *customItem = qobject_cast<ListBaseItem *> (widget);
    if(!customItem)
    {
        qDebug() << "slot item clicked widget is nullptr";
        return ;
    }
    auto itemType = customItem->GetItemType();
    if(itemType==ListItemType::INVALID_ITEM)
    {
        qDebug() << "invalid item clicked";
        return ;
    }
    if(itemType==ListItemType::ADD_USER_TIP_ITEM)
    {
        qDebug() << "search.....";
        _find_dlg = std::make_shared<FindSuccessDlg>(this);
        auto si = std::make_shared<SearchInfo>(0,"nima","nima","nima",0);
        std::dynamic_pointer_cast<FindSuccessDlg>(_find_dlg)->SetSearchInfo(si);
        _find_dlg->show();
        // std::dynamic_pointer_cast<FindSuccessDlg>(_find_dlg)->SetSearchInfo(si);
        // if(_send_pending)
        //     return ;
        // waitPending(true);
        // auto searchBox = dynamic_cast<CustomizedEdit *>(_search_box);
        // auto uid_str = searchBox->text();
        // QJsonObject jsonObj;
        // jsonObj["uid"] = uid_str;
        // QJsonDocument jsonDoc(jsonObj);
        // QString jsonStr = jsonDoc.toJson(QJsonDocument::Indented);
        // emit TcpMgr::GetInstance()->sigSendData(ReqId::ID_SEARCH_USER_REQ, jsonStr.toUtf8());
        return;
    }
    CloseFindDlg();
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
    userItem->setSizeHint(add_user_item->sizeHint());
    this->addItem(userItem);
    this->setItemWidget(userItem, add_user_item);
}
